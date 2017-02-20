/*
 * Names: Ian Kirkpatrick, Benjamin Groseclose, Nathan Johnson,
 * Class: CPS 360,                            Section: Spring 2017
 * Times: Tuesday, Thursday 9:30 - 11:00      Assignment: 03
 * Due: February 21, 2017                      Started: February 19, 2017
 * Credit: 10 points.
 *
 * 
 */

#include <stdio.h>
#include <stdlib.h>

/*
  Main function of program.
  This simplly calls the output funtion and then exits with an error code of
  0.
*/
int main(int argc, char *argv[]) {
  void output();
  output();
  exit(0);
}

/*
  Print the output for the program.
  The output displays 3 things.

  One of these outputs displays whether or not the architecture of
  the compiler stores bytes in big-endian representation or little-endian
  representation.
  Another of these outputs displays how many bytes are used to store an integer
  by the C compiler. There are two different algorithms that are written to do
  this so the output displays both of these making one more line of output for
  a total of 4 things to display.
  The final piece of information to display is whether or not the compiler
  stores integers in two's complement.
*/
void output() {
  int isbigornot();
  int sizeofint();
  int sizeofintalt();
  int is2scompornot();

  int bigend = isbigornot();
  int i1size = sizeofint();
  int i2size = sizeofintalt();
  int is2scomp = is2scompornot();

  char *beout;
  char *tcout;

  if (bigend) {
    beout = "Yes";
  } else {
    beout = "No";
  }

  if (is2scomp) {
    tcout = "Yes";
  } else {
    tcout = "No";
  }
  printf("Big endian architecture: %s\n", beout);
  printf("Size of integer in bytes: %d\n", i1size);
  printf("(Alternate method size) %d\n", i2size);
  printf("2's complement representation: %s\n", tcout);
}

/* returns 1 if the underlying architecture uses
  big-endian representation for multibyte data, 0 otherwise.
  Follow the suggestion in textbook.

  Create an array of two integers and sets them to different numbers. For
  readability's sake, each nibble of the ints are one larger than the nibble
  before.

  Next we create a new pointer that reads the array as an array of chars. This
  way, we can break the array down into it's indevidual bytes. If the first int
  is stored with the first byte (read as a char in the char array pointer) as the
  least significant byte, then it is assumed that the underlying
  archetecture stores values in little-endian representation. Otherwise, if the
  first byte (read as a char in the char array pointer) stores the most
  significant byte in the integer, then it is assumed that the underlying
  archetecture stores values in big-endian representation.

  If the underlying archetecture is represented using big-endian,
  then 1 is returned. Otherwise 0 is returned.
*/
int isbigornot() {
  unsigned int blist[2] = {0x01234567,0x89abcdef};
  char *arr = (char *) blist;

  if (arr[0] == 0x67) {
    return 0;
  } else {
    return 1;
  }
}

/* Determine whether or not integers are represented in the computer as 2's
  complement or 1's complement.

  To do this, set an int to an arbitrary number above 0. We then take that number
  and flip it using the ~ operator. If the number referenced as a signed int is
  returned as that number plus one but negative, then we know that the compiler
  adds one to the complement when converting so we assume that signed ints are
  represented in 2's complement.

  If it is determined that the compiler stores numbers in 2's complement, then
  1 is returned. Otherwise, 0 is returned.
*/
int is2scompornot() {
  int a = 10;
  if(~a == -11){
    return 1;
  }
  return 0;
}

/* Determines the size of integers stored by the c compiler.
  First, an array of 2 ints is declared, the first being 0 and the second being
  -1 (in 2's complement, this is fffffffff...). This second int is used as
  a signifier int to tell the algorithm when it's done looking at the first
  int (all 0's).

  Next, a second pointer is declared that treats the first array as an array
  of chars (We know that chars are 1 byte each and it's the smallest amount
  type). This devides each element in the array pointed to by both the first
  and now the second pointer into their indevidual bytes.

  It then counts how many bytes are 0 until it hits the first non zero byte
  (the first one in -1 or ffff... as a signed int). that number is returned as
  the number of bytes that are used to represent the first element in the first
  array which sees it as an int.
*/
int sizeofintalt() {
  int a[2] = {0, -1};
  char *aptr = (char *) a;
  int i = 0;

  for ( ; i < 10; i ++) {
    if (aptr[i] != 0x00) {
      return i;
    }
  }
  return -1;
}

/* Determines the size of an int stored by the compiler.
  First, a variable is declared as an int and set to 1. We then bit-shift the
  1 to the left one place in a loop until the value of this variable is 0 (the
  bit reached the end of the storage of the int).

  Each time we shift the bit, we increment a count by 1. At the end, we divide
  that count by 8 (number of bits in a byte) and return that as the size of int
  in bytes.
*/
int sizeofint() {
  unsigned int x = 1;
  int i = 1;
  while (x != 0) {
    x <<= 1;
    i ++;
  }
  return i/8;
}
