#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

bool isprime(int x)
{
	for(int i = 2; i * i <= 150; i++)
		if(x % i == 0) 
			return false;
	return true;
}

bool ans[1005];

int main()
{
	ans[2] = ans[3] = ans[5] = ans[7] = ans[13] = ans[17] = ans[19] = ans[31] = ans[61] = ans[89] = ans[107] = ans[127] = 1;
	int n;
	scanf("%d", &n);
	while(n)
	{
		printf("%d:", n);
		if(ans[n])
			puts("Prime");
		else
			puts("NotPrime");
		scanf("%d", &n);
	}
	return 0;
}
