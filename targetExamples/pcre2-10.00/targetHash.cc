// Copyright 2016 Google Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");

#include <string>
#include "pcre2posix.h"

using std::string;

int findParity(int x)
{
  int y = x ^ (x >> 1);
  y = y ^ (y >> 2);
  y = y ^ (y >> 4);
  y = y ^ (y >> 8);
  y = y ^ (y >> 16);

  // Rightmost bit of y holds the parity value
  // if (y&1) is 1 then parity is odd else even
  if (y & 1)
    return 1;
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  if (size < 1) return 0;
  regex_t preg;
    int i,j,c,len,counter=0;
  int x_1=48;
  int x_2=193;
  int x_3=239;

  if (size == -1) {
    printf("Failed to read from stdin\n");
    return(-1);
  }
  int h_1=0,h_2=0,h_3=0;
  for(int a =0; a < size; a++)
    {
      h_1=(h_1 + findParity(x_1&data[a]))%2;
      h_2=(h_2 + findParity(x_2&data[a]))%2;
      h_3=(h_3 + findParity(x_3&data[a]))%2;
    }
  if(h_1==0)
    counter++;
 else
    counter++;
  if(h_2==0)
    counter++;
  else
    counter++;
  if(h_3==0)
    counter++;
  else
    counter++;
  string str(reinterpret_cast<const char*>(data), size);
  string pat(str);
  int flags = data[size/2] - 'a';  // Make it 0 when the byte is 'a'.
  if (0 == regcomp(&preg, pat.c_str(), flags)) {
    regmatch_t pmatch[5];
    regexec(&preg, str.c_str(), 5, pmatch, 0);
    regfree(&preg);
  }
  return 0;
}
