/* Write a function that calculates the depth of the tree (the maximum number
 * of nodes in the path from the root to the leaf). The solution shall return
 * all paths in the tree that have such depth.
 */

#include <gtest/gtest.h>

#include "tree.h"

class Test : public ::testing::Test {
};

TreeNode *makeTree();

TEST_F(Test, Check)
{
  TreeNode *root = makeTree();
  std::vector<std::string> paths = allMaxDepths(root);
  for (auto &it: paths) {
    std::cout << it << ", len = " << it.size() << std::endl;
  }

  ASSERT_TRUE(paths.size() == 2);
  ASSERT_TRUE(paths[0] == "0138b");
  ASSERT_TRUE(paths[1] == "025ac");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TreeNode *makeTree()
{
  TreeNode *root = newNode('0');

  root->leftChild = newNode('1');
  root->rightChild = newNode('2');
  root->leftChild->leftChild = newNode('3');
  root->leftChild->rightChild = newNode('4');
  root->rightChild->leftChild = newNode('5');
  root->rightChild->rightChild = newNode('6');
  root->leftChild->leftChild->leftChild = newNode('7');
  root->leftChild->rightChild->rightChild = newNode('9');
  root->rightChild->leftChild->rightChild = newNode('a');
  root->leftChild->leftChild->rightChild = newNode('8');
  root->leftChild->leftChild->rightChild->leftChild = newNode('b');
  root->rightChild->leftChild->rightChild->rightChild = newNode('c');
/*              0
 *            /   \
 *           1     2
 *         /  \   / \
 *        3    4 5   6
 *       / \   |  \
 *      7   8  9   a
 *         /        \
 *        b          c
*/
  return root;
}

