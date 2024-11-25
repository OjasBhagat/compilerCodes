/*
write a program to design Lexical Analyzer in C/C++.
string keywords ={"int" , "float" , "bool"}

Input 
Enter number of lines of input = 2
    int a,b,c = 20;
    flot k = 20.5;

Output
    keywords = int , float

    operators are = =
    total operators = 2

    constants are 20  20.5
    total constants = 2
*/

#include <bits/stdc++.h>
using namespace std;

enum TokenType { KEYWORD, IDENTIFIER, NUMBER, OPERATOR, UNKNOWN };

struct Token {
    TokenType type;
    string value;
};

unordered_set<string> kwSet = {"int", "float", "bool", "if", "else", "while", "for", "return"};
unordered_set<string> multiOpSet = {"==", "!=", "<=", ">=", "&&", "||", "++", "--"};
unordered_set<char> unaryOpSet = {'+', '-', '!'};

vector<Token> tokenize(const string &line) {
    vector<Token> tokens;
    size_t idx = 0;

    while (idx < line.length()) {
        char c = line[idx];

        if (isspace(c)) {
            idx++;
            continue;
        }

        string currToken;

        if (isdigit(c)) {
            while (idx < line.length() && (isdigit(line[idx]) || line[idx] == '.')) {
                currToken += line[idx++];
            }
            tokens.push_back({NUMBER, currToken});
        }
        else if (isalpha(c)) {
            while (idx < line.length() && (isalnum(line[idx]) || line[idx] == '_')) {
                currToken += line[idx++];
            }
            TokenType type = (kwSet.count(currToken) ? KEYWORD : IDENTIFIER);
            tokens.push_back({type, currToken});
        }
        else if (idx + 1 < line.length() && multiOpSet.count(line.substr(idx, 2))) {
            tokens.push_back({OPERATOR, line.substr(idx, 2)});
            idx += 2;
        }
        else if (strchr("=+-*/%<>&|?", c)) {
            tokens.push_back({OPERATOR, string(1, c)});
            idx++;
        }
        else if (unaryOpSet.count(c)) {
            tokens.push_back({OPERATOR, string(1, c)});
            idx++;
        }
        else {
            tokens.push_back({UNKNOWN, string(1, c)});
            idx++;
        }
    }

    return tokens;
}

void printTokens(const string &label, const vector<string> &tokens) {
    cout << "\n" << label << ": ";
    for (const string &token : tokens) {
        cout << token << " ";
    }
    cout << "\nTotal " << label << ": " << tokens.size() << endl;
}

int main() {
    int numLines;
    cout << "Enter number of lines of input: ";
    cin >> numLines;
    cin.ignore();

    unordered_set<string> kwSetFinal, opSetFinal, constSetFinal, idSetFinal;

    for (int i = 0; i < numLines; ++i) {
        string line;
        cout << "Enter line " << (i + 1) << ": ";
        getline(cin, line);

        vector<Token> tokens = tokenize(line);
        for (const auto &token : tokens) {
            switch (token.type) {
                case KEYWORD: kwSetFinal.insert(token.value); break;
                case OPERATOR: opSetFinal.insert(token.value); break;
                case NUMBER: constSetFinal.insert(token.value); break;
                case IDENTIFIER: idSetFinal.insert(token.value); break;
                default: break;
            }
        }
    }

    printTokens("Keywords", vector<string>(kwSetFinal.begin(), kwSetFinal.end()));
    printTokens("Operators", vector<string>(opSetFinal.begin(), opSetFinal.end()));
    printTokens("Constants", vector<string>(constSetFinal.begin(), constSetFinal.end()));
    printTokens("Identifiers", vector<string>(idSetFinal.begin(), idSetFinal.end()));

    return 0;
}