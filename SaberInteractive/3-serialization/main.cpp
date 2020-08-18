#include "node.h"

int main(void)
{
 {// open file and serialize a list
    FILE *outfile = fopen("list.sr", "w+b");
    if (outfile != nullptr) {
      List *myList = new List(10);
      myList->print();

      myList->Serialize(outfile);

      fclose(outfile);
    }
  }

  {// open file and deserialize a list
    List *recoveredList = new List();
    FILE *outfile = fopen("list.sr", "r+b");
    if (outfile != nullptr) {
      recoveredList->Deserialize(outfile);
      std::cout << "recovered list: " << std::endl;
      recoveredList->print();
      fclose(outfile);
    }
  }

  return 0;
}
