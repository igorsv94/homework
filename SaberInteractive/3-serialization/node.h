#include <iostream>
#include <string>

struct ListNode {
  ListNode    *prev;
  ListNode    *next;
  ListNode    *rand; // pointer to random member or nullptr
  std::string  data;
};

ListNode *NewNode(ListNode *prev, ListNode *next, ListNode *rand,
  std::string data);

/* doubly-linked list with serialization/deserialization support
 */ 
class List {
public:
  List():head(nullptr), tail(nullptr), count(0) {}; // creates an empty list
  List(int N); // create a list with N elements and some data

  void Serialize   (FILE * file); // saves the list in the given file
  void Deserialize (FILE * file); // reads a list from the given file

  void print(); // prints data filed and some kind of representation of
                // rand-field
  void Clear() { // erase all elements from the list
    if (count == 0) {
      return;
    }

    for (auto node = this->head; node != nullptr; node = node->next) {
      delete node;
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
  }

  void TailInsert(std::string data) { // inserts an element into the list
    ListNode *node = NewNode(this->tail, nullptr, nullptr, data);
    if (tail == nullptr) {
      this->head = node;
      this->tail = node;
      count = 1;
    } else {
      this->tail->next = node;
      this->tail = node;
      ++count;
    }
  }

private:
  ListNode *head;
  ListNode *tail;
  int       count;
};
