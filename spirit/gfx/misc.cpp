#include "misc.h"

std::string file_to_string(const char *filename) {
  std::ifstream is(filename);
  std::string ret;

  is.seekg(0, std::ios::end);
  ret.reserve(is.tellg());
  is.seekg(0, std::ios::beg);

  ret.assign((std::istreambuf_iterator<char>(is)),
             std::istreambuf_iterator<char>());

  return ret;
}