#include<bits/stdc++.h>
#include <iomanip>
using namespace std;

struct SymbolItems {
    string type;
    int address;
    string scope;
};

class symbolTable {
    unordered_map<string, SymbolItems> table;
    int memoryAdd = 8000;

public:
    void insertSym(string sym, string type, string scope) {
        table[sym] = {type, memoryAdd++, scope};
    }

    void checkSym(string line, symbolTable &st, string scope) {
        stringstream ss(line);
        string type, symbol;

        if (ss >> type >> symbol) {
            size_t pos = symbol.find_first_of("=;");
            if (pos != string::npos) {
                symbol = symbol.substr(0, pos);
            }
            st.insertSym(symbol, type, scope);
        }
    }

    void show() {
        vector<pair<string, SymbolItems>> sortedTable(table.begin(), table.end());
        sort(sortedTable.begin(), sortedTable.end(), [](const pair<string, SymbolItems> &a, const pair<string, SymbolItems> &b) {
            return a.second.address < b.second.address;
        });

        cout << left << setw(15) << "Symbol"
             << setw(10) << "Type"
             << setw(10) << "Address"
             << setw(10) << "Scope" << endl;

        for (auto &item : sortedTable) {
            cout << left << setw(15) << item.first
                 << setw(10) << item.second.type
                 << setw(10) << item.second.address
                 << setw(10) << item.second.scope << endl;
        }
    }
};

int main() {
    symbolTable st;
    ifstream codeFile("file.cpp");
    if (!codeFile) {
        cout << "unable to read file" << endl;
        return 1;
    }

    string line;
    string scope = "global";
    int bloc = 0;

    while (getline(codeFile, line)) {
        if (line.find("{") != string::npos) {
            bloc++;
            scope = "block" + to_string(bloc);
        }
        if (line.find("}") != string::npos) {
            scope = "global";
        }
        st.checkSym(line, st, scope);
    }
    codeFile.close();
    st.show();
    return 0;
}
