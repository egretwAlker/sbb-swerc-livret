#include <bits/stdc++.h>
using namespace std;
const int N=10010;
typedef long long ll;
#define err(...) fprintf(stderr, __VA_ARGS__)

namespace lct {
  int ch[N][2], fa[N]; // nodes count from 1
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

  void setRev(int x) { // rev is for the makeRoot, can be occasionally removed
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
using namespace lct;

void showAux(int x) {
	if(x) {
		err("%d(%d %d): %d %d\n", x, val[x], sm[x], ch[x][0], ch[x][1]);
		showAux(ch[x][0]);
		showAux(ch[x][1]);
	}
}