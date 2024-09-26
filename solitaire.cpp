
/**
 * Recursive DP to solve marble solitaire, and if possible gives solution
 *
 * O(2^N * R * C), N = #open spaces
 */

#include <iostream>
#include <vector>
#define ll long long

using namespace std;

int R, C;
vector<vector<int>> gridIdx;
ll grid = 0;

vector<bool> memo;
vector<bool> visited;

bool full (ll situation, int r, int c) {
	return ((1ll << gridIdx[r][c]) & situation);
}

bool canMove (int rFrom, int cFrom, int rTo, int cTo, ll situation) {
	int rMid = (rFrom + rTo) / 2, cMid = (cFrom + cTo) / 2;

	if (gridIdx[rFrom][cFrom] == -1 || gridIdx[rMid][cMid] == -1 || gridIdx[rTo][cTo] == -1) return false;
	return (full(situation, rFrom, cFrom) && full(situation, rMid, cMid) && !full(situation, rTo, cTo));
}

ll move (int rFrom, int cFrom, int rTo, int cTo, ll situation) {
	int rMid = (rFrom + rTo) / 2, cMid = (cFrom + cTo) / 2;
	
	return situation - (1ll << gridIdx[rFrom][cFrom]) - (1ll << gridIdx[rMid][cMid]) + (1ll << gridIdx[rTo][cTo]);
}

ll mv;
void test (ll situation) {
	visited[situation] = true;

	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {

			// up -> down
			if (r < R-2 && canMove(r, c, r+2, c, situation)) {
				mv = move(r, c, r+2, c, situation);
				if (!visited[mv]) test(mv);
				memo[situation] = memo[situation] || memo[mv];
			}

			// down -> up
			if (r < R-2 && canMove(r+2, c, r, c, situation)) {
				mv = move(r+2, c, r, c, situation);
				if (!visited[mv]) test(mv);
				memo[situation] = memo[situation] || memo[mv];
			}

			// left -> right
			if (c < C-2 && canMove(r, c, r, c+2, situation)) {
				mv = move(r, c, r, c+2, situation);
				if (!visited[mv]) test(mv);
				memo[situation] = memo[situation] || memo[mv];
			}

			// right -> left
			if (c < C-2 && canMove(r, c+2, r, c, situation)) {
				mv = move(r, c+2, r, c, situation);
				if (!visited[mv]) test(mv);
				memo[situation] = memo[situation] || memo[mv];
			}
		}
	}
}

signed main () {
	cin >> R >> C;
	gridIdx.assign(R, vector<int> (C));

	int idxOn = 0;
	char on;
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			cin >> on;
			if (on == '_') {
				gridIdx[r][c] = -1;
			}
			else {
				grid += (1ll << idxOn) * (on == 'o');
				gridIdx[r][c] = idxOn++;
			}
		}
	}

	if (idxOn == 0) {
		cout << "Not possible\n";
		return 0;
	}

	memo.assign(1ll << idxOn, false);
	visited.assign(1ll << idxOn, false);

	for (int i = 0; i < idxOn; i++) {
		memo[1ll << i] = true;
		visited[1ll << i] = true;
	}

	test(grid);

	cout << (memo[grid] ? "Possible" : "Not possible") << "\n";
}
