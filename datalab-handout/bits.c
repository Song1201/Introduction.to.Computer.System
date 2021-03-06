/* 
 * CS:APP Data Lab                                                              
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~((~x) | (~y));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  return (x >> (n<<3)) & 255;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  return ~(1<<31>>n<<1) & x>>n;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int zeroOne = (85<<8) + 85;
  int zero2one2 = (51<<8) + 51;
  int zero4one4 = (15<<8) + 15;
  zeroOne = (zeroOne<<16) + zeroOne;
  // Each 2 bits in x shows the number of set bits in these 2 bits.
  x = (x&zeroOne) + ((x>>1)&zeroOne);
  zero2one2 = (zero2one2<<16) + zero2one2;
  // Each 4 bits in x shows the number of set bits in these 4 bits.
  x = (x&zero2one2) + ((x>>2)&zero2one2);
  zero4one4 = (zero4one4<<16) + zero4one4;
  // Like before
  x = (x&zero4one4) + ((x>>4)&zero4one4);
  return (x&255) + ((x>>8)&255) + ((x>>16)&255) + ((x>>24)&255);
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  // Only 0xffffffff and 0x7fffffff will change the highest bit after plus 1.
  // So after ^ operation, only those two will have 1 on the highest bit. 
  // But only 0xffffffff which is ~0 will also have 1 on the highest bit before
  // the ^ operation. So after the & operation, only x=0 will have the result 
  // which has 1 on the highest bit.  
  return ((((~x+1)^(~x))&(~x))>>31)&1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  // Get 32-n
	int shift = (~n + 1) & 0x1f;
  // For negetive integer than can be represent by n bits, it should have a 
  // bunch of 1s from the most significant bit.
	int key = (x << shift) >> shift;  
  return !(x^key); 
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int neg = x>>31; // neg == 0xffffffff when x<0, neg == 0x00000000 when x>0
  int lastNbitsMask = ~0 + (1<<n);
  // The result should be added 1 when  1.x<0 && 2.there are 1(s) in last n bits
  return (x>>n) + !!(neg&lastNbitsMask&x);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  return (!(x&(1<<31)))&(!!x);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int msbX = (x>>31)&1;
  int msbY = (y>>31)&1;
  int equalSign = !(msbX^msbY);
  // if x,y have equal sign, x<=y iff x+(~y)<0. This can be proved when detailed
  // analyse in different cases:1.x>=0, y>=0 2.x<0,y<0. In case 2, y=-1 need to
  // be special considered but we can have the same conclusion.
  int equalSignTrue = equalSign&((x+(~y))>>31);
  // if x,y do not have equal sign, it quite easy to decide.
  int diffSignTrue = (!equalSign)&msbX; 
  return equalSignTrue|diffSignTrue;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  // If there is 1 from the 31-17 bit, base will be 16. Otherwise base is 0.
  int base = (!!(x>>16))<<4;
  // Follow the divide&conquer method. Process a smaller range each time.
  base += (!!(x>>(base+8)))<<3;
  base += (!!(x>>(base+4)))<<2;
  base += (!!(x>>(base+2)))<<1;
  base += !!(x>>(base+1));
  return base;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  // Key point is to identify the NaN. In IEEE 754, for a floating point value 
  // in C, it is NaN when the 31-24 bit are all 1, but there is still 1 in 
  // 23-1 bit.
  // !!!ATTENTION. A question from this function. Why define the above situation 
  //as Nan? It could have an actual value.
  // Guessed Answer: To avoid overflow when operating floats.
  // If uf is Nan, then return it.
  if ((uf & 0x7fffffff) > 0x7f800000) return uf;
  // Otherwise return the negetive uf.
  return uf ^ 0x80000000;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  // First need to convert negetive number to its absolute value. Because the 
  // fraction part in floating point number doesn't use 2's component number.
  // Then shift them to the right, until the shifted value equals to 1. At that 
  // time, the shifted bits is the exponent we need. 2 special cases need to be 
  // considered. First, no 1 exists in 0x00000000, so just return its floating
  // point representation directly, which is also 0x00000000. Second, 0x80000000
  // doesn't have a positive absolute value. So deal with it sperately.

  int xFractionLeft;
  int numTruncatedBits;
  int truncatedBits;
  int roundThresh;

  // x == 0, return x.
  if(!x) return x;
  else {
    int LENGTH = 32;
    int FRACTION_LENGTH = 23;
    int FRACTION_MASK = 0x007fffff;
    int BIAS = 127;
    int INT_MIN = 0x80000000;
    int exponent = 0;
    int fraction = 0;
    int signX = (x>>31)&1;
    // If more bits than FRACTION_LENGTH need to be used to represent x, some 
    // bits will be truncated during right shift. But we want to round. So add
    // extra to the final result. IEEE754 floating point number rounding rules:
    // Round to the nearest value. When have equal accuracy loss rounding to 
    // both sides, round to the even side, which means after rounding, the last
    // bit of the rounded number should be 0.
    int extra = 0;
    // x is 0x80000000
    if(x==INT_MIN) exponent = LENGTH-1;
    // x is other negetive or positive
    else {
      if(signX) x = -x;
      while((x>>exponent)!=1) exponent++;
      xFractionLeft = x<<(LENGTH-exponent);
      numTruncatedBits = LENGTH - FRACTION_LENGTH;
      fraction = (xFractionLeft>>numTruncatedBits) & FRACTION_MASK;
      truncatedBits = xFractionLeft & ((1<<numTruncatedBits)-1);
      roundThresh = 1<<(numTruncatedBits-1);
      if(truncatedBits>roundThresh) extra = 1;
      else if(truncatedBits==roundThresh && (fraction&1)) extra = 1;
    }
    return (signX<<(LENGTH-1))|((((exponent+BIAS)<<FRACTION_LENGTH)|fraction)+\
    extra);
  }
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  // In IEEE 754, for a floating point value, it is NaN when the 31-24 bit are 
  // all 1, but there is still 1 in the 23-1 bit. When all exponent bits are 1, 
  // means it is inf, then just return it.
  if((uf&0x7fffffff)>=0x7f800000) return uf;
  // If the exponent is all 0s, and the mantissa(fraction) is non-zero, then the
  // value is treated as a denormalized number. The denormalized numbers do not 
  // have an assumed leading 1 before the binary point. Also, the power of 2 
  // when converting to decimal number is treated as -126, not -127. To deal 
  // with denormalized numbers, we shift them 1 bit to the left to *2, when it 
  // moves a 1 into the exponent, it is interpreted as a normal floating point
  // value again and the value is equal to the origin denormalized value *2.
  if((uf&0x7f800000)==0) return ((uf&0x80000000)|(uf<<1));
  return uf + (1<<23);
}
