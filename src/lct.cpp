// https://www.spoj.com/problems/QTREE/
#include <bits/stdc++.h>
using namespace std;
const int N=10010;
typedef long long ll;
#define err(...) fprintf(stderr, __VA_ARGS__)

namespace LCT {
  int ch[N][2], fa[N]; // notes count from 1
	int sm[N], val[N];
  bool rev[N];

  bool isRoot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
  }

  bool which(int x) {
    return ch[fa[x]][1] == x;
  }

  void pushUp(int x) {
		sm[x] = val[x];
		if(ch[x][0]) sm[x] = max(sm[x], sm[ch[x][0]]);
		if(ch[x][1]) sm[x] = max(sm[x], sm[ch[x][1]]);
  }

  void setRev(int x) {
    rev[x] ^= 1;
    swap(ch[x][0], ch[x][1]);
  }

  void pushDown(int x) {
    if(rev[x]) {
      setRev(ch[x][0]);
      setRev(ch[x][1]);
      rev[x] = 0;
    }
  }

  void rotate(int x) {
    int y = fa[x], d = which(x);
    fa[x] = fa[y];
    if(!isRoot(y)) ch[fa[y]][which(y)] = x;
    fa[ch[x][!d]] = y; ch[y][d] = ch[x][!d];
    ch[x][!d] = y; fa[y] = x;
		pushUp(y);
  }

  void splay(int x) {
    static stack<int> sta;
    sta.push(x);
    int t = x;
    while(!isRoot(t)) sta.push(t = fa[t]);
    while(!sta.empty()) pushDown(sta.top()), sta.pop();
    for(int i=fa[x];!isRoot(x);rotate(x), i=fa[x])
      if(!isRoot(i)) rotate(which(i) == which(x)?i:x);
    pushUp(x);
  }

  void access(int x) {
    for(int t=0;x;t=x, x=fa[x]) {
      splay(x);
      ch[x][1] = t;
      pushUp(x);
    }
  }

  void makeRoot(int x) {
    access(x);
    splay(x);
    setRev(x);
  }

  inline void link(int x, int y) { // x is lower
    makeRoot(x);
    fa[x] = y;
  }

  void cut(int x, int y) {
    makeRoot(x);
    access(y);
    access(x);
    fa[y] = 0;
  }

  int getRoot(int x) {
    access(x); splay(x);
    while(ch[x][0]) x = ch[x][0];
    splay(x);
    return x;
  }

	void acclay(int x) {
		access(x);
		splay(x);
	}

	void clear() {
		memset(ch, 0, sizeof(ch));
		memset(fa, 0, sizeof(fa));
		memset(val, 0, sizeof(val));
		memset(sm, 0, sizeof(sm));
	}
}
using namespace LCT;

void showAux(int x) {
	if(x) {
		err("%d(%d %d): %d %d\n", x, val[x], sm[x], ch[x][0], ch[x][1]);
		showAux(ch[x][0]);
		showAux(ch[x][1]);
	}
}

vector<int> G[N];
int n, c[N], vx[N];

void dfs(int u, int fa) {
	for(auto a : G[u]) {
		int e = a/(n+1), v = a%(n+1);
		if(v == fa) continue;
		vx[e] = v;
		sm[v] = val[v] = c[e];
		link(v, u);
		dfs(v, u);
	}
}

int query(int x, int y) {
	if(x == y) return 0;
	acclay(y);
	splay(x);
	if(fa[y] != 0) {
		acclay(x);
		splay(y);
		return sm[y];
	}
	acclay(x);
	splay(y);
	if(fa[x] != 0) {
		acclay(y);
		splay(x);
		return sm[x];
	}
	int t = sm[y];
	acclay(y);
	splay(x);
	return max(t, sm[x]);
}

void solve() {
	clear();
	scanf("%d", &n);
	for(int i=1;i<=n;++i) G[i].clear();
	for(int i=1, x, y;i<n;++i) {
		scanf("%d%d%d", &x, &y, c+i);
		G[x].push_back(i*(n+1)+y);
		G[y].push_back(i*(n+1)+x);
	}
	dfs(1, 0);
	while(1) {
		char s[10]; int x, y;
		scanf("%s", s);
		if(s[0] == 'Q') {
			scanf("%d%d", &x, &y);
			printf("%d\n", query(x, y));
		} else if(s[0] == 'C') {
			scanf("%d%d", &x, &y);
			acclay(vx[x]);
			val[vx[x]] = y;
			pushUp(vx[x]);
		} else {
			break;
		}
	}
}

int main(void) {
	int T;
	scanf("%d", &T);
	while(T--) solve();
  return 0;
}