#include <bits/stdc++.h>
using namespace std;
class BigInt
{
	string num;
	BigInt();
	BigInt(string s);
	BigInt(long long int s);
};
BigInt::BigInt()
{
	num="0";
}
BigInt::BigInt(string s)
{
	num=s;
}
BigInt::BigInt(long long int n) 
{
	stringstream ss;
	ss<<n;
	num=ss.str();
}
int main()
{
	return 0;
}