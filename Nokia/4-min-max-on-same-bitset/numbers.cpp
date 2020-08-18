#include "numbers.h"

/* calculates minimum and maximum numbers using bits of provided number 
 */
void processNumber(const uint32_t number, uint32_t &min, uint32_t &max)
{
  // calculate count of non-zero bits
  int countOfDigits = 0;

  for (uint32_t i = 1 << sizeof(uint32_t)*8 - 1; i > 0; i = i / 2) {
    if (number & i) { countOfDigits++; }
  }

  uint32_t templateNum = 0;
  // make min number
  for (int i = 0; i < countOfDigits; i++) {
    templateNum |= (1 << i);
  }
  min = templateNum;

  // make max number
  templateNum = templateNum << sizeof(uint32_t)*8 - countOfDigits;
  max = templateNum;
}

