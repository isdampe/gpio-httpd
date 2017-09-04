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

string string_replace_all(const string &haystack, const string &needle, const string &replace)
{
  string subject = haystack;
  string::size_type n = 0;
  while ( ( n = subject.find( needle, n ) ) != string::npos )
  {
      subject.replace( n, needle.size(), replace );
      n += replace.size();
  }

  return subject;
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

string string_trim(const string &s, const string &whitespace = " \t")
{
    const size_t str_begin = s.find_first_not_of(whitespace);
    if (str_begin == string::npos)
        return ""; // no content

    const size_t str_end = s.find_last_not_of(whitespace);
    const size_t str_range = str_end - str_begin + 1;

    return s.substr(str_begin, str_range);
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

string string_get_file_extension(const string &file_name)
{
  string result = "";

  size_t strpos = file_name.rfind(".");
  if (strpos == string::npos)
    return result;

  return file_name.substr(strpos +1);

}

string string_file_extension_to_mime_type(string fe)
{
  fe = string_to_lower(fe);
  string mime_type = "application/octet-stream";

  if ( fe == "aac" )
  {
  	mime_type = "audio/aac";
  }
  else if ( fe == "abw" )
  {
  	mime_type = "application/x-abiword";
  }
  else if ( fe == "arc" )
  {
  	mime_type = "application/octet-stream";
  }
  else if ( fe == "avi" )
  {
  	mime_type = "video/x-msvideo";
  }
  else if ( fe == "azw" )
  {
  	mime_type = "application/vnd.amazon.ebook";
  }
  else if ( fe == "bin" )
  {
  	mime_type = "application/octet-stream";
  }
  else if ( fe == "bz" )
  {
  	mime_type = "application/x-bzip";
  }
  else if ( fe == "bz2" )
  {
  	mime_type = "application/x-bzip2";
  }
  else if ( fe == "csh" )
  {
  	mime_type = "application/x-csh";
  }
  else if ( fe == "css" )
  {
  	mime_type = "text/css";
  }
  else if ( fe == "csv" )
  {
  	mime_type = "text/csv";
  }
  else if ( fe == "doc" )
  {
  	mime_type = "application/msword";
  }
  else if ( fe == "eot" )
  {
  	mime_type = "application/vnd.ms-fontobject";
  }
  else if ( fe == "epub" )
  {
  	mime_type = "application/epub+zip";
  }
  else if ( fe == "gif" )
  {
  	mime_type = "image/gif";
  }
  else if ( fe == "html" || fe == "htm" )
  {
  	mime_type = "text/html";
  }
  else if ( fe == "ico" )
  {
  	mime_type = "image/x-icon";
  }
  else if ( fe == "ics" )
  {
  	mime_type = "text/calendar";
  }
  else if ( fe == "jar" )
  {
  	mime_type = "application/java-archive";
  }
  else if ( fe == "jpg" || fe == "jpeg" )
  {
  	mime_type = "image/jpeg";
  }
  else if ( fe == "js" )
  {
  	mime_type = "application/javascript";
  }
  else if ( fe == "json" )
  {
  	mime_type = "application/json";
  }
  else if ( fe == "midi" || fe == "mid" )
  {
  	mime_type = "audio/midi";
  }
  else if ( fe == "mpeg" )
  {
  	mime_type = "video/mpeg";
  }
  else if ( fe == "mpkg" )
  {
  	mime_type = "application/vnd.apple.installer+xml";
  }
  else if ( fe == "odp" )
  {
  	mime_type = "application/vnd.oasis.opendocument.presentation";
  }
  else if ( fe == "ods" )
  {
  	mime_type = "application/vnd.oasis.opendocument.spreadsheet";
  }
  else if ( fe == "odt" )
  {
  	mime_type = "application/vnd.oasis.opendocument.text";
  }
  else if ( fe == "oga" )
  {
  	mime_type = "audio/ogg";
  }
  else if ( fe == "ogv" )
  {
  	mime_type = "video/ogg";
  }
  else if ( fe == "ogx" )
  {
  	mime_type = "application/ogg";
  }
  else if ( fe == "otf" )
  {
  	mime_type = "font/otf";
  }
  else if ( fe == "png" )
  {
  	mime_type = "image/png";
  }
  else if ( fe == "pdf" )
  {
  	mime_type = "application/pdf";
  }
  else if ( fe == "ppt" )
  {
  	mime_type = "application/vnd.ms-powerpoint";
  }
  else if ( fe == "rar" )
  {
  	mime_type = "application/x-rar-compressed";
  }
  else if ( fe == "rtf" )
  {
  	mime_type = "application/rtf";
  }
  else if ( fe == "sh" )
  {
  	mime_type = "application/x-sh";
  }
  else if ( fe == "svg" )
  {
  	mime_type = "image/svg+xml";
  }
  else if ( fe == "swf" )
  {
  	mime_type = "application/x-shockwave-flash";
  }
  else if ( fe == "tar" )
  {
  	mime_type = "application/x-tar";
  }
  else if ( fe == "tiff" || fe == "tif" )
  {
  	mime_type = "image/tiff";
  }
  else if ( fe == "ts" )
  {
  	mime_type = "application/typescript";
  }
  else if ( fe == "ttf" )
  {
  	mime_type = "font/ttf";
  }
  else if ( fe == "vsd" )
  {
  	mime_type = "application/vnd.visio";
  }
  else if ( fe == "wav" )
  {
  	mime_type = "audio/x-wav";
  }
  else if ( fe == "weba" )
  {
  	mime_type = "audio/webm";
  }
  else if ( fe == "webm" )
  {
  	mime_type = "video/webm";
  }
  else if ( fe == "webp" )
  {
  	mime_type = "image/webp";
  }
  else if ( fe == "woff" )
  {
  	mime_type = "font/woff";
  }
  else if ( fe == "woff2" )
  {
  	mime_type = "font/woff2";
  }
  else if ( fe == "xhtml" )
  {
  	mime_type = "application/xhtml+xml";
  }
  else if ( fe == "xlsx" || fe == "xlsx" )
  {
  	mime_type = "application/vnd.ms-excel";
  }
  else if ( fe == "xml" )
  {
  	mime_type = "application/xml";
  }
  else if ( fe == "xul" )
  {
  	mime_type = "application/vnd.mozilla.xul+xml";
  }
  else if ( fe == "zip" )
  {
  	mime_type = "application/zip";
  }
  else if ( fe == "3gp" )
  {
  	mime_type = "video/3gpp";
  }
  else if ( fe == "3g2" )
  {
  	mime_type = "video/3gpp2";
  }
  else if ( fe == "7z" )
  {
  	mime_type = "application/x-7z-compressed";
  }

  return mime_type;

}

string char_to_hex(char c)
{
  string result;
  char first, second;

  first = (c & 0xF0) / 16;
  first += first > 9 ? 'A' - 10 : '0';
  second = c & 0x0F;
  second += second > 9 ? 'A' - 10 : '0';

  result.append(1, first);
  result.append(1, second);

  return result;
}

char hex_to_char(char first, char second)
{
  int digit;

  digit = (first >= 'A' ? ((first & 0xDF) - 'A') + 10 : (first - '0'));
  digit *= 16;
  digit += (second >= 'A' ? ((second & 0xDF) - 'A') + 10 : (second - '0'));
  return static_cast<char>(digit);
}

string url_encode(const string &src)
{
  string result;
  string::const_iterator iter;

  for(iter = src.begin(); iter != src.end(); ++iter)
  {
    switch(*iter)
    {
      case ' ':
        result.append(1, '+');
        break;
        // alnum
      case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
      case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
      case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
      case 'V': case 'W': case 'X': case 'Y': case 'Z':
      case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
      case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
      case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
      case 'v': case 'w': case 'x': case 'y': case 'z':
      case '0': case '1': case '2': case '3': case '4': case '5': case '6':
      case '7': case '8': case '9':
      case '-': case '_': case '.': case '!': case '~': case '*': case '\'':
      case '(': case ')':
        result.append(1, *iter);
        break;
      default:
        result.append(1, '%');
        result.append(char_to_hex(*iter));
        break;
      }
  }

  return result;
}


string url_decode(const string &src)
{
  string result;
  string::const_iterator iter;
  char c;

  for(iter = src.begin(); iter != src.end(); ++iter)
  {
    switch(*iter)
    {
      case '+':
        result.append(1, ' ');
        break;
      case '%':
        // Don't assume well-formed input
        if (std::distance(iter, src.end()) >= 2 && std::isxdigit(*(iter + 1)) &&
            std::isxdigit(*(iter + 2)))
        {
  	       c = *++iter;
  	        result.append(1, hex_to_char(c, *++iter));
        }
        // Just pass the % through untouched
        else
        {
  	       result.append(1, '%');
        }
        break;

      default:
        result.append(1, *iter);
        break;
    }
  }

  return result;
}
