#include <bits/stdc++.h>
using namespace std;

class Assembler{
    private:


    public:
    
    Assembler(){
        
    }
}


int main()
{

    int inp;

    while (1)
    {
        cout << "\t\t1. Assemble new program\n";
        cout << "\t\t2. Exit\n\n";
        cout << "\t\tEnter your choice\t:\t";
        cin >> inp;
        if (inp == 2)
            break;
        switch (inp)
        {
        case 1: //assemble
            break;
        default:
            cout << "\t\tInvalid Input\n\n";
        }
    }

    return 0;
}