#include <bits/stdc++.h>
using namespace std;

class Assembler{
    private:


    public:
    
    Assembler(){

    }
};


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
        case 1: //assemble
            break;
        default:
            cout << "\n\t\tInvalid Input\n\n";
            system("sleep 1");
        }
    }

    return 0;
}