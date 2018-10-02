#include <stdio.h>

int main(){
  int x = 0xfeffffff;

  if(!x) return x;
  else {
    int LENGTH = 32;
    int FRACTION_LENGTH = 23;
    int BIAS = 127;
    int INT_MIN = 0x80000000;
    int exponent = 0;
    int fraction = 0;
    int signX = (x>>31)&1;
    // If more bits than FRACTION_LENGTH need to be used to represent x, some 
    // bits will be truncated during right shift. But we want to round. So add
    // extra to the final result.
    int extra = 0;
    // x is 0x80000000
    if(x==INT_MIN) exponent = LENGTH-1;
    // x is other negetive or positive
    else {
      if(signX) x = -x;
      int xCopy = x;
      while(xCopy!=1) {
        xCopy = xCopy>>1;
        exponent++;
      }
      fraction = (x<<(LENGTH-exponent)>>(LENGTH-FRACTION_LENGTH))&0x007fffff;
      if(exponent>FRACTION_LENGTH+1) {
        extra = (x>>(exponent-FRACTION_LENGTH-1))&1;
      }
    }
    printf("%d %d\n",exponent,extra);
    return (signX<<(LENGTH-1))|((((exponent+BIAS)<<FRACTION_LENGTH)|fraction)+\
    extra);
  }
}
