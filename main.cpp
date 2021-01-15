#include <string>
//#include <md5.h>

const char base64[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

//taken from slides; change later
std::string to64(long v, int n) {
  std::string ret = "";  //no actual string in c ig

  for (int i = 1; i < n; i++) {
    ret += base64[v & 0x3f];
    v >>= 6;
  }
  return ret;
}

int main(int argc, char* argv[]) {


  return 0;
}
