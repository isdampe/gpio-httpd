#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <ctime>

using namespace std;

vector<string> string_split_to_vector(const string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> tokens;


  while (getline(ss, item, delim))
  {
    if(! item.empty() && *item.rbegin() == '\r') {
      item.erase( item.length()-1, 1);
    }

    if (! item.empty() )
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

string string_trim(const string &str, const string &whitespace = " \t")
{
    const size_t strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    const size_t strEnd = str.find_last_not_of(whitespace);
    const size_t strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

string string_get_datetime()
{
  stringstream ss;

  const time_t t = time(nullptr);
  struct tm *timeinfo;
  timeinfo = localtime(&t);
  ss << put_time(timeinfo, "%a, %d %b %Y %H:%M:%S %Z");

  return ss.str();
}

