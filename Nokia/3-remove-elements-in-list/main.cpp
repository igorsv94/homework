/* Task: write a function that removes every fifth (5) element from this list.
 */

#include <gtest/gtest.h>
#include "list.h"

class Test : public ::testing::Test {
};

TEST_F(Test, CheckDeleteElements)
{
  List *head = new List(nullptr, 1);
  List *currElement = head;
  for (int i = 2; i < 18; i++) {
     currElement->next = new List(nullptr, i);
     currElement = currElement->next;
  }

  printList("original list:  ", head);

  deleteElements(head, 5);
  printList("after removing: ", head);

  ASSERT_TRUE(find(head, 5) == - 1);
  ASSERT_TRUE(find(head, 10) == -1);
  ASSERT_TRUE(find(head, 15) == -1);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
