/* Task: Write a function that counts the number of words in the text for each
 * word length (X words with  1-letter length, Y words with 2-letters length,
 * and etc.)
 */

#include <string_view>
#include <iostream>
#include <gtest/gtest.h>
#include "stringcounter.h"

class Test : public ::testing::Test {
};

TEST_F(Test, CheckCountOfWords)
{
  std::string_view text("C++ is a general-purpose programming language created by"
  " Bjarne Stroustrup as an extension of the C programming language");

  std::map<int, int> summaryMap = parse(text);

  ASSERT_TRUE(summaryMap[14] == 2);
  ASSERT_TRUE(summaryMap[13] == 5);
  ASSERT_TRUE(summaryMap[12] == 2);
  ASSERT_TRUE(summaryMap[9]  == 1);
  ASSERT_TRUE(summaryMap[8]  == 1);
  ASSERT_TRUE(summaryMap[7]  == 2);
  ASSERT_TRUE(summaryMap[6]  == 1);
  ASSERT_TRUE(summaryMap[5]  == 1);
  ASSERT_TRUE(summaryMap[4]  == 2);

}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
} 
