#include <iostream>
#include "sodoku.h"

bool LOG=0;

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"made by Osztopani Kristof"<<endl;
    string path;
    string yesOrNo;
    switch(argc){
        case 1:
            cout<<"Please give the path and the extension(.txt):\t";
            cin>>path;
            cout<<"Should I tell you how I solved it?(y/n)\t";
            cin>>yesOrNo;
            LOG=(yesOrNo.length()==1&&yesOrNo.at(0)=='y')?1:0;

        break;
        case 2:
            path=argv[1];
        break;
        case 3:
            LOG=string(argv[1]).at(0)-48;
            path=argv[2];
        break;
        default:
            cout<<"Wrong sintax!"<<endl;
            return EXIT_FAILURE;
        break;
    }
    Sodoku sodoku(path);
    sodoku.printArray();
    sodoku.solve();
    cout<<endl;
    if(sodoku.isDone()){
        cout<<"It was too easy! :D"<<endl;
    }else{
        cout<<"Sorry! I couldn't make it. :("<<endl;
    }
    sodoku.printArray();
    return 0;
}
