/* 
 * CS:APP Data Lab 
 * 
 * Name: Nicholas Renninger
 * SID: 105492876
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
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
	 This file is part of the GNU C Library.

	 The GNU C Library is free software; you can redistribute it and/or
	 modify it under the terms of the GNU Lesser General Public
	 License as published by the Free Software Foundation; either
	 version 2.1 of the License, or (at your option) any later version.

	 The GNU C Library is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	 Lesser General Public License for more details.

	 You should have received a copy of the GNU Lesser General Public
	 License along with the GNU C Library; if not, see
	 <http://www.gnu.org/licenses/>.  */

/* This header is separate from features.h so that the compiler can
	 include it implicitly at the start of every compilation.  It must
	 not itself include <features.h> or any other header that includes
	 <features.h> because the implicit include comes before any feature
	 test macros that may be defined in a source file before it first
	 explicitly includes a system header.  GCC knows the name of this
	 header in order to preinclude it.  */

/* glibc's intent is to support the IEC 559 math functionality, real
	 and complex.  If the GCC (4.9 and later) predefined macros
	 specifying compiler intent are available, use them to determine
	 whether the overall intent is to support these features; otherwise,
	 presume an older compiler has intent to support these features and
	 define these macros by default.  */

/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
	 synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
	 2015-05-15).  */

/* We do not support C11 <threads.h>.  */


/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	/* Use De Morgan's Laws: A & B = ~(~A | ~B)*/
	return ~(~x | ~y);}

