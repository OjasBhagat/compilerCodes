#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <map>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

string applyOp(char op, string operand1, string operand2, int &tempCount) {
    string tempVar = "t" + to_string(tempCount++);
    cout << tempVar << " = " << operand1 << " " << op << " " << operand2 << endl;
    return tempVar;
}

void generateThreeAddressCode(const string &expr) {
    stack<string> values;
    stack<char> ops;
    int tempCount = 1;

    for (int i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue;

        if (isdigit(expr[i]) || isalpha(expr[i])) {
            string operand(1, expr[i]);
            values.push(operand);
        }
        else if (expr[i] == '(') {
            ops.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                string operand2 = values.top(); values.pop();
                string operand1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                string result = applyOp(op, operand1, operand2, tempCount);
                values.push(result);
            }
            ops.pop();
        }
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                string operand2 = values.top(); values.pop();
                string operand1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                string result = applyOp(op, operand1, operand2, tempCount);
                values.push(result);
            }
            ops.push(expr[i]);
        }
    }

    while (!ops.empty()) {
        string operand2 = values.top(); values.pop();
        string operand1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        string result = applyOp(op, operand1, operand2, tempCount);
        values.push(result);
    }

    cout << "result = " << values.top() << endl;
}

int main() {
    string expr;
    cout << "Enter an expression: ";
    getline(cin, expr);

    cout << "Three-Address Code for expression: " << expr << endl;
    generateThreeAddressCode(expr);

    return 0;
}
