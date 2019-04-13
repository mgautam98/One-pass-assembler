#ifdef __unix__

#define OS_Windows 0
#include <bits/stdc++.h>

#elif defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <utility>
#include <stack>
#include <queue>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <math.h>

#endif

using namespace std;

inline bool fileExists(const string &name)
{
    ifstream f(name.c_str());
    return f.good();
}

class Assembler
{
  private:
    map<string, string> OPTAB;
    map<string, pair<int, list<int>>> SYMTAB;
    map<int, vector<string>> records;
    string src_file_name;
    string symtab_file_name;
    string optab_file_name;
    string object_file_name;
    string header_record;
    string end_record;
    string program_name;
    int starting_address;
    int ending_address;
    int first_executable_instruction;
    int LOCCTR;

  public:
    Assembler(string src, string optab, string symtab, string obj);
    void displaySourceCode();
    void displayOptab();
    void displayObjectCode();
    void populateOPTAB();
    void generateObjectCode();
    vector<string> tokenize(string str);
    int hexToDec(string s);
    string decToHex(int a);
    string hexToBin(string s);
};

int Assembler::hexToDec(string s)
{
    int dval = 0;
    int a;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0')
            a = 0;
        if (s[i] == '1')
            a = 1;
        if (s[i] == '2')
            a = 2;
        if (s[i] == '3')
            a = 3;
        if (s[i] == '4')
            a = 4;
        if (s[i] == '5')
            a = 5;
        if (s[i] == '6')
            a = 6;
        if (s[i] == '7')
            a = 7;
        if (s[i] == '8')
            a = 8;
        if (s[i] == '9')
            a = 9;
        if (s[i] == 'A')
            a = 10;
        if (s[i] == 'B')
            a = 11;
        if (s[i] == 'C')
            a = 12;
        if (s[i] == 'D')
            a = 13;
        if (s[i] == 'E')
            a = 14;
        if (s[i] == 'F')
            a = 15;
        dval = a + dval * 16;
    }
    return dval;
}
string Assembler::decToHex(int a)
{
    string hexlist = "0123456789ABCDEF";
    string hstr = "";
    while (a)
    {
        hstr = hexlist[a % 16] + hstr;
        a /= 16;
    }
    return hstr;
}

string Assembler::hexToBin(string s)
{
    string htb;
    for (auto i : s)
    {
        int n;
        if (i <= '9' and i >= '0')
            n = i - '0';
        else
            n = 10 + i - 'A';
        for (int j = 3; j >= 0; --j)
            htb.push_back((n & (1 << j)) ? '1' : '0');
    }
    return htb;
}

vector<string> Assembler::tokenize(string str)
{
    vector<string> tokens;
    string element;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ' && element.length() != 0)
        {
            tokens.push_back(element);
            element.clear();
        }
        else if (str[i] != ' ')
        {
            element += string(1, str[i]);
        }
    }
    if (element.length() != 0)
    {
        tokens.push_back(element);
    }
    return tokens;
}

Assembler::Assembler(string src, string optab, string symtab, string obj)
{
    src_file_name = src;
    symtab_file_name = symtab;
    optab_file_name = optab;
    object_file_name = obj;
    populateOPTAB();
    generateObjectCode();
}

void Assembler::displaySourceCode()
{
    ifstream file(src_file_name.c_str());
    cout << endl;
    cout << "\t\t================================================\n";
    for (string line; getline(file, line);)
    {
        cout << "\t\t" << line << endl;
    }
    cout << "\n\t\t================================================\n";
    file.close();
    return;
}

void Assembler::displayOptab()
{
    cout << endl;
    cout << "\t\t================================================\n";
    for (auto i : OPTAB)
    {
        cout << "\t\t" << i.first << "\t\t:\t\t" << i.second << endl;
    }
    cout << "\n\t\t================================================\n";
    return;
}

void Assembler::displayObjectCode()
{
    ifstream file(object_file_name.c_str());
    cout << endl;
    cout << "\t\t================================================\n";
    for (string line; getline(file, line);)
        cout << "\t\t" << line << endl;
    cout << "\n\t\t================================================\n";
    file.close();
    return;
}

void Assembler::populateOPTAB()
{
    ifstream file(optab_file_name.c_str());
    for (string line; getline(file, line);)
    {
        vector<string> tokens = tokenize(line);
        if (OPTAB.find(tokens[0]) == OPTAB.end())
        {
            OPTAB.insert({tokens[0], tokens[1]});
        }
        else
        {
            cout << "\n\t\tDuplicate OPCODE! Exiting\n\n";
            exit(0);
        }
    }
    file.close();
    return;
}

