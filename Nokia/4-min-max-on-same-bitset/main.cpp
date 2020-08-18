/* Write a function that takes a 32-bit unsigned integer number and returns
 * the maximum and minimum 32-bit unsigned integer numbers which can be
 * obtained using the same number of bits set to 1 as in the taken number
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>

#include "numbers.h"

class Test : public ::testing::Test {
};

void printBitsRepr(uint32_t min, uint32_t max)
{
  std::cout << "\nmin: " << min << ", "
            << "max:"  << max
            << std::endl;

  std::cout << "bits representation: " << std::endl;
  std::string minStr, maxStr;
  for (uint32_t i = 1 << sizeof(uint32_t)*8 - 1; i > 0; i = i / 2) {
    minStr.append((min & i)? "1" : "0");
    maxStr.append((max & i)? "1" : "0");
  }
  std::cout << "min: " << minStr << std::endl
            << "max: " << maxStr
            << std::endl;
}

TEST_F(Test, CheckNumbers)
{
  uint32_t min, max;
  
  processNumber(7, min, max);
  printBitsRepr(min, max);
  ASSERT_TRUE(min == 7);
  ASSERT_TRUE(max == 3758096384);

  processNumber(UINT32_MAX, min, max);
  printBitsRepr(min, max);
  ASSERT_TRUE(min == UINT32_MAX);
  ASSERT_TRUE(max == UINT32_MAX);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
