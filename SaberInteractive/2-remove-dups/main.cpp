#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* removes duplicated symbols in the given char array. easy to read
 */
void RemoveDups(char *str)
{
  char *resStr = (char*)malloc(strlen(str)); //allocate a buffer for result
  int j = 0; // index in the result string
  /* walk through the given string and copy not duplicated symbols */
  for (int i = 0; str[i] != '\0'; ++i) {
    if (str[i] != str[i+1]) {
      resStr[j++] = str[i]; // copy, if the aren't equals
    }
  }

  resStr[++j] = '\0'; // put null-terminator at the end
  strncpy(str, resStr, j); // copy result by provided link,
                           // length is already calculated

  free(resStr); // free an allocated memory for result string
}

/* removes duplicated symbols in the given char array. optimized
*/
void RemoveDups2(char *pStr)
{
  int readIndex = 1, writeIndex = 0;
  //search a symbol that does not equal to a current symbol (in pStr[writeIndex])
  for (; pStr[readIndex] != '\0'; ++readIndex) {
    if (pStr[readIndex] != pStr[writeIndex]) {
      pStr[++writeIndex] = pStr[readIndex];
    }
  }
  pStr[writeIndex + 1] = '\0';
}

int main(void)
{
  char data[] = "AAA BBB AAA";
  printf("orig: %s\n", data);
  RemoveDups(data);
  printf("result: %s\n", data); // “A B A”


  char test[] = "aAbbCDee kpoAAGGGGGe";
  printf("\norig: %s\n", test);
  RemoveDups2(test);
  printf("result: %s\n", test); // aAbCDe kpoAGe

  char test2[] = "";
  test2[0] = '\0';
  RemoveDups2(test2);
  printf("\nresult: %s\n", test2); // ""

  return 0;
}
