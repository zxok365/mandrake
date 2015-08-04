#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define PII pair<int, int>

using namespace std;

const int N = 100;
const int dx[] = {0, 0, 0, 1, -1};
const int dy[] = {0, 1, -1, 0, 0};
struct Runins{
	int x, y, bonus;
}pos[10];


int n, m, target, ruins;
char mat[N][N];
int max_turn;
int conquered[N][N], product[N][N];
int worker_product[N * N * 2], worker[N];
int ruin_product[N * N * 2];
int order[10], dist[10][N][N];
queue<PII> Q;
vector<PII> land[N * N * 2];

void chkmax(int &x, int y) {
	if (y <= x) return;
	x = y;
}

void clear_worker() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			conquered[i][j] = -1;
			
	for (int i = 0; i <= max_turn; i++) land[i].clear();
	for (int i = 0; i <= max_turn; i++) worker_product[i] = 0;
}

void calc_worker() {
	clear_worker();
	
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++)
			if (mat[i][j] == '*') {
				Q.push(make_pair(i, j));
				conquered[i][j] = 0;
			}
	
	for(; !Q.empty(); Q.pop()) {
		PII now = Q.front();
		int nx = now.first, ny = now.second , nturn = conquered[nx][ny];
		land[nturn].push_back(make_pair(nx, ny));
		for (int d = 1; d <= 4; d++) {
			int tx = nx + dx[d];
			int ty = ny + dy[d];
			if (tx < 1 || tx > n || ty < 1 || ty > m || conquered[tx][ty] > -1 || mat[tx][ty] == 'X') continue;
			conquered[tx][ty] = nturn + 5;
			Q.push(make_pair(tx, ty));
		}
	}
	
	for (int i = 0; i <= 50; i++) worker[i] = 0;
	
	int nowsum = 0;
	int cnt = 0;
	priority_queue<int> heap;
	while (!heap.empty()) heap.pop();
	for (int turns = 0; turns <= max_turn; turns++) {
		worker_product[turns + 1] = 0;
		if (turns % 5 == 0) {
			for (int i = 0; i < (int)land[turns].size(); i++) {
				int tx = land[turns][i].first, ty = land[turns][i].second;
				heap.push(product[tx][ty]);
			}
			if (!heap.empty()) {
				int nowproduct = heap.top();
				heap.pop();
				if (nowproduct == 0) continue;
				worker[nowproduct]++;
			}
		}

		for (int i = 1; i <= 50; i++)
			if (worker[i] > 0) {
				nowsum += worker[i] * i;
				worker[i -1] += worker[i];
				worker[i] = 0;
			}
		worker_product[turns + 1] = nowsum;
	}	
}

void bfs(int start) {
	int sx = pos[start].x, sy = pos[start].y;
	Q.push(make_pair(sx, sy));
	dist[start][sx][sy] = 0;
	for (; !Q.empty(); Q.pop()) {
		PII tmp = Q.front();
		int nx = tmp.first, ny = tmp.second;
		for (int d = 1; d <= 4; d++) {
			int tx = nx + dx[d];
			int ty = ny + dy[d];
			if (tx < 1 || tx > n || ty < 1 || ty > m || mat[tx][ty] == 'X' || dist[start][tx][ty] > -1)  continue;
			dist[start][tx][ty] = dist[start][nx][ny] + 1;
			Q.push(make_pair(tx, ty));
		}
	}
}

void clear_ruin() {
	for (int i = 0; i <= 5; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= m; k++)
				dist[i][j][k] = -1;
	for (int i = 0; i <= max_turn; i++)
		ruin_product[i] = 0;
}


void calc_ruin() {
	clear_ruin();
	for (int i = 0; i <= ruins; i++) {
		bfs(i);		
	}
	
	for (int i = 0 ;i <= ruins; i++) order[i] = i;
	
	do {
		int sumturns = 0;
		int sumscore = 0;
		int now = 0;
		while (now < ruins) {
			++now;
			int di = dist[order[now - 1]][pos[order[now]].x][pos[order[now]].y];
			if (di > -1) {
				sumturns += di;
				sumscore += pos[order[now]].bonus;
				chkmax(ruin_product[(sumturns + 1) / 2], sumscore);
			}
			else break;
		}
	} while (next_permutation(order + 1, order + ruins + 1));
	
	for (int i = 1; i <= max_turn; i++)
		chkmax(ruin_product[i], ruin_product[i - 1]);
		
}

int main() {
	while (scanf("%d%d%d", &n, &m, &target) == 3) {
		for (int i = 1; i <= n; i++)
			scanf("%s",mat[i] + 1);
			
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {	
				scanf("%d", &product[i][j]);
			}
		
		scanf("%d", &ruins);
		
		for (int i = 1; i <= ruins; i++) {
			scanf("%d%d%d", &pos[i].x, &pos[i].y, &pos[i].bonus);
		}
		
		int capx, capy;
		scanf("%d%d", &capx, &capy);
		
		
		pos[0].x = capx, pos[0].y = capy;
		
		max_turn = n * m * 2 + 50;
		
		calc_worker();
		calc_ruin();
		
		int ans = -1;		
	/*	for (int turns = 1; turns <= 10; turns++) {
			printf("Round %d : %d\n", turns, worker_product[turns]);
		}
		for (int turns = 1; turns <= 10; turns++) {
			printf("Round %d : %d\n", turns, ruin_product[turns]);
		}*/
		
		for (int turns = 1; turns <= max_turn; turns++) {
			if (worker_product[turns] + ruin_product[turns] >= target) {
				ans = turns;
				break;
			}
		}
		
		printf("%d\n", ans);
	}			
	return 0;
}
