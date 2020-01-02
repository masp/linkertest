#include "wrap.h"
#include <iostream>

extern "C" {

DLL_PUBLIC int WRAP(add)(int a, int b) {
  std::cout << "hello from CPP" << std::endl;
  return REAL(add)(a, b);
}

}
