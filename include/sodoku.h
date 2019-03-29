#ifndef SODOKU_H
#define SODOKU_H

#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>


#define LG if(LOG) // if log is on write how it was solved
#define boxIndex(i,k) (i/3)*3+((k/3)%3)

using namespace std;

extern bool LOG;

vector<int> getNumFromBitset(const bitset<9>& convertable);

class Sodoku
{
    public:
        Sodoku();
        Sodoku(string path);

        bool isDone();

        void printArray();
        void solve();

    private:

        friend vector<int> getNumFromBitset(const bitset<9>& convertable);

        bool possibleRow();
        bool possibleColumn();
        bool possibleBox();

        bool onlyThere();
        bool nowhereElseInRow();
        bool nowhereElseInColumn();
        bool nowhereElseInBox();

        bool canGo(int i,int k, int value);
        void update();

        int onlyInBox(int i);
        int onlyInRow(int i);
        int onlyInColumn(int i);

        int fields[9][9];
        bitset<9> rows[9];
        bitset<9> cols[9];
        bitset<9> boxes[9];
};

#endif // SODOKU_H
