#include <string.h>
#include <md5.h>

const base64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

//taken from slides; change later
int to64(v, n) {
  ret = "";
  for (i = 1; i < n) {
    ret += base64[v & 0x3f];
    v >>= 6;
  }
  return ret;
}

int main(int argc, char* argv[]) {

}
