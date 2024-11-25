#include <iostream>
#include <stack>
#include <string>
using namespace std;

int precedence(char sym) {
    if (sym == '+' || sym == '-') return 1;
    if (sym == '*' || sym == '/') return 2;
    if (sym == '^') return 3;
    return 0;
}
string infixToPostfix(const string& infix) {
    stack<char> symbol;
    string postfix;
    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;
        }
        else if (ch ==  '(' ) {
            symbol.push(ch);
        }
        else if (ch ==  ')' ) 
{
            while(!symbol.empty() && symbol.top() != '(' ) {
                postfix += symbol.top();
                symbol.pop();
            }
            if (!symbol.empty()) symbol.pop();
        }
        else {
           while (!symbol.empty() && precedence(symbol.top()) >= precedence(ch)) 
{
                postfix += symbol.top();
                symbol.pop();
            }
            symbol.push(ch);
        }
    }
    while (!symbol.empty()) 
{
        postfix += symbol.top();
        symbol.pop();
    }
    return postfix;
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;
    string postfix = infixToPostfix(infix);
    cout << "Postfix expression: " << postfix << endl;
    return 0;
}

