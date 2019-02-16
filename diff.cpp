#include<bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin>>n;

  string s;
  cin>>s;

  int f[26]={0};

  for(int i=0;i<n;i++)
   f[s[i]-97]=1;

  int sum=0;

   for(int i=0;i<26;i++)
    sum=sum+f[i];

  if(n>26)
   cout<<-1;

  else if((n-sum)>=26)
   cout<<-1;

  else
  cout<<(n-sum);

  return 0;
}
