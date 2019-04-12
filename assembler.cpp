#include <bits/stdc++.h>
using namespace std;

inline bool fileExists(const std::string &name)
{
    ifstream f(name.c_str());
    return f.good();
}

class Assembler
{
  private:
    map<string, string> OPTAB;
    map<string, pair<int, list<int>>> SYMTAB;
    string src_file_name;
    string symtab_file_name;
    string optab_file_name;
    string object_file_name;
    string header_record;
    string end_record;
    string program_name;
    int starting_address;
    int LOCCTR;

  public:
    Assembler(string src, string optab, string symtab, string obj);
    void displaySourceCode();
    void displayOptab();
    void displayObjectCode();
    void populateOPTAB();
    void generateObjectCode();
    vector<string> tokenize(string str);
};

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
    return;
}

void Assembler::generateObjectCode()
{
    ifstream sourceFile(src_file_name.c_str());

    sourceFile.close();
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