/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	/* First need to right shift the bits by (n * 2^3) - right shift by n bytes.
		 Then, mask out any leading digits by doing bitwise and with TMAX mask.
		 Task becomes to push all of the bits to the right until, then get rid of 
		 leading digits*/
	int shiftedNBytes = x >> (n << 3);
	int mask = 0xFF;
	return shiftedNBytes & mask;
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

	/* Need to generate a mask of n leading 0s followed by 1s in order to remove
	 * any extra 1s placed by arithmetic shift. Then just and the mask with the
	 * arithmetic right shift by n bits ( x >> n ) to get the equivolent logical
	 * shift. 
	 */

	//int onesMask = ~(( ~(x & 0) << (31 - n)) << 1);
	int onesMask = ~(1 << 31 >> n << 1);
	int arithmeticShiftX = x >> n;
	int logicalShiftX = arithmeticShiftX & onesMask;

	return logicalShiftX;
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
			
	/* determine if the LSB of each byte of x is a one. Then shift x right by one
	 * byte and repeat the proccess, adding any new ones to the running total.
	 * Then add up the grand total at the end, and mask out all but one byte for
	 * the final count of ones. 
	 */

	int LSB_Counter = 0x01; // initial mask bit-pattern
	int currentOneCount, finalOneCount, onesMask;

	// generate bitmask (LSB_Counter) to count the LSB of each byte fromm the
	// initial bit-mask pattern: 0x01010101.
	LSB_Counter = LSB_Counter | (LSB_Counter << 16);
	LSB_Counter = LSB_Counter | (LSB_Counter << 8);

	// Count LSB of each byte, add it to the total, then shift x right one more
	// bit and repeat the process for each byte.
	currentOneCount = (x & LSB_Counter);

	currentOneCount = currentOneCount + ((x >> 1) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 2) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 3) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 4) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 5) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 6) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 7) & LSB_Counter);

	// Add the first half of the ones count for each byte together.
	currentOneCount = currentOneCount + (currentOneCount >> 16);

	// Add the second half of the ones count for each byte together.
	currentOneCount = currentOneCount + (currentOneCount >> 8);

	// max number of ones = 32 -> stored in one byte, so mask out all but last
	// byte of the current ones mask.
	onesMask = 0xff;
	finalOneCount = currentOneCount & onesMask;

	return finalOneCount;	
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {

	/* Checks if x is zero with with bitwise operations. */

	// find two's complement of x to use as subtraction
	int twosCompX = ~x + 0x1; 

	// determine if x == 0 using bitwise operators using the identity: a == b :=
	// ~( (a - b) | (b - a) ). Shifts 32 - 1 bits to ensure that the first bit
	// sets the equality of the statement.
	int bangX = ~((0x0 + twosCompX) | (x + 0x0)) >> 31;

	// only return first bit of bangX, as bangX will either be 0x00000000 or
	// 0xffffffff at this point.
	bangX = bangX & 0x1;

	return bangX;
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

	/* minimum two's comp. integer is a one in the MSB and the rest zeros. */

	return 0x1 << 31;
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

	/* Shift the bits n-1 to the right, such that if x can be perfectly
	 * represented by n bits, shiftedX = 0. Then add 1 to this number and then
	 * right shift it again by 1 bit. If the number is 0, then the number can be
	 * represented by n bits
	 */

	int onesTwosComp = ~0x1 + 0x1;
	int shiftedX = x >> (n + onesTwosComp); 
	int oneOrZero = 0x1 + shiftedX;
	int lastThang = oneOrZero >> 1;

	// 0 means it fits in n-bits, so need to not the answer
	return !lastThang;
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

	/* x >> n works, except when x is a negative number not divisble by 2^n. In
	 * this, case x >> n needs to be corrected by adding one to the quotient. 
	 */

	// start by computing x/(2^n) for all positive integers and negative 
	// integers divisible by 2^ns
	int basicDivide2n = (x >> (n));

	// get sign bit of x
	int isNegative = (x >> 31); 

	// determine if x can be divided by 2^n
	int isntDivBy2N = !!(x << (32 + (~n + 1)));

	// if x is negative, not divisible by 2^n, and n != 0 (n = 1 => 2 ^ 0 = 
	// 1 => x is always divisble by 2^n), add one to the quotient.
	int negCorrection = (isNegative & isntDivBy2N) & !!n;

	return basicDivide2n + negCorrection;
}

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {

	/* The negation of a two's complement integers is given simply by its two's 
	 * complement.
	 */

	return ~x + 1;
}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	
	/* Check the sign bit. If the sign bit is 0 and x != 0, return true. */

	int signBit = x >> 31;
	return !signBit & !!x;
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {

	/* Checks sign of y-x, and handles some special cases due to overflow. */

	// need to get the sign of the x and y
	int xSign = x >> 31;
	int ySign = y >> 31;
	
	// returns 1 if x and y are the same sign or x is neg. and y is pos.
	// returns 0 if x is pos. and y is neg.
	// conditions essentially checks that x MIGHT be less than or eq. to y
	int possiblyLessThan = xSign | ~ySign;

	// Handles special case of x being neg. and y being pos., and immediately
	// returns 1. This is done to handle overflow; when large integers are added,
	// the sign bit will no longer be reflective of the actual result, so this
	// function is implemented to manually guarantee that x = (-), y = (+) always
	// returns true. Specifically, if x = neg. and y = pos., returns 1.
	int xNegYPos = ~(xSign & ~ySign) + 0x1;

	// do: y-x. If the sum is negative return false.
	int twosCompX = ~x + 1;
	int signYMinusX = ((y + twosCompX) >> 31) + 0x1;
 
	return possiblyLessThan & (xNegYPos | signYMinusX);
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {

  /* floor(Log base 2) boils down to find the index of the MSB in the number.
	 * First make a number with all ones to the left of the MSB. Then simply count
	 * the number of ones to find the index of the original MSB, which is 
	 * equivalent to floor(log base 2).
	 */

	int LSB_Counter = 0x01; // initial mask bit-pattern
	int currentOneCount, finalOneCount, onesMask;

	// Need to fill in all ones up to and including the index of the MSB. This is
	// done by shifting over by 1, 2, ... and ORing the new x. This sets all
	// adjacent bits right of the MSB to one, inclusing the MSB. 
	// 
	// REFERENCED from:
	// https://stackoverflow.com/questions/21413565/create-a-mask-that-marks-the-
	// most-significant-set-bit-using-only-bitwise-operat
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;

	// need to shift one more to the right to set the MSB to zero, as we need to
	// count the number of zeros the right of the MSB.
	x >>= 1;


	/***************************************************************/
	/* NOW USE BITCOUNT CODE TO COUNT THE # OF BITS TO LEFT OF MSB */
	/***************************************************************/	


	// generate bitmask (LSB_Counter) to count the LSB of each byte fromm the
	// initial bit-mask pattern: 0x01010101.
	LSB_Counter = LSB_Counter | (LSB_Counter << 16);
	LSB_Counter = LSB_Counter | (LSB_Counter << 8);

	// Count LSB of each byte, add it to the total, then shift x right one more
	// bit and repeat the process for each byte.
	currentOneCount = (x & LSB_Counter);

	currentOneCount = currentOneCount + ((x >> 1) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 2) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 3) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 4) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 5) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 6) & LSB_Counter);
	currentOneCount = currentOneCount + ((x >> 7) & LSB_Counter);

	// Add the first half of the ones count for each byte together.
	currentOneCount = currentOneCount + (currentOneCount >> 16);

	// Add the second half of the ones count for each byte together.
	currentOneCount = currentOneCount + (currentOneCount >> 8);

	// max number of ones = 32 -> stored in one byte, so mask out all but last
	// byte of the current ones mask.
	onesMask = 0xff;
	finalOneCount = currentOneCount & onesMask;

	return finalOneCount;

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
 return 2;
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
	return 2;
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
	return 2;
}
