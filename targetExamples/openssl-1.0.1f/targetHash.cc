// Copyright 2016 Google Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

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

SSL_CTX *Init() {
  SSL_library_init();
  SSL_load_error_strings();
  ERR_load_BIO_strings();
  OpenSSL_add_all_algorithms();
  SSL_CTX *sctx;
  assert (sctx = SSL_CTX_new(TLSv1_method()));
  /* These two file were created with this command:
      openssl req -x509 -newkey rsa:512 -keyout server.key \
     -out server.pem -days 9999 -nodes -subj /CN=a/
  */
  assert(SSL_CTX_use_certificate_file(sctx, "runtime/server.pem",
                                      SSL_FILETYPE_PEM));
  assert(SSL_CTX_use_PrivateKey_file(sctx, "runtime/server.key",
                                     SSL_FILETYPE_PEM));
  return sctx;
}
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  static SSL_CTX *sctx = Init();
  SSL *server = SSL_new(sctx);
  BIO *sinbio = BIO_new(BIO_s_mem());
  BIO *soutbio = BIO_new(BIO_s_mem());
  SSL_set_bio(server, sinbio, soutbio);
  SSL_set_accept_state(server);
      int i,j,c,len,counter=0;
  int x_1=48;
  int x_2=193;
  int x_3=239;


  if (Size == -1) {
    printf("Failed to read from stdin\n");
    return(-1);
  }
  int h_1=0,h_2=0,h_3=0;
  for(int a =0; a < Size; a++)
    {
      h_1=(h_1 + findParity(x_1&Data[a]))%2;
      h_2=(h_2 + findParity(x_2&Data[a]))%2;
      h_3=(h_3 + findParity(x_3&Data[a]))%2;
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

  BIO_write(sinbio, Data, Size);
  SSL_do_handshake(server);
  SSL_free(server);
  return 0;
}
