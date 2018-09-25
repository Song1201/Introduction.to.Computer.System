#include <stdio.h>

int main(){
  int x = -1;
  int n = 2;
  int shift = ~n + 1;
  int shiftLow5 = shift&(0x0000001f);
  printf("%d",shiftLow5);
  printf("\n");
  int midKey = x<<shift;
  printf("%d",midKey);
  printf("\n");
  int key = midKey>>shift;
  printf("%d",key);
  printf("\n");

  return 0;
}