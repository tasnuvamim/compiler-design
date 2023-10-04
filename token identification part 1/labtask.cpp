#include<iostream>
using namespace std;

void checkNum(string s)
{


bool check=true;
    for( int i=0;i<s.size();i++)
    {
        if(s[i]>='0' &&s[i]<='9' )
        {
           check =true ;
           //cout<<"the num is numeric"<<endl;
        }

        else
        {
            check=false;
            break;
           // cout<<"the num is not numeric"<<"\n";
        }
    }
            if(check==true)
            {
                cout<<"numeric"<<endl;
            }
            else
            {
                cout<<"not numeric";
            }
    }
    int main()

    {
        string s;
        cin>>s;
        checkNum(s);

        return 0;

    }
