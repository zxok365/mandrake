#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

#define N 100005

int type[N], num[N];
int stack[N],t[N];
char c[N];
int cnt = 0, top = 0;

typedef long long LL;

void ERROR()
{
	puts("ERROR");
	return ;
}

bool check(LL x)
{
	if(x > 1000000000) return true;
	if(x < -1000000000) return true;
	return false;
}

void work(int x)
{
	top = 1;
	stack[top] = x;
	for(int i = 1; i <= cnt; i++)
	{
		//printf("%d ", type[i]);
		if(type[i] == 1)
			stack[++top] = num[i];
		if(type[i] == 2)
		{
			if(top == 0) {ERROR(); return ;}
			top--;
		}
		if(type[i] == 3) stack[top] *= -1;
		if(type[i] == 4)
		{
			stack[top + 1] = stack[top];
			top++;
		}
		if(type[i] == 5)
		{
			if(top <= 1) {ERROR(); return ;}
			swap(stack[top], stack[top - 1]);
		}
		if(type[i] == 6)
		{
			if(top <= 1) {ERROR(); return ;}
			if(check((LL)stack[top] + stack[top - 1]))
			{ ERROR(); return ;}
			stack[top - 1] += stack[top];
			top--;
		}
		if(type[i] == 7)
		{
			if(top <= 1) {ERROR(); return ;}
			if(check((LL)stack[top - 1] - stack[top]))
			{ ERROR(); return ;}
			stack[top - 1] = (LL)stack[top - 1] - stack[top];
			top--;
		}
		if(type[i] == 8)
		{
			//printf("%d %d\n",stack[top], stack[top - 1]);
			//printf("%d\n",top);
			if(top <= 1) {ERROR(); return ;}
			if(check((LL)stack[top - 1] * stack[top]))
			{ ERROR(); return ;}
			stack[top - 1] *= stack[top];
			top--;
		}
		if(type[i] == 9)
		{
			if(top <= 1) {ERROR(); return ;}
			if(stack[top] == 0) { ERROR(); return ;}
			stack[top - 1] /= stack[top];
			top--;
		}
		if(type[i] == 10)
		{
			if(top <= 1) {ERROR(); return ;}
			if(stack[top] == 0) { ERROR(); return ;}
			stack[top - 1] %= stack[top];
			top--;
		}		
		//printf("%d ", i);
	}
	//puts("");
	if(top > 1 || top == 0)
	{
		ERROR();return ;
	}
	printf("%d\n", stack[top]);
	return ;
}

int main()
{	
	while(1)
	{
		cnt = 0;
		while(1)
		{
			scanf("%s",c);
			++cnt;
			if(!strcmp(c, "QUIT")) return 0;
			if(!strcmp(c, "NUM"))
				type[cnt] = 1, scanf("%d", &num[cnt]);
			if(!strcmp(c, "POP"))
				type[cnt] = 2;
			if(!strcmp(c, "INV"))
				type[cnt] = 3;
			if(!strcmp(c, "DUP"))
				type[cnt] = 4;
			if(!strcmp(c, "SWP"))
				type[cnt] = 5;
			if(!strcmp(c, "ADD"))
				type[cnt] = 6;
			if(!strcmp(c, "SUB"))
				type[cnt] = 7;
			if(!strcmp(c, "MUL"))
				type[cnt] = 8;
			if(!strcmp(c, "DIV"))
				type[cnt] = 9;
			if(!strcmp(c, "MOD"))
				type[cnt] = 10;
			if(!strcmp(c, "END"))
				break;
		}
		cnt --;
		//for(int i = 1; i <= cnt; i++)
		//	printf("%d ",type[i]);
		//puts("");
		int Q;
		scanf("%d",&Q);
		for(int i = 1; i <= Q; i++)
		{
			int p;
			scanf("%d", &p);
			work(p);
		}
		puts("");
	}
	return 0;
}
