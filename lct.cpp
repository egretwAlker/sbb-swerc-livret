#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
namespace LCT {
  int c[N][2], fa[N];
  bool rev[N];
  bool IsRoot(int x) {
    return c[fa[x]][0] != x && c[fa[x]][1] != x;
  }
  bool Which(int x) {
    return c[fa[x]][1] == x;
  }
  void PushUp(int x) {
  }
  void SetRev(int x) {
    rev[x] ^= 1;
    swap(c[x][0], c[x][1]);
  }
  void PushDown(int x) {
    if(rev[x]) {
      SetRev(c[x][0]);
      SetRev(c[x][1]);
      rev[x] = 0;
    }
  }
  void Rotate(int x) {
    int y = fa[x], d = Which(x);
    fa[x] = fa[y];
    if(!IsRoot(y)) c[fa[y]][Which(y)] = x;
    fa[c[x][!d]] = y; c[y][d] = c[x][!d];
    c[x][!d] = y; fa[y] = x;
  }
  void Splay(int x) {
    static stack<int> sta;
    sta.push(x);
    int t = x;
    while(!IsRoot(t)) sta.push(t = fa[t]);
    while(!sta.empty()) PushDown(sta.top()), sta.pop();
    for(int i=fa[x];!IsRoot(x);Rotate(x), i=fa[x])
      if(!IsRoot(i)) Rotate(Which(i) == Which(x)?i:x);
    PushUp(x);
  }
  void Access(int x) {
    for(int t=0;x;t=x, x=fa[x]) {
      Splay(x);
      c[x][1] = t;
      PushUp(x);
    }
  }
  void MakeRoot(int x) {
    Access(x);
    Splay(x);
    SetRev(x);
  }
  inline void Link(int x, int y) {
    MakeRoot(x);
    fa[x] = y;
  }
  void Cut(int x, int y) {
    MakeRoot(x);
    Access(y);
    Access(x);
    fa[y] = 0;
  }
  int GetRoot(int x) {
    Access(x); Splay(x);
    while(c[x][0]) x = c[x][0];
    Splay(x);
    return x;
  }
}

int main(void) {
  // TESTS!!
  return 0;
}