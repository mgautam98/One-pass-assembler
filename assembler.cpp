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
    string src_file_name;
    string symtab_file_name;
    string optab_file_name;
    string object_file_name;

  public:
    Assembler(string src, string optab, string symtab, string obj);
    void displaySourceCode();
    void displayOptab();
    void displayObjectCode();
};


Assembler::Assembler(string src, string optab, string symtab, string obj)
{
    src_file_name = src;
    symtab_file_name = symtab;
    optab_file_name = optab;
    object_file_name = obj;
    if (!fileExists(src_file_name) || !fileExists(optab_file_name))
    {
        cout << "\n\t\t SOURCE FILE OR OPTAB DOESN'T EXISTS\n\n";
        system("sleep 3");
    }
}

void Assembler::displaySourceCode(){
    ifstream ifs(src_file_name.c_str());
	for(string line; getline(ifs, line);)
		cout<<line<<endl;
	return;
}

void Assembler::displayOptab(){
    ifstream ifs(optab_file_name.c_str());
	for(string line; getline(ifs, line);)
		cout<<line<<endl;
	return;
}

void assembleNewProgram()
{
    string src, optab, object, symtab;
    cout << "\n\t\tSource File Name  :  ";
    cin >> src;
    cout << "\t\tOPTAB file Name  :  ";
    cin >> optab;
    cout << "\t\tFile name where Object Code will be stored  :  ";
    cin >> object;
    symtab = "symtab.txt";
    Assembler(src, optab, symtab, object);
}

int main()
{
    system("chmod +x menu.sh");
    int inp;

    while (1)
    {
        system("./menu.sh");
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