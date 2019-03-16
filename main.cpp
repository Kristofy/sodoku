#include <iostream>
#include "sodoku.h"

using namespace std;

int main()
{
    string path;
    cout<<"made by Osztopani Kristof"<<endl;
    cout<<"Please give the path and the extension(.txt) : ";
    cin>>path;
    Sodoku sodoku(path);
    sodoku.printArray();
    sodoku.solve();
    cout<<endl;
    sodoku.printArray();
    return 0;
}
