// Copyright 2016 Google Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");
#include <string>
#include "re2/re2.h"

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

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int i,j,c,len,counter=0;
  int x_1=48;
  int x_2=193;
  int x_3=239;

  if (size == -1) {
    //printf("Failed to read from stdin\n");
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



  if (size < 3 || size > 64) return 0;
  uint16_t f = (data[0] << 16) + data[1];
  RE2::Options opt;
  opt.set_log_errors(false);
  if (f & 1) opt.set_encoding(RE2::Options::EncodingLatin1);
  opt.set_posix_syntax(f & 2);
  opt.set_longest_match(f & 4);
  opt.set_literal(f & 8);
  opt.set_never_nl(f & 16);
  opt.set_dot_nl(f & 32);
  opt.set_never_capture(f & 64);
  opt.set_case_sensitive(f & 128);
  opt.set_perl_classes(f & 256);
  opt.set_word_boundary(f & 512);
  opt.set_one_line(f & 1024);
  const char *b = reinterpret_cast<const char*>(data) + 2;
  const char *e = reinterpret_cast<const char*>(data) + size;
  std::string s1(b, e);
  RE2 re(s1, opt);
  if (re.ok())
    RE2::FullMatch(s1, re);
  return 0;
}
