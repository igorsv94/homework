#include <vector>
#include <string_view>
#include <map>

std::vector<std::string_view>
splitSV(std::string_view strv, std::string_view delims = " ");

std::map<int,int> parse(std::string_view text); 
