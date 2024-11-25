#include <bits/stdc++.h>
using namespace std;
int main() {
int n;
cout << "Enter the number of variables: ";
cin >> n;
while(n--) {
string var, type, val;
cout << "Enter the name of variable: ";
cin >> var;
cout << "Enter the type of variable: ";
cin >> type;
cout << "Enter the value of variable: ";
cin >> val;
if(type == "int") {
regex reg(R"([-+]?\d+)");
if(regex_match(val,reg)) cout << var << " is an integer";
else cout << var << " is not an integer";
}
else if(type == "float") {
regex reg1(R"([-+]?\d+?\.?\d+f?)");
if(regex_match(val,reg1)) cout << var << " is a floating point decimal";
else cout << var << " is not a floating point decimal";
}
else if(type == "double") {
regex reg2(R"([-+]?\d+?\.?\d+([eE][-+]?\d+)?)");
if(regex_match(val,reg2)) cout << var << " is a double value";
else cout << var << " is not a double value";
}
else if(type == "char") {
regex reg3(R"('([^'\\]|\\.)')");
if(regex_match(val,reg3)) cout << var << " is a character";
else cout << var << " is not a character";
}
else if(type == "string") {
regex reg4(R"("([^"\\]|\\.)*")");
if(regex_match(val,reg4)) cout << var << " is a string";
else cout << var << " is not a string";
}
else if(type == "bool") {
if(val == "true" || val == "false") cout << var << " is a boolean value";
else cout << var << " is not a boolean value";
}
else {
cout << "Undefined datatype";
}
cout << endl;
}
}