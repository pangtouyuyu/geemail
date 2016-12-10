#include <stddef.h>
#include <string.h>

using namespace std;
   
volatile void *spc_memset(volatile void *dst, int c, size_t len) {
  volatile char *buf;
   
  for (buf = (volatile char *)dst;  len;  buf[--len] = c);
  return dst;
}
   
volatile void *spc_memcpy(volatile void *dst, volatile void *src, size_t len) {
  volatile char *cdst, *csrc;
   
  cdst = (volatile char *)dst;
  csrc = (volatile char *)src;
  while (len--) cdst[len] = csrc[len];
  return dst;
}
   
volatile void *spc_memmove(volatile void *dst, volatile void *src, size_t len) {
  size_t        i;
  volatile char *cdst, *csrc;
   
  cdst = (volatile char *)dst;
  csrc = (volatile char *)src;
  if (csrc > cdst && csrc < cdst + len)
    for (i = 0;  i < len;  i++) cdst[i] = csrc[i];
  else
    while (len--) cdst[len] = csrc[len];
  return dst;
}

volatile void *secureZero(volatile void *dst){
    spc_memset(dst, 0, sizeof(dst));
}

class secure_string {
  public:
  string string_;
  secure_string (void) {}
 
  ~secure_string(void) {
        for(int i = 0; i < string_.length(); i++){
            string_[i]='0';
        }
        cout << "Overwritten string: " << string_ << endl;
        //secureZero(&string_);
        //delete(&string_);
        //string_ = NULL;
  }
 
  string get(void){
        return string_;
  }
  void set(const string str){
      string_ = str;
  }
};
