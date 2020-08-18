/* Task: Write a function that calculates the first N prime numbers and put
 * these numbers in the array passed to it.
 */

#include <iostream>
#include <gtest/gtest.h>
#include "primeNumbers.h"

class Test : public ::testing::Test {
};

TEST_F(Test, CheckPrimeNumbers) 
{
  std::vector<int> primeNumbersArray;
  std::vector<int> model = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  primeNumbers(30, primeNumbersArray);
  ASSERT_TRUE(primeNumbersArray == model);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
