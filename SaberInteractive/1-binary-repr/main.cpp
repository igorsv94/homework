#include <iostream>
#include <string>
#include <algorithm>

/* prints a binary representation of the given number. C-style
*/
void printBinaryRepr(int8_t number)
{
  char *numRepr = (char*)malloc(sizeof(int8_t) * 8); //allocate a buffer
  memset(numRepr, 0, sizeof(int8_t)); // fills it with nulls

  printf("binary repsesentation of \t%d:\t", number);
  //walk through the bits of the given number and fill a representations str
  for(unsigned int i = 0; i < sizeof(int8_t) * CHAR_BIT; ++i, number >>= 1) {
    numRepr[i] = (number & 1)? '1' : '0';
  }

  //print it in the reverse direction
  for (int i = sizeof(numRepr)*8; i >= 0; --i) {
    printf("%c", numRepr[i]);
  }
  printf("\n");
  free(numRepr); // free an allocated memory
}

/* prints a binary representation of the given number. C++ style
 */
template<typename T>
void printBinaryRepr2(T t)
{
  std::string res = ""; // create an empty string

  //walk through the bits of the given number and fill a representations str
  for(unsigned int i = 0; i < sizeof(T) * CHAR_BIT; ++i, t >>= 1) {
    res.push_back((t & 1)? '1' : '0');
  }

  std::reverse(res.begin(), res.end()); // reverse the result string
  std::cout << res << std::endl; // print it
}

int main(void)
{
  printf("C-style:\n");
  printBinaryRepr(5);
  printBinaryRepr(-6);
  printBinaryRepr(0);
  printBinaryRepr(127);
  printBinaryRepr(-127);
  printBinaryRepr(1);

  std::cout << "C++ style" << std::endl;
  printBinaryRepr2(uint8_t(5));
  printBinaryRepr2(uint8_t(-6));
  printBinaryRepr2(uint8_t(0));
  printBinaryRepr2(uint8_t(127));
  printBinaryRepr2(uint8_t(-127));
  printBinaryRepr2(uint8_t(1));

  return 0;
}
