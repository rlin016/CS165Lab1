//#include <libcrypto>
//#include "hashlib2plus/trunk/src/hashlibpp.h"
//#include "helper.h"
#include <openssl/md5.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//taking from slides, translating to see what it does; will change to avoid problems LMAO

//moved here for convenience lol you can move it back later if you want, I just wanted to look at it all w/o switching files
const char base64[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

char* 
to64(long v, int n) 
{
  char* ret;  //no actual string in c ig
  int i; 
  for (i = 1; i < n; i++) {
    ret += base64[v & 0x3f];
      v >>= 6;
      }
  return ret;
}

char*
md5_crypt(const char* pw, const char* salt)
{
  //Trying to use the hashwrapper thing given by the hashlib2plus example
  // hashwrapper *md5Wrapper = new md5wrapper();
  MD5_CTX ctx;
  const char* magic = "$1$";
  char* res;
  char* h;
  //strcpy(res, pw);
  //strcat(res, magic);
  //strcat(res, salt);

  MD5_Init(&ctx);
  MD5_Update(&ctx, pw, strlen(pw));
  MD5_Update (&ctx, salt, strlen(salt));
  MD5_Update(&ctx, pw, strlen(pw));
  MD5_Final(h, &ctx);
  
  int l = strlen(pw);

  // Replace res with the hashed string of pw + salt + pw ??
  char* sub;
  char* tmp1;
  MD5_Init(&ctx);
  int num = fmin(16.0, 1.0);
  while (l > 0) {
    memcpy(tmp1, h, num);
    h = tmp1;
    strcat(res, sub);
    l = l - 16;
  }
  int i = strlen(pw);
  for (i; i != 0; i >>= 1) {
    if (i & 1) {
      res += '\x00'; //no idea what this is for... maybe extra conditions for looping? unknown
    }
    else {
      res += pw[0];
    }
  }
  MD5_Update(&ctx, res, strlen(res)); //second time hashing the new Alternate (is that word LMAO)
  MD5_Final(h, &ctx);
  
  MD5_Init(&ctx);
  i = 0;
  for (i; i < 1000; i++) {
    char* tmp; //temp string
    if (i % 2 == 1) {
      strcat(tmp,pw);
    }
    else {
      strcat(tmp,h);
    }
    if (i % 3 != 0) {
      strcat(tmp, salt);
    }
    if (i % 7 != 0) {
      strcat(tmp, pw);
    }
    if (i % 2 == 1) {
      strcat(tmp, h);
    }
    else {
      strcat(tmp,pw);
    }
    MD5_Update(&ctx, tmp, strlen(tmp));
  }
 MD5_Final(h, &ctx);
  char* ret;
  strcpy(ret, to64((h[0] << 16) | (h[6] << 8) | (h[12]), 4));
  strcat(ret, to64((h[1] << 16) | (h[7] << 8) | (h[13]), 4));
  strcat(ret, to64((h[2] << 16) | (h[8] << 8) | (h[14]), 4));
  strcat(ret, to64((h[3] << 16) | (h[9] << 8) | (h[15]), 4));
  strcat(ret, to64((h[4] << 16) | (h[10] << 8) | (h[5]), 4));
  strcat(ret, to64(h[11], 2)); //I DONT KNOW WHAT THIS DOES REALLY; BASE64 THING?
  return ret;
}
