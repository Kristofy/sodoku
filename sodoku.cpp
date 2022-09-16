#include "sodoku.h"

using namespace std;

void Sodoku::solve()
{
    guessed = true;
    while(guessed) {
        guessed = false;
        guessed = possibleRow()
        || possibleColumn()
        || possibleBox()
        || onlyThere()
        || nowhereElseInRow()
        || nowhereElseInColumn()
        || nowhereElseInBox();
    }
}

bool Sodoku::nowhereElseInRow()
{
    vector<int> nums;
    int only=0;
    int index=0;
    for(int i=0; i<9; ++i)
    {
        nums=getNumFromBitset(rows[i]);
        for(int j=0; j<nums.size(); ++j)
        {
            for(int k=0; k<9; ++k)
            {
              if(fields[i][k]==0){
                if(canGo(i,k,nums[j]))
                {
                    index=k;
                    ++only;
                    if(only>1)
                    {
                        break;
                    }
                }
              }
            }
            if(only==1)
            {
                guessNumber(i, index, nums[j]);
                return true;
            }
            only=0;
        }
        nums.clear();
    }
    return guessed;
}

bool Sodoku::nowhereElseInBox()
{
    vector<int> nums;
    int only=0;
    int indexI=0;
    int indexK=0;
    for(int i=0; i<9; ++i)
    {
        nums=getNumFromBitset(boxes[i]);
        for(int j=0; j<nums.size(); ++j)
        {
            for(int k=0; k<9; ++k)
            {
                ///fields[(mi/3)+(index/3)*3][(mi%3)+(index%3)*3]
               /// cout<<"i: "<<(k/3)+((i/3)*3)<<" k: "<<(k%3)+((i%3)*3)<<endl;
                if(fields[(k/3)+((i/3)*3)][(k%3)+((i%3)*3)]==0){
                  if(canGo((k/3)+((i/3)*3),(k%3)+((i%3)*3),nums[j]))
                  {
                      indexI=(k/3)+((i/3)*3);
                      indexK=(k%3)+((i%3)*3);
                      ++only;
                      if(only>1)
                      {
                          break;
                      }
                  }
                }
            }
            if(only==1)
            {
                guessNumber(indexI, indexK, nums[j]);
                return true;
            }
            only=0;
        }
        nums.clear();
    }
    return guessed;
}

bool Sodoku::nowhereElseInColumn()
{
    vector<int> nums;
    int only=0;
    int index=0;
    for(int i=0; i<9; ++i)
    {
        nums=getNumFromBitset(cols[i]);
        for(int j=0; j<nums.size(); ++j)
        {
            for(int k=0; k<9; ++k)
            {
              if(fields[k][i]==0){
                if(canGo(k,i,nums[j]))
                {
                    index=k;
                    ++only;
                    if(only>1)
                    {
                        break;
                    }
                }
              }
            }
            if(only==1)
            {
                guessNumber(index, i, nums[j]);
                return true;
            }
            only=0;
        }
        nums.clear();
    }
    return guessed;
}

bool Sodoku::canGo(int i,int k, int value)
{
    if(fields[i][k]!=0)
    {
        return false;
    }
    for(int mi=0; mi<9; ++mi)
    {
        if(fields[mi][k]==value)
        {
            return false;
        }
    }
    for(int mk=0; mk<9; ++mk)
    {
        if(fields[i][mk]==value)
        {
            return false;
        }
    }

    auto[index, _] = boxTransform(i,k);
    for(int mi=0; mi<9; ++mi)
    {
        //  cout<<"fields value:: "<<(mi/3)+(index/3)*3<<" "<<(mi%3)+(index%3)*3<<" "<<fields[(mi/3)+(index/3)*3][(mi%3)+(index%3)*3]<<endl;
        if(fields[(mi/3)+(index/3)*3][(mi%3)+(index%3)*3]==value)
        {
            return false;
        }
    }

    return true;

}

vector<int> Sodoku::getNumFromBitset(const bitset& convertable)
{
    vector<int> v;
    for(int i=0; i<9; ++i)
    {
        if(convertable[i])
        {
            v.push_back(i+1);
        }
    }
    return v;
}

