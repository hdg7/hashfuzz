// Copyright 2016 Google Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");
#include <stddef.h>
#include <stdint.h>

#include "woff2_dec.h"

int findParity(int x)
{
  int y = x ^ (x >> 1);
  y = y ^ (y >> 2);
  y = y ^ (y >> 4);
  y = y ^ (y >> 8);
  y = y ^ (y >> 16);

  if (y & 1)
    return 1;
  return 0;
}

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::string buf;
  woff2::WOFF2StringOut out(&buf);
  out.SetMaxSize(30 * 1024 * 1024);
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

  woff2::ConvertWOFF2ToTTF(data, size, &out);
  return 0;
}
