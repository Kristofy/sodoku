#ifndef SODOKU_H
#define SODOKU_H

#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>


#define boxIndex(i,k) (i/3)*3+((k/3)%3)

struct fast_bitset {
    private:
        int bits;
    public: 
        fast_bitset() {}
        fast_bitset(int x) :bits(x) {}

        int count() const { return __builtin_popcount(bits); }
        int first() const { return __builtin_ctz(bits); }   
        int getBits() const { return bits; }
        
        bool operator[](int i) const { return (bits&(1<<i)) != 0; }
        bool any() const { return bits != 0; }
        bool none() const { return bits == 0; }

        void set(int i) { bits |= 1<<i; }
        void unset(int i) { bits &= ~(1<<i); }
        void flip(int i) { bits ^= 1<<i; }


        fast_bitset operator&(const fast_bitset& other) const { return bits & other.bits; }
};

class Sodoku
{
    using bitset = fast_bitset;

    public:
        Sodoku();
        Sodoku(std::string path);

        bool isDone();

        void printArray();
        void solve();

    private:

        static std::vector<int> getNumFromBitset(const bitset& convertable);

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
        int onlyInRow(int i) const;
        int onlyInColumn(int i);

        int fields[9][9];
        bitset rows[9];
        bitset cols[9];
        bitset boxes[9];
};

#endif // SODOKU_H