bool Sodoku::onlyThere()
{
    int possibilities=0;
    bool only;
    int guess=0;
    for(int i = 0; i < 9; i++) {
        for(int k = 0; k < 9; k++) {
            if(fields[i][k] == 0) {
                fast_bitset possibilities = rows[i]&cols[k]&boxes[get<0>(boxTransform(i,k))];
                if(possibilities.count() == 1) {
                    int guess = possibilities.first() + 1;
                    guessNumber(i, k, guess);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Sodoku::possibleBox()
{
    for(int i=0; i<9; i++) {
        int guess = onlyInBox(i);
        if(guess) {
            auto[y, x] = boxTransform(i, box_positions[i].first());
            guessNumber(y, x, guess);
            return true;
        }
    }
    return false;
}

int Sodoku::onlyInBox(int i)
{
    return boxes[i].count() == 1 ? boxes[i].first() + 1 : 0;
}


bool Sodoku::possibleRow()
{
    for(int i=0; i<9; i++) {
        int guess=onlyInRow(i);
        if(guess) {
            guessNumber(i, row_positions[i].first(), guess);
            return true;
        }
    }
    return false;
}

bool Sodoku::possibleColumn()
{
    for(int i=0; i<9; i++) {
        int guess=onlyInColumn(i);
        if(guess) {
            guessNumber(col_positions[i].first(), i, guess);
            return true;
        }
    }
    return false;
}

void Sodoku::update()
{
    for(int i=0; i<9; ++i)
    {
        for(int k=0; k<9; ++k)
        {
            if(fields[i][k]!=0)
            {
                auto[outer, inner] = boxTransform(i, k);

                row_positions[i].unset(k);
                col_positions[k].unset(i);
                box_positions[outer].unset(inner);
                rows[i].unset(fields[i][k]-1);
                cols[k].unset(fields[i][k]-1);
                boxes[outer].unset(fields[i][k]-1);
            }
        }
    }
}

bool Sodoku::isDone(){
    for(int i=0; i<9; ++i)
    {
        for(int k=0; k<9; ++k)
        {
            for(int j=0;j<9;++j){
                if((fields[i][k]==fields[i][j]&&k!=j)&&fields[i][k]!=0){
                    return false;
                }
                if((fields[k][i]==fields[j][i]&&k!=j)&&fields[i][k]!=0){
                    return false;
                }
            }
        }
    }
    return true;
}

int Sodoku::onlyInColumn(int i)
{
    return cols[i].count() == 1 ? cols[i].first() + 1 : 0; 
}

int Sodoku::onlyInRow(int i) const {
    return rows[i].count() == 1 ? rows[i].first() + 1 : 0;
}

Sodoku::Sodoku() {
    for(int i=0; i<9; ++i)
       rows[i]=cols[i]=boxes[i]=row_positions[i]=col_positions[i]=box_positions[i]=0b111111111;
}

Sodoku::Sodoku(string path)
{
    for(int i=0; i<9; ++i)
        rows[i]=cols[i]=boxes[i]=row_positions[i]=col_positions[i]=box_positions[i]=0b111111111;


    ifstream fin(path);
    if(!fin.is_open())
    {
        cout<<"Error!\nFailed to open the file!"<<endl;
        for(int j=0; j<9; ++j)
        {
            for(int k=0; k<9; ++k)
            {
                fields[j][k]=0;
            }
        }
        return;
    }
    int i;
    for(i=0; i<81&&!fin.eof(); ++i)
    {
        fin>>fields[i/9][i%9];
        if(fields[i/9][i%9]>9||fields[i/9][i%9]<0)
        {
            cout<<"Error!\nLoading file failed!\nInvalid character found!"<<endl;
            for(int j=0; j<9; ++j)
            {
                for(int k=0; k<9; ++k)
                {
                    fields[j][k]=0;
                }
            }
            fin.close();
            return;
        }

    }
    if(i!=81)
    {
        cout<<"Error!\nLoading file failed!\nTo few characters!\n 0x"<<i<<endl;
        for(int i=0; i<9; ++i)
        {
            for(int k=0; k<9; ++k)
            {
                fields[i][k]=0;
            }
        }
        fin.close();
        return;
    }
    if(!fin.eof())
    {
        cout<<"Error!\nLoading file failed!\nTo many characters in the file!"<<endl;
        for(int i=0; i<9; ++i)
        {
            for(int k=0; k<9; ++k)
            {
                fields[i][k]=0;
            }
        }
    }
    fin.close();
   
    for(int i=0; i<9; ++i)
    {
        for(int k=0; k<9; ++k)
        {
            if(fields[i][k]!=0)
            {
                auto[outer, inner] = boxTransform(i, k);

                row_positions[i].unset(k);
                col_positions[k].unset(i);
                box_positions[outer].unset(inner);
                rows[i].unset(fields[i][k]-1);
                cols[k].unset(fields[i][k]-1);
                boxes[outer].unset(fields[i][k]-1);
            }
        }
    }
}

void Sodoku::printArray() const
{
    cout<<"-------------------------------"<<endl;
    for(int i=0; i<9; ++i)
    {
        cout<<"|";
        for(int k=0; k<9; ++k)
        {
            cout<<" "<<fields[i][k]<<" ";
            if((k+1)%3==0)
            {
                cout<<"|";
            }
        }
        cout<<endl;
        if((i+1)%3==0)
        {
            cout<<"-------------------------------"<<endl;
        }
    }
}
