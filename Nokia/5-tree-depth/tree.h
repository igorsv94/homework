#include <vector>
#include <string>

struct TreeNode {
  char payload;    // label of node

  struct TreeNode* leftChild;
  struct TreeNode* rightChild;
};

TreeNode *newNode(char data);
void findPaths(TreeNode *node, std::vector<std::string> &paths,
     char bufPath[], int pathLen);
std::vector<std::string> allMaxDepths(TreeNode *root);
