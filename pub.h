//
// Created by masp on 12/28/19.
//

#ifndef LINKERSCRIPTSTEST__PUB_H
#define LINKERSCRIPTSTEST__PUB_H

#if __GNUC__ >= 4
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define DLL_PUBLIC
#define DLL_LOCAL
#endif

#ifdef __cplusplus
extern "C"
{
#endif

DLL_PUBLIC extern int add(int a, int b);

#ifdef __cplusplus
};
#endif

#endif // LINKERSCRIPTSTEST__PUB_H
