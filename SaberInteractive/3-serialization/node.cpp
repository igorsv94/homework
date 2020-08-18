#include <vector>
#include <stdio.h>
#include "node.h"

#define SERIALIZED_NULLPTR -1 // to show that variable is linked to nullptr

/* serializes a list 
 */ 
void List::Serialize(FILE *file)
{
  // if the list is empty or provided file descriptor is invalid
  if (this->count == 0 || file == nullptr) {
    return;
  }

  fwrite(&this->count, sizeof(this->count), 1, file);
  int offset = 0;
  // walk through the List and write a data,
  // and an offset (for ListNode::rand field)
  for (auto node = head; node != nullptr; node = node->next) {
    // here is offset is a sequence number
    *reinterpret_cast<int*>(&(node->prev)) = offset;
    ++offset;
    fwrite(&node->data, sizeof(node->data), 1, file);
  }

  for (auto node = head; node != nullptr; node = node->next) {
    // here is offset is an offset from the head, to show up rand-field link
    if (node->rand != nullptr) {
      offset = *reinterpret_cast<int*>(&(node->rand->prev));
    } else {
      offset = SERIALIZED_NULLPTR; // -1 is kind equal to nullptr
    }
   
    fwrite(&offset, sizeof(offset), 1, file);
  }
}

/* deserialize a list
 */ 
void List::Deserialize(FILE *file)
{
  if (file == nullptr) { // if provided file descriptor is invalid
    return;
  }
  
  Clear(); // we should clear the list before initializing

  int length = -1; // count of elements of the list in file
  fread(&length, sizeof(length), 1, file);
  if (length < 0) {
    return;
  }

  std::vector<ListNode*> pointers; //a vector that stores an elements
  pointers.reserve(length + 1); //reserve memory for elements
  std::string data; // buffer-string that stores current data of one element

  // read $length elements from file and add it to the list
  for (int index = 0; index < length; ++index) {
    fread(&data, sizeof(data), 1, file);
    TailInsert(data); // inset an element into the list
    pointers.push_back(tail);
  }

  int index = SERIALIZED_NULLPTR;//stores a ListNode::rand field of one element
  for (auto node = head; node != nullptr; node = node->next) {
    fread(&index, sizeof(index), 1, file);
    assert(index < count);
    if (index == SERIALIZED_NULLPTR) {
      node->rand = nullptr;
    } else {
      node->rand = pointers[index];
    }
  }
}

/* helper-function that returns a new node and fills it with given values.
 */ 
ListNode *NewNode(ListNode *prev, ListNode *next, ListNode *rand,
  std::string data)
{
  ListNode *node = new ListNode();
  node->prev = prev;
  node->next = next;
  node->rand = rand;
  node->data = data;
  return node;
}

/* helper-function. Create a List-object with N elements, with some data.
 */ 
List::List(int N)
{
  this->head = new ListNode();
  this->head->prev = nullptr;
  this->head->next = nullptr;
  this->head->rand = nullptr;
  this->head->data = "1";

  this->tail = this->head;
  count = 1;

  ListNode *curr = this->head;
  for (int i = 2; i <= N; ++i) {
    ListNode * node = new ListNode();
    node->prev = curr;
    node->next = nullptr;
    node->rand = this->tail;

    node->data = std::to_string(i);
    curr->next = node;
    curr = node;
    this->tail = curr;
    ++count;
  }
  this->tail->rand = nullptr;
}

/* helper-function that prints field data and some kind of
* representation of rand-filed
*/
void List::print()
{
  if (this->head == nullptr) {
    return;
  }

  ListNode *curr = this->head;
  while (curr != nullptr) {
    std::cout << curr->data
              << ", rand link to: "
              << ((curr->rand == nullptr)? "nullptr" : curr->rand->data)
              << std::endl;

    curr = curr->next;
  }
}


