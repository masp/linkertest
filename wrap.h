//
// Created by masp on 1/1/20.
//

#ifndef LINKERSCRIPTSTEST__WRAP_H
#define LINKERSCRIPTSTEST__WRAP_H

#ifdef _WIN32
#define WRAP(x) __wrap_##x
#define REAL(x) x
#else
#define WRAP(x) x
#define REAL(x) __wrap_##x
#endif

#ifndef _WIN32
// since linux doesn't have the same priority semantics as windows, it's necessary to modify the static library
// using objcopy to generate the correct names as well as modify the header file internally so we can reference both
// the wrapped and real
#define add REAL(add)
#endif
#include "pub.h"
#ifndef _WIN32
#undef add
#endif

#endif // LINKERSCRIPTSTEST__WRAP_H
