#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// ==================== Custom Stack (Array-based) ====================
const int MAX = 1000;

template <typename T>
class Stack {
private:
    T arr[MAX];
    int topIndex;

public:
    Stack() { topIndex = -1; }

    bool isEmpty() {
        return topIndex == -1;
    }

    bool isFull() {
        return topIndex == MAX - 1;
    }

    void push(T x) {
        if (isFull()) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++topIndex] = x;
    }

    T pop() {
        if (isEmpty()) {
            return T();          // return default value
        }
        return arr[topIndex--];
    }

    T peek() {
        if (isEmpty()) {
            return T();
        }
        return arr[topIndex];
    }
};

// ==================== PART A: Bracket Validator ====================
bool isValidBrackets(string s) {
    Stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        }
        else if (c == ')' || c == '}' || c == ']') {
            if (st.isEmpty()) {
                return false;           // closing bracket without opening
            }

            char top = st.pop();

            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false;           // mismatched brackets
            }
        }
        // ignore all other characters
    }

    return st.isEmpty();                // stack must be empty at the end
}

// ==================== PART B: HTML/XML Tag Validator ====================
// Returns: pair<bool, vector<string>>  →  (isValid, list_of_errors)
pair<bool, vector<string>> validate_markup(string s) {
    Stack<string> st;
    vector<string> errors;
    int i = 0;
    int n = s.length();

    while (i < n) {
        // Skip non-tag characters
        if (s[i] != '<') {
            i++;
            continue;
        }

        // Found a '<'
        i++;  // move past '<'

        if (i >= n) {
            errors.push_back("Unexpected end of string after '<'");
            break;
        }

        bool isClosing = false;
        if (s[i] == '/') {
            isClosing = true;
            i++;
        }

        // Extract tag name
        string tagName = "";
        while (i < n && s[i] != '>' && !isspace(s[i])) {
            tagName += s[i];
            i++;
        }

        // Skip any attributes or spaces until '>'
        while (i < n && s[i] != '>') {
            i++;
        }

        if (i >= n || s[i] != '>') {
            errors.push_back("Missing '>' for tag <" + tagName + ">");
            break;
        }
        i++;  // move past '>'

        if (tagName.empty()) {
            errors.push_back("Empty tag name found");
            continue;
        }

        if (!isClosing) {
            // Opening tag
            st.push(tagName);
        }
        else {
            // Closing tag
            if (st.isEmpty()) {
                errors.push_back("Closing tag </" + tagName + "> without matching opening tag");
            }
            else {
                string top = st.pop();
                if (top != tagName) {
                    errors.push_back("Mismatched tags: expected </" + top + "> but found </" + tagName + ">");
                    // Optionally push it back if you want stricter recovery
                    // st.push(top);
                }
            }
        }
    }

    // Any remaining opening tags are unclosed
    while (!st.isEmpty()) {
        string unclosed = st.pop();
        errors.push_back("Unclosed tag <" + unclosed + ">");
    }

    bool isValid = errors.empty();
    return {isValid, errors};
}

// ==================== MAIN (Demo Menu) ====================
int main() {
    int choice;
    string input;

    do {
        cout << "\n============================================\n";
        cout << "         TASK 2 - Expression Validators\n";
        cout << "============================================\n";
        cout << "1. Bracket Validator (Part A)\n";
        cout << "2. HTML/XML Tag Validator (Part B)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();   // clear newline

        if (choice == 1) {
            cout << "\nEnter a string with brackets: ";
            getline(cin, input);

            if (isValidBrackets(input)) {
                cout << "Result: VALID - All brackets are balanced and correctly nested.\n";
            } else {
                cout << "Result: INVALID - Brackets are not properly balanced/nested.\n";
            }
        }
        else if (choice == 2) {
            cout << "\nEnter HTML/XML markup string:\n";
            getline(cin, input);

            auto result = validate_markup(input);
            bool isValid = result.first;
            vector<string> errors = result.second;

            if (isValid) {
                cout << "Result: VALID - All tags are properly nested and closed.\n";
            } else {
                cout << "Result: INVALID\n";
                cout << "Errors found:\n";
                for (size_t i = 0; i < errors.size(); i++) {
                    cout << "  " << (i + 1) << ". " << errors[i] << endl;
                }
            }
        }
        else if (choice == 3) {
            cout << "Exiting program. Goodbye!\n";
        }
        else {
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}