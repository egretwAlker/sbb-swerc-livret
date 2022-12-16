#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10; // nodes numerated from 1
namespace LCT {
  int c[N][2], fa[N];
  bool rev[N];
  bool isRoot(int x) {
    return c[fa[x]][0] != x && c[fa[x]][1] != x;
  }
  bool which(int x) {
    return c[fa[x]][1] == x;
  }
  void pushUp(int x) {
  }
  void setRev(int x) {
    rev[x] ^= 1;
    swap(c[x][0], c[x][1]);
  }
  void pushDown(int x) {
    if(rev[x]) {
      setRev(c[x][0]);
      setRev(c[x][1]);
      rev[x] = 0;
    }
  }
  void rotate(int x) {
    int y = fa[x], d = which(x);
    fa[x] = fa[y];
    if(!isRoot(y)) c[fa[y]][which(y)] = x;
    fa[c[x][!d]] = y; c[y][d] = c[x][!d];
    c[x][!d] = y; fa[y] = x;
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
      c[x][1] = t;
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
    while(c[x][0]) x = c[x][0];
    splay(x);
    return x;
  }
}
using namespace LCT;

int lca(int x, int y) {
  access(y);
  access(x);
  splay(y);
  return fa[y];
}

int main(void) {
  makeRoot(1);
  makeRoot(2);
  makeRoot(3);
  makeRoot(4);
  makeRoot(5);
  link(4, 3);
  link(5, 3);
  printf("%d\n", getRoot(4));
  link(3, 1);
  printf("%d\n", getRoot(4));
  link(2, 1);
  printf("%d\n", lca(5, 4));
  printf("%d\n", lca(5, 2));
  return 0;
}