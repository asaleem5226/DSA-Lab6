#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

//  Custom Stack (Array-based) 
const int MAX = 1000;

template <typename T>
class Stack {
private:
    T arr[MAX];
    int top;

public:
    Stack() { top = -1; }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX - 1;
    }

    void push(T x) {
        if (isFull()) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++top] = x;
    }

    T pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return T();
        }
        return arr[top--];
    }

    T peek() {
        if (isEmpty()) {
            return T();
        }
        return arr[top];
    }
};

//  Helper Functions 

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isRightAssociative(char op) {
    return op == '^';
}

//  1. Infix to Postfix 
string infix_to_postfix(string expr) {
    Stack<char> st;
    string result = "";

    for (char c : expr) {
        if (c == ' ') continue;                     // ignore spaces

        if (isalnum(c)) {
            result += c;
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                result += st.pop();
            }
            if (!st.isEmpty()) st.pop();             // remove '('
        }
        else if (isOperator(c)) {
            while (!st.isEmpty() && st.peek() != '(' &&
                   (precedence(st.peek()) > precedence(c) ||
                   (precedence(st.peek()) == precedence(c) && !isRightAssociative(c)))) {
                result += st.pop();
            }
            st.push(c);
        }
    }

    while (!st.isEmpty()) {
        result += st.pop();
    }
    return result;
}

//  2. Infix to Prefix 
string infix_to_prefix(string expr) {
    // Step 1: Reverse the expression
    string rev = "";
    for (int i = expr.length() - 1; i >= 0; i--) {
        if (expr[i] == '(') rev += ')';
        else if (expr[i] == ')') rev += '(';
        else rev += expr[i];
    }

    // Step 2: Convert reversed expression to postfix
    string postfix = infix_to_postfix(rev);

    // Step 3: Reverse the postfix to get prefix
    string prefix = "";
    for (int i = postfix.length() - 1; i >= 0; i--) {
        prefix += postfix[i];
    }
    return prefix;
}

//  3. Postfix to Infix 
string postfix_to_infix(string expr) {
    Stack<string> st;

    for (char c : expr) {
        if (c == ' ') continue;

        if (isalnum(c)) {
            st.push(string(1, c));
        }
        else if (isOperator(c)) {
            string op2 = st.pop();
            string op1 = st.pop();
            string temp = "(" + op1 + c + op2 + ")";
            st.push(temp);
        }
    }
    return st.pop();
}

//  4. Evaluate Postfix 
double evaluate_postfix(string expr) {
    Stack<double> st;

    for (char c : expr) {
        if (c == ' ') continue;

        if (isdigit(c)) {
            st.push(c - '0');                       // single digit
        }
        else if (isOperator(c)) {
            double b = st.pop();
            double a = st.pop();
            double res = 0;

            switch (c) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                case '^': res = pow(a, b); break;
            }
            st.push(res);
        }
    }
    return st.pop();
}

//  5. Evaluate Prefix 
double evaluate_prefix(string expr) {
    Stack<double> st;

    // Scan from right to left
    for (int i = expr.length() - 1; i >= 0; i--) {
        char c = expr[i];
        if (c == ' ') continue;

        if (isdigit(c)) {
            st.push(c - '0');
        }
        else if (isOperator(c)) {
            double a = st.pop();
            double b = st.pop();
            double res = 0;

            switch (c) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                case '^': res = pow(a, b); break;
            }
            st.push(res);
        }
    }
    return st.pop();
}

//  Main (Demo) 
int main() {
    string infix;

    cout << "Enter an Infix Expression (e.g. (2+3)*4 or a+b*c): ";
    getline(cin, infix);

    cout << "\n========== Results ==========\n";

    string postfix = infix_to_postfix(infix);
    cout << "Postfix   : " << postfix << endl;

    string prefix = infix_to_prefix(infix);
    cout << "Prefix    : " << prefix << endl;

    string infix_back = postfix_to_infix(postfix);
    cout << "Postfix → Infix : " << infix_back << endl;

    // Evaluation (only works correctly if expression contains digits 0-9)
    bool hasDigits = false;
    for (char c : infix) {
        if (isdigit(c)) {
            hasDigits = true;
            break;
        }
    }

    if (hasDigits) {
        cout << "Evaluate Postfix : " << evaluate_postfix(postfix) << endl;
        cout << "Evaluate Prefix  : " << evaluate_prefix(prefix) << endl;
    } else {
        cout << "(Evaluation skipped – expression contains variables)\n";
    }

    return 0;
}