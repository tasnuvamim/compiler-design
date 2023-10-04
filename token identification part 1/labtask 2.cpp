#include<iostream>

using namespace std;


int main()

{
    string s;
    cin>>s;
    string b;

    for(int i=0;i<s.size();i++)

    {
         if(s[i]>='0' &&s[i]<='9'||s[i]>='a'&&s[i]<='z')

         {

         }
         else
         {
             b.push_back(s[i]);
         }
    }
    cout<<b;
}
