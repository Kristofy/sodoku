#ifndef SODOKU_H
#define SODOKU_H

#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <tuple>



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

        void printArray() const;
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

        void guessNumber(int y, int x, int number) {
            if(!canGo(y, x, number)) {
                std::cerr << "Error! Number missplaced!" << std::endl;
                std::cerr << "Tried to place " << number << " at " << y + 1 << " "  << x + 1 << std::endl;
                printArray();
                std::cout << std::flush;
                abort();
            }

            auto[o, i] = boxTransform(y, x);

            fields[y][x] = number;

            row_positions[y].unset(x);
            col_positions[x].unset(y);
            box_positions[o].unset(i);

            rows[y].unset(number-1);
            cols[x].unset(number-1);
            boxes[o].unset(number-1);

            guessed = true;
        }

        // it's both the transform and the inverse transform from box to coordinate space
        static std::tuple<int, int> boxTransform(int i, int j) {
            return {i / 3 * 3 + j / 3, i % 3 * 3 + j % 3};
        }

        const Sodoku& save() {
            return (*this);
        }


        bool guessed = false;
        int fields[9][9];
        bitset row_positions[9];
        bitset col_positions[9];
        bitset box_positions[9];
        bitset rows[9];
        bitset cols[9];
        bitset boxes[9];
};

#endif // SODOKU_H
