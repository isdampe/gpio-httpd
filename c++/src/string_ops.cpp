#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

vector<string> string_split_to_vector(const string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> tokens;

  while (getline(ss, item, delim))
  {
    tokens.push_back(item);
  }
  return tokens;
}

string string_to_lower(const string &s)
{
  string result = s; 
  transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

string string_to_upper(const string &s)
{
  string result = s; 
  transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}
