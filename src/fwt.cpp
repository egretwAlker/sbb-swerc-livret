void fwt(ll *f) {
  for(int i=1;i<=L;i<<=1) {
    for(int j=0;j<=L;++j) {
      if(j&i) {
        f[j] += f[j^i];
        f[j^i] = 2*f[j^i] - f[j];
      }
    }
  }
}

void dfwt(ll *f) {
  for(int i=1;i<=L;i<<=1) {
    for(int j=0;j<=L;++j) {
      if(j&i) {
        f[j] = (f[j]-f[j^i])>>1;
        f[j^i] += f[j];
      }
    }
  }
}