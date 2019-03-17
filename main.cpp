#include <iostream>
#include "sodoku.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"made by Osztopani Kristof"<<endl;
    string path;
    //cout<<"argc: "<<argc<<endl;
    if(argc==1){
    cout<<"Please give the path and the extension(.txt) : ";
    cin>>path;
    }else{
        path=argv[1];
      // cout<<"path: "<<path<<endl;
    }
    Sodoku sodoku(path);
    sodoku.printArray();
    sodoku.solve();
    cout<<endl;
    sodoku.printArray();
    return 0;
}
