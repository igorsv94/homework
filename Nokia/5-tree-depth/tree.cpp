#include <iostream>
#include <algorithm>

#include "tree.h"

/* returns a new node
 */
TreeNode *newNode(char data)
{
  TreeNode *node = new TreeNode();
  node->payload = data;
  node->leftChild = nullptr;
  node->rightChild = nullptr;

  return node;
}

/* recursive helper functions, which helps to find a root-to-leaf path
 */ 
void findPaths(TreeNode *node, std::vector<std::string> &paths,
     char bufPath[], int pathLen)
{
  if (node == nullptr) {
    return;
  }

  // append node to path
  bufPath[pathLen++] = node->payload;

  // if it's a leaf - search next
  if (node->leftChild == nullptr && node->rightChild == nullptr) {
    bufPath[pathLen] = '\0';
    paths.push_back(bufPath);
  } else {
    findPaths(node->leftChild, paths, bufPath, pathLen);
    findPaths(node->rightChild, paths, bufPath, pathLen);
  }
}

/* returns a vector of strings, which contain the deepest paths of a tree
 */ 
std::vector<std::string> allMaxDepths(TreeNode *root)
{
  std::vector<std::string> paths = {""}; // vector of deepest paths
  char bufPath[1000]; // buffer
  findPaths(root, paths, bufPath, 0);
  
  auto maxDepth = std::max_element(paths.begin(), paths.end(),
                                   [](std::string &a, std::string &b) {
                                     return a.size() < b.size();
                                   });

  std::vector<std::string> result;
  std::copy_if(paths.begin(), paths.end(), std::back_inserter(result),
               [maxDepth](std::string &str) {
                 return str.size() == maxDepth->size();
               });
  return result;
}

