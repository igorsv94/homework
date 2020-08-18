#include <string>
#include <iostream>

#include "list.h"

/* prints list
 */ 
void printList(std::string append, List *list)
{
  List *curr = list;
  std::cout << append;

  while (curr != nullptr) {
    std::cout << curr->payload << " ";
    curr = curr->next;
  }
  std::cout << std::endl;
}

/* deletes every 'pos' element from the list
 */ 
void deleteElements(List *list, int pos)
{
  int index = 1; // index of the element in the list
  List *currPos = list;
  while (currPos != nullptr) {
    // if next element should be deleted
    if (currPos->next != nullptr && index + 1 == pos) {
      // modify pointer to next element
      List *newNext = currPos->next->next;
      currPos->next = newNext;
      index = 0;
      continue; 
    }
    // if the next element is exists - modify pointer
    if (currPos->next != nullptr) {
      currPos = currPos->next;
      index++;
    } else { break; }
  }
}

/* return index of element or -1
 */ 
int find(List *list, int data)
{
  int index = 1;
  List *currPos = list;
  while (currPos != nullptr) {
    if (currPos->payload == data) { return index; }
    else {
      if (currPos->next != nullptr) {
        currPos = currPos->next;
        index++;
      } else { break; }
    }
  }
 
  return -1;
}
