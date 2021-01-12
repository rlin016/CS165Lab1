#include <md5.h>
#include <string.h>
#include <stdio.h>

//taking from slides, translating to see what it does; will change to avoid problems LMAO
char*
md5_crypt(const char* pw, const char* salt)
{
  res = password + "$1$" + salt;
  h = MD5(password + salt + password); //maybe use MD5 library here?
  l = strlen(pw);
  ("Length of pw: %d", l); //checks to see if strlen works with const char... will write own if not

  //not sure what this section does...
  while (l > 0) {
    res = res + substr(h, 0, min(16, l)); //what do i need to use substr?
    l = l - 16;
  }
  for (i = strlen(pw); i != 0; i >>= 1) {
    if (i & 1) {
      res += '\x00'; //no idea what this is for... maybe extra conditions for looping? unknown
    }
    else {
      res += password[0];
    }
  }
  h = MD5(res); //second time hashing the new Alternate (is that word LMAO)

  for (i = 0; i < 1000; i++) {
    tmp = ""; //temp string
    if (i % 2 == 1) {
      tmp += password;
    }
    else {
      tmp += h;
    }
    if (i % 3 != 0) {
      tmp += salt;
    }
    if (i % 7 != 0) {
      tmp += password;
    }
    if (i % 2 == 1) {
      tmp += h;
    }
    else {
      tmp += password;
    }
    h = MD5(tmp);
  }

  return to64((h[0] << 16) |
	      (h[6] << 8) | (h[12]), 4) + to64((h[1] << 16) |
					       (h[7] << 8) | (h[13]), 4) + to64((h[2] << 16) |
										(h[8] << 8) | (h[14]), 4) + to64((h[3] << 16) |
														 (h[9] << 8) | (h[15]), 4) + to64((h[4] << 16) |
																		  (h[10] << 8) | (h[5]), 4) + to64(h[11], 2); //I DONT KNOW WHAT THIS DOES REALLY; BASE64 THING?

}
