#include <vector>
#include <array>
#include <iostream>

#include "primeNumbers.h"

/* Calculates the first N prime numbers and puts it in passed array.
 * Algorithm is based on sieve of Eratosthenes.
 */ 
void primeNumbers(const int N, std::vector<int> &result)
{
  // set vector size as N+1 and initialize it as 1
  std::vector<int> sieveArr(N + 1, 1);
  sieveArr[0] = sieveArr[1] = 0;

  // indexes is equals to number it's represents
  // so, we need to skip [0,1] indexes
  // elements in the array which marked as '1' is prime numbers
  for (int k = 2; k*k < 2*N; k++) {
    if (sieveArr[k] == 1) {
      for (int j = k*k; j <= N; j += k) {
        sieveArr[j] = 0;
      }
    }
  }

  for (int k = 2; k <= N; k++) {
    if (sieveArr[k] == 1) {
      result.push_back(k);
    }
  }
}

