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
    cout << item << "\n";
    tokens.push_back(item);
  }
  return tokens;
}
