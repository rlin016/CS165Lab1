//#include <libcrypto>
//#include "hashlib2plus/trunk/src/hashlibpp.h"

//#include <openssl/md5.h>

#include <algorithm>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cmath>

//taking from slides, translating to see what it does; will change to avoid problems LMAO

//moved here for convenience lol you can move it back later if you want, I just wanted to look at it all w/o switching files
const char base64[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

char* 
to64(long v, int n) 
{
  char* ret;  //no actual string in c ig
  for (int i = 1; i < n; i++) {
    ret += base64[v & 0x3f];
      v >>= 6;
  }
  return ret;
}

std::string
md5_crypt(const std::string pw, const std::string salt)
{
  //Trying to use the hashwrapper thing given by the hashlib2plus example
  // hashwrapper *md5Wrapper = new md5wrapper();
  MD5_CTX ctx;
  const std::string magic = "$1$";
  std::string res = pw + magic + salt;
  std::string temp = pw + salt + pw;

  MD5_Init(&ctx);
  MD5_Update(temp, temp.size());
  MD5_Final(h, &ctx);
  
  int l = pw.length();

  // Replace res with the hashed string of pw + salt + pw ??
  std::string sub;
  MD5_Init(&ctx);
  while (l > 0) {
    res = res + h.substr(0, std::min(16, l));
    l = l - 16;
  }
  for (int i = pw.size(); i != 0; i >>= 1) {
    if (i & 1) {
      res += '\x00'; //no idea what this is for... maybe extra conditions for looping? unknown
    }
    else {
      res += pw[0];
    }
  }
  MD5_Update(res, res.size()); //second time hashing the new Alternate (is that word LMAO)
  MD5_Final(h, &ctx);
  
  for (int i = 0; i < 1000; i++) {
    std::string tmp; //temp string
    if (i % 2 == 1) {
      tmp += pw;
    }
    else {
      tmp += h;
    }
    if (i % 3 != 0) {
      tmp += salt;
    }
    if (i % 7 != 0) {
      tmp += pw;
    }
    if (i % 2 == 1) {
      tmp += h;
    }
    else {
      tmp += pw;
    }
    MD5_Init(&ctx);
    MD5_Update(tmp, tmp.size());
    MD5_Update(h, &ctx);
  }
  std::string ret;
  /*strcpy(ret, to64((h[0] << 16) | (h[6] << 8) | (h[12]), 4));
  strcat(ret, to64((h[1] << 16) | (h[7] << 8) | (h[13]), 4));
  strcat(ret, to64((h[2] << 16) | (h[8] << 8) | (h[14]), 4));
  strcat(ret, to64((h[3] << 16) | (h[9] << 8) | (h[15]), 4));
  strcat(ret, to64((h[4] << 16) | (h[10] << 8) | (h[5]), 4));
  strcat(ret, to64(h[11], 2));*/ //I DONT KNOW WHAT THIS DOES REALLY; BASE64 THING?
  return ret;
}
