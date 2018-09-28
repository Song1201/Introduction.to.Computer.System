#include <stdio.h>

int main(){
  divpwr2(0x9bfceb01,1);

  return 0;
}

int divpwr2(int x, int n) {
  printf("%d\n",(!!(x&(1<<31)))&(!!n)&(!!(x&(~(-1<<n)))));
  return (x>>n)+((!!(x&(1<<31)))&(!!n)&(!!(x&(~(-1<<n)))));
}