void Assembler::generateObjectCode()
{
    bool firstLine = true;
    string label, opcode, operand;
    ifstream sourceFile(src_file_name.c_str());

    for (string line; getline(sourceFile, line);)
    {
        vector<string> tokens = tokenize(line);

        //For First line of program
        if (firstLine)
        {
            firstLine = false;
            program_name = tokens[0].substr(0, 6);

            if (tokens.size() == 3)
            {
                if (tokens[1].compare(string("START")) == 0)
                {
                    LOCCTR = hexToDec(tokens[2]);
                    starting_address = LOCCTR;
                }
                else
                {
                    LOCCTR = 0;
                    starting_address = 0;
                }
            }
            else
            {
                LOCCTR = 0;
                starting_address = 0;
            }
            continue;
        }
        //FOR Last line of program
        if (tokens[0].compare("END") == 0)
        {
            ending_address = LOCCTR;
            if (tokens.size() > 1)
                first_executable_instruction = hexToDec(tokens[1]);
            else
                first_executable_instruction = starting_address;
        }

        //comment line
        if (tokens[0].compare(".") == 0)
            continue;

        if (tokens.size() == 2)
        {
            opcode = tokens[0];
            operand = tokens[1];
        }
        else if (tokens.size() == 3)
        {
            label = tokens[0];
            opcode = tokens[1];
            operand = tokens[2];
        }

        //handling label
        if (tokens.size() == 3)
        {
            if (SYMTAB.find(label) == SYMTAB.end())
            {
                SYMTAB.insert({label, pair<int, list<int>>(LOCCTR, {})});
            }
            else if (SYMTAB.find(label) != SYMTAB.end())
            {
                if (SYMTAB[label].first == -1)
                {
                    SYMTAB[label].first = LOCCTR;
                }
                else
                {
                    cout << "\n\t\tDuplicate Label\n";
                    exit(0);
                }
            }
        }

        //handling opcode
        string newRecord = "000000";
        bool indexRegister = false;

        if(operand[operand.size()-1]=='X'){
            indexRegister = true;
            operand = operand.substr(0, operand.size()-2);
        }

        if (OPTAB.find(opcode) != OPTAB.end())
        {
            newRecord.replace(0, 2, OPTAB[opcode]);
            if (SYMTAB.find(operand) != SYMTAB.end())
            {
                if (SYMTAB[operand].first != -1)
                {
                    string addressFeild = decToHex(SYMTAB[operand].first);
                    newRecord.replace(6 - addressFeild.size(), 6, addressFeild);
                }
                else
                {
                    SYMTAB[operand].second.push_back(LOCCTR);
                }
            }
            else
            {
                SYMTAB.insert({operand, pair<int, list<int>>(-1, {})});
                SYMTAB[operand].second.push_back(LOCCTR);
            }
            LOCCTR += 3;
        }
        else
        {
            if (opcode.compare(string("WORD")) == 0)
            {
                LOCCTR += 3;
            }
            else if (opcode.compare(string("RESW")) == 0)
            {
                LOCCTR += 3 * stoi(operand);
            }
            else if (opcode.compare(string("BYTE")) == 0)
            {
                if (operand[0] == 'X')
                {
                    LOCCTR++;
                }
                else
                {
                    LOCCTR += operand.length() - 3;
                }
            }
            else if (opcode.compare(string("RESB")) == 0)
            {
                LOCCTR += stoi(operand);
            }
            else
            {
                cout << "\t\tError: Opcode is not present in OPTAB\n";
                exit(0);
            }
        }
    }

    sourceFile.close();

    ofstream symout(symtab_file_name.c_str());
    for (auto it = SYMTAB.begin(); it != SYMTAB.end(); ++it)
    {
        symout << it->first << " : " << decToHex((it->second).first) << endl;
    }
    symout.close();
}

void assembleNewProgram()
{
    int inp;
    string src, optab, object, symtab;
    cout << "\n\t\tSource File Name  :  ";
    cin >> src;
    cout << "\t\tFile name where Object Code will be stored  :  ";
    cin >> object;
    symtab = "symtab.txt";
    optab = "optab.txt";
    if (!fileExists(src) || !fileExists(optab))
    {
        cout << "\n\t\t SOURCE FILE OR OPTAB DOESN'T EXISTS\n\n";
        system("sleep 3");
        return;
    }
    Assembler newProgram(src, optab, symtab, object);
    while (1)
    {
        cout << "\n\n\t\t1. Display source code\n";
        cout << "\t\t2. Display OPTAB\n";
        cout << "\t\t3. Display object code\n";
        cout << "\t\t4. Return to Main\n";
        cout << " \n\t\tEnter your choice : ";
        cin >> inp;
        if (inp == 4)
            break;
        switch (inp)
        {
        case 1:
            newProgram.displaySourceCode();
            break;
        case 2:
            newProgram.displayOptab();
            break;
        case 3:
            newProgram.displayObjectCode();
            break;

        default:
            cout << "\t\tEnter valid choice\n\n";
            break;
        }
    }
}

int main()
{
    system("chmod +x menu.sh");
    int inp;

    while (1)
    {
        system("./menu.sh");

        cout << "\t\t\t\t\t";
        cin >> inp;
        if (inp == 2)
            break;
        switch (inp)
        {
        case 1:
            assembleNewProgram();
            break;
        default:
            cout << "\n\t\tInvalid Input\n\n";
            system("sleep 1");
        }
    }

    return 0;
}
