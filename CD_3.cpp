#include <bits/stdc++.h>
using namespace std;

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isOperand(char ch) {
    return isdigit(ch) || isalpha(ch);
}

bool isValidExpression(const string& expression) {
    stack<char> brackets;
    bool operatorFlag = true;

    for (char ch : expression) {
        if (ch == '(') {
            brackets.push(ch);
        } else if (ch == ')') {
            if (brackets.empty() || (ch == ')' && brackets.top() != '(') || 
            (ch == '}' && brackets.top() != '{') || 
            (ch == ']' && brackets.top() != '[')) {
                return false;
            }
            brackets.pop();
        } else if (isOperator(ch)) {
            if (operatorFlag) {
                return false;
            }
            operatorFlag = true;
        } else if (isOperand(ch)) {
            operatorFlag = false;
        } else if (!isspace(ch)) {
            return false;
        }
    }

    return brackets.empty() && !operatorFlag;
}

int main() {
    string expr1 = "(a/b";
    cout<< "expression:"<< expr1<<endl;
    if (isValidExpression(expr1)) {
        cout << "The expression is valid.\n";
    } else {
        cout << "The expression is invalid.\n";
    }

    string expr;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expr);

    if (isValidExpression(expr)) {
        cout << "The expression is valid.\n";
    } else {
        cout << "The expression is invalid.\n";
    }

    return 0;
}
