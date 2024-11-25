#include <bits/stdc++.h>
using namespace std;

int main() 
{
    string st;
    cout << "Enter the expression :";
    cin >> st;  
    
    vector<int> nums;
    string op = "";
    string num = "";
    
    for (int i = 0; i < st.size(); i++) 
    {
        if (isdigit(st[i])) 
        {
            num += st[i];  
        } 
        else 
        {
            if (!num.empty()) 
            {
                nums.push_back(stoi(num)); 
                num = "";  
            }
            if (st[i] == '>' || st[i] == '<' || st[i] == '=' || st[i] == '!') 
            {
                op += st[i];  
            }
        }
    }
    
    if (!num.empty()) 
    {
        nums.push_back(stoi(num));  
    }

    if (op == ">") 
    {
        if (nums[0] > nums[1]) 
        {
            cout << "Valid" << endl;
        } 
        else 
        {
            cout << "Invalid" << endl;
        }
    } 
    else if (op == "<") 
    {
        if (nums[0] < nums[1]) 
        {
            cout << "Valid" << endl;
        } 
        else 
        {
            cout << "Invalid" << endl;
        }
    } 
    else if (op == "==") 
    {
        if (nums[0] == nums[1]) 
        {
            cout << "Valid" << endl;
        } 
        else 
        {
            cout << "Invalid" << endl;
        }
    } 
    else if (op == "!=") 
    {
        if (nums[0] != nums[1]) 
        {
            cout << "Valid" << endl;
        } 
        else 
        {
            cout << "Invalid" << endl;
        }
    } 
    else 
    {
        cout << "Error: Invalid expression" << endl;
    }

    return 0;
}
