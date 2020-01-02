#include "wrap.h"
#include <iostream>

extern "C" {

DLL_PUBLIC int add(int a, int b) {
  std::cout << "hello from CPP" << std::endl;
  return wrap_add(a, b);
}

}
