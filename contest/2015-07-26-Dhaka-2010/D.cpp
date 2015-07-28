#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int dx[] = {0, -1, 1, 0, 0};
const int dy[] = {0, 0, 0, -1, 1};
const int MAXN = 1000000;
struct Point {
	int x, y, id;
}po[10], recover[10];



int where[200];
int mypow[10];
int obstacle[11][11];
int marked[3000], q[MAXN];
char row[11][11];
int occur[64*64*64*64+10];

int getpos(int x,int y) {
	return (x - 1) * 8 + y;
}
int getx(int k) {
	return k / 8 + (k % 8 > 0);
}
int gety(int k) {
	if (k % 8 == 0) return 8;
	return k % 8;
}
bool cmp1(Point p1, Point p2){
	return p1.x < p2.x;
}
bool cmp2(Point p1, Point p2){
	return p1.x > p2.x;
}
bool cmp3(Point p1, Point p2){
	return p1.y < p2.y;
}
bool cmp4(Point p1, Point p2){
	return p1.y > p2.y;
}
int can_go(int nx, int ny ,int dir) {
	//cout<< nx <<" "<< ny <<" "<<dir << endl;
	if (dir == 1) {
		nx += dx[dir];
		ny += dy[dir];
		if (obstacle[nx][ny] == 1 || obstacle[nx][ny + 1] == 1) return 0;
		return 1;
	}
	if (dir == 2) {
		nx += dx[dir];
		ny += dy[dir];
		if (obstacle[nx + 1][ny] == 1 || obstacle[nx + 1][ny + 1] == 1) return 0;
		return 1;		
	}
	if (dir == 3) {
		nx += dx[dir];
		ny += dy[dir];
		if (obstacle[nx][ny] == 1 || obstacle[nx + 1][ny] == 1) return 0;
		return 1; 		
	}
	if (dir == 4) {
		nx += dx[dir];
		ny += dy[dir];
		if (obstacle[nx][ny + 1] == 1 || obstacle[nx + 1][ny + 1] == 1) return 0;
		return 1;
	}
}
void solve(int test) {
	int first_state = 0;
	mypow[0] = 1;
	for (int i = 1; i <= 4; i++)
		mypow[i] = mypow[i - 1] * 64;
	
	where['A'] = 0;
	where['B'] = 1;
	where['C'] = 2;
	where['D'] = 3;
	
	for (int i  = 0 ;i <= 9; i++)
		for (int j = 0; j <= 9; j++)
			obstacle[i][j] = 1;
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
			obstacle[i][j] = 0;	
			
			
			
	memset(marked, 0 , sizeof marked);
	
	
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (row[i][j] == '#') 
			{
				obstacle[i][j] = 1;
				continue;
			}
			if (row[i][j] != '.'&& !marked[row[i][j]]) {
				first_state += getpos(i,j) * mypow[where[row[i][j]]];
				marked[row[i][j]] = 1;
			}
			if (row[i][j] == '.') obstacle[i][j] = 0;
		}
	}
	//occur[first_state] = test;
	
	int l = 0, r = 1;
	q[1] = first_state;
	while (l < r) {
		int now_state = q[++l];
		int p = now_state;
		int cnt = 0;
		while (p) {
			int tmp = p % 64;
			p /= 64;
			++cnt;
			po[cnt].x = getx(tmp);
			po[cnt].y = gety(tmp);
			po[cnt].id = cnt;
		}
		for (int direction = 1; direction <= 4; direction++) {
			if (direction == 1)	{
				sort(po + 1, po + 5, cmp1);
			}
			if (direction == 2) {
				sort(po + 1, po + 5, cmp2);
			}
			if (direction == 3) {
				sort(po + 1, po + 5, cmp3);
			}
			if (direction == 4) {
				sort(po + 1, po + 5, cmp4);
			}
			
			for (int i = 1; i <= 4; i++) {
					int nx = po[i].x, ny = po[i].y;
					while (can_go(nx, ny, direction)) 
					{
						nx += dx[direction];
						ny += dy[direction];
					}
					recover[po[i].id].x = nx;
					recover[po[i].id].y = ny;
					for (int xx = nx; xx <= nx + 1; xx++)
						for (int yy = ny; yy <= ny + 1; yy++)
							obstacle[xx][yy] = 1;
				}
			for (int i = 1; i <= 4; i++) {
				int nx = recover[i].x, ny = recover[i].y;
				for (int xx = nx; xx <= nx + 1; xx++)
					for (int yy = ny; yy <= ny + 1; yy++)
						obstacle[xx][yy] = 0;
			}
			
			int new_state = 0;
			
			for (int i = 1; i <= 4; i++)
				new_state += getpos(recover[i].x, recover[i].y) * mypow[i - 1];
			if (occur[new_state] != test) {
				q[++r] = new_state;
				occur[new_state] = test;				
			}
					
		}
	}
	printf("%d\n", r - 1);
}
int main() {
	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; tt++) {
		for (int i = 1; i <= 8; i++) {
			scanf("%s", row[i] + 1);
		}
		printf("Case %d: ",tt);
		solve(tt);
	}
}

