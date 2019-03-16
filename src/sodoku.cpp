#include "sodoku.h"

void Sodoku::solve()
{
    while(true)
    {
        update();
        //printArray();
        //system("pause")
        if(possibleRow()){
            continue;
        }
        if(possibleColumn()){
            continue;
        }
        if(possibleBox()){
            continue;
        }
        if(onlyThere()){
            continue;
        }
        if(nowhereElseInRow()){
            continue;
        }
        if(nowhereElseInColumn())
        {
            continue;
        }

        if(nowhereElseInBox())
        {
            continue;
        }
        break;
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
                fields[i][index]=nums[j];
                cout<<"guess in nowhereElseInRow: "<<nums[j]<<endl;
                return true;
            }
            only=0;
        }
        nums.clear();
    }
    return false;
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
                fields[indexI][indexK]=nums[j];
                cout<<"guess in nowhereElseInBox: "<<nums[j]<<endl;
                return true;
            }
            only=0;
        }
        nums.clear();
    }
    return false;
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
                fields[index][i]=nums[j];
                cout<<"guess in nowhereElseInColumn: "<<nums[j]<<endl;
                return true;
            }
            only=0;
        }
        nums.clear();
    }
    return false;
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
    int index = boxIndex(i,k);
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

vector<int> getNumFromBitset(const bitset<9>& convertable)
{
    vector<int> v;
    for(int i=0; i<9; ++i)
    {
        if(convertable.to_ulong()&(1<<i))
        {
            v.push_back(i+1);
        }
    }
    return v;
}

bool Sodoku::onlyThere()
{
    unsigned long possibilities=0;
    bool only;
    int guess=0;
    for(int i=0; i<9; ++i)
    {
        for(int k=0; k<9; ++k)
        {
            if(fields[i][k]==0)
            {
                possibilities=((rows[i]&cols[k])&boxes[boxIndex(i,k)]).to_ulong();
                if(possibilities)
                {
                    only=true;
                    for(int j=0; j<9; ++j)
                    {
                        if(possibilities&(1<<j))
                        {
                            if(only)
                            {
                                guess=j+1;
                                only=false;
                            }
                            else
                            {
                                guess=0;
                                break;
                            }
                        }
                    }
                    if(guess)
                    {
                        if(canGo(i,k,guess))
                        {
                            cout<<"guess in onlyThere: "<<guess<<endl;
                            fields[i][k]=guess;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;


}

bool Sodoku::possibleBox()
{
    int guess;
    for(int i=0; i<9; i++)
    {
        guess=onlyInBox(i);
        if(guess)
        {
            for(int k=0; k<9; ++k)
            {
                ///if(fields[(mi/3)+(index/3)*3][(mi%3)+(index%3)*3]
                ///I dont think so
                if(fields[((i/3)*3)+k/3][((i%3)*3)+k%3]==0&&canGo((((i/3)*3)+k/3),((i%3)*3)+k%3,guess))
                {
                    fields[((i/3)*3)+k/3][((i%3)*3)+k%3]=guess;
                    cout<<"guess in possibeBox: "<<guess<<endl;
                    return true;
                }
            }
            break;
        }
    }
    return false;
}

int Sodoku::onlyInBox(int i)
{
    bool only=true;
    int guess;
    for(int k=0; k<9; ++k)
    {
        if(boxes[i][k])
        {
            if(only)
            {
                guess=k+1;
                only=false;
            }
            else
            {
                guess=0;
                break;
            }
        }
    }
    return guess;
}

bool Sodoku::possibleRow()
{
    int guess;
    for(int i=0; i<9; i++)
    {
        guess=onlyInRow(i);
        if(guess)
        {
            for(int k=0; k<9; ++k)
            {
                ///I dont think so
                if(fields[i][k]==0&&canGo(i,k,guess))
                {
                    fields[i][k]=guess;
                    cout<<"guess in possibeRow: "<<guess<<endl;
                    return true;
                }
            }
        }
    }
    return false;
}
bool Sodoku::possibleColumn()
{
    int guess;
    for(int i=0; i<9; i++)
    {
        guess=onlyInColumn(i);
        if(guess)
        {
            for(int k=0; k<9; ++k)
            {
                ///Replace
                if(fields[k][i]==0&&canGo(k,i,guess))
                {
                    fields[k][i]=guess;
                    cout<<"guess in possibeColumn: "<<guess<<endl;
                    return true;
                }
            }
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
                rows[i][fields[i][k]-1]=0;
                cols[k][fields[i][k]-1]=0;
                boxes[boxIndex(i,k)][fields[i][k]-1]=0;
            }
        }
    }
}
int Sodoku::onlyInColumn(int i)
{
    bool only=true;
    int guess=0;
    for(int k=0; k<9; ++k)
    {
        if(cols[i][k])
        {
            if(only)
            {
                guess=k+1;
                only=false;
            }
            else
            {
                guess=0;
                break;
            }
        }
    }
    return guess;
}

int Sodoku::onlyInRow(int i)
{
    bool only=true;
    int guess=0;
    for(int k=0; k<9; ++k)
    {
        if(rows[i][k])
        {
            if(only)
            {
                guess=k+1;
                only=false;
            }
            else
            {
                guess=0;
                break;
            }
        }
    }
    return guess;
}

Sodoku::Sodoku()
{
    for(int i=0; i<9; ++i)
    {
        rows[i]=0b111111111;
        cols[i]=0b111111111;
        boxes[i]=0b111111111;
    }
}

Sodoku::Sodoku(string path)
{
    for(int i=0; i<9; ++i)
    {
        rows[i]=0b111111111;
        cols[i]=0b111111111;
        boxes[i]=0b111111111;
    }
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
}

void Sodoku::printArray()
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
