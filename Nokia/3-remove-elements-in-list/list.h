#include <string>

struct List {
  struct List *next;
  int payload;

  List(struct List *pNext, int data)
    : next(pNext), payload(data) {}
};

void printList(std::string append, List *list);
void deleteElements(List *list, int pos);
int find(List *list, int data);
