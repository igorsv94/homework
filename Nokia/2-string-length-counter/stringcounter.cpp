#include <vector>
#include <string_view>
#include <map>
#include <algorithm>
#include <iostream>

#include "stringcounter.h"

/* returns a vector of words, which are contained in strv
 */ 
std::vector<std::string_view>
splitSV(std::string_view strv, std::string_view delims)
{
  std::vector<std::string_view> output;
  size_t first = 0;

  while (first < strv.size())
  {
    const auto second = strv.find_first_of(delims, first);

    if (first != second) {
      output.emplace_back(strv.substr(first, second-first));
    }

    if (second == std::string_view::npos) {
      break;
    }

    first = second + 1;
  }

  return output;
}

bool compare(std::string_view &a, std::string_view &b) 
{
  return a.size() > b.size();
}

/* counts the number of words in the text for each word length.
 * and prints it.
 *
 * return a map, which contain the difference between word length and length of
 * longest word as a key, and count of words as a value
 */
std::map<int, int> parse(std::string_view text) 
{
  auto splittedText = splitSV(text);

  std::sort(splittedText.begin(), splittedText.end(), compare);
  // should do I remove equal strings?

  // set maxLength as longest substring
  int maxLength = splittedText.front().size();

  // this map contains the difference between word length and length of longest
  // word as a key, and count of words as a value
  std::map<int, int> summaryMap;
  for (auto &item: splittedText) {
    int lenDiff = maxLength - item.size();
    if (lenDiff > 0) {
      summaryMap[lenDiff]++;
    }
  }

  for (auto &it: summaryMap) {
    std::cout << it.second
              << " words with shorter than longest on "
              << it.first
              << " letters" << std::endl;
  }

  return summaryMap;
}
