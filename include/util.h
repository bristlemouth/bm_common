#ifndef __BM_UTIL_H__
#define __BM_UTIL_H__

#include <stdbool.h>
#include <stdio.h>

typedef enum {
  BmOK = 0,
  BmEPERM = 1,
  BmENOENT = 2,
  BmEIO = 5,
  BmENXIO = 6,
  BmEAGAIN = 11,
  BmENOMEM = 12,
  BmEACCES = 13,
  BmENODEV = 19,
  BmEINVAL = 22,
  BmENODATA = 61,
  BmENONET = 64,
  BmEBADMSG = 74,
  BmEMSGSIZE = 90,
  BmENETDOWN = 100,
  BmETIMEDOUT = 110,
  BmECONNREFUSED = 111,
  BmEHOSTDOWN = 112,
  BmEHOSTUNREACH = 113,
  BmEALREADY = 114,
  BmEINPROGRESS = 115,
  BmECANCELED = 125,
} BmErr;

#define array_size(x) (sizeof(x) / sizeof(x[0]))

#define bm_err_check(e, f)                                                     \
  if (e == BmOK) {                                                             \
    e = f;                                                                     \
    if (e != BmOK) {                                                           \
      printf("err: %d at %s:%d ", e, __FILE__, __LINE__);                      \
    }                                                                          \
  }
#define bm_err_check_print(e, f, format, ...)                                  \
  if (e == BmOK) {                                                             \
    e = f;                                                                     \
    if (e != BmOK) {                                                           \
      printf("err: %d at %s:%d " format, e, __FILE__, __LINE__, __VA_ARGS__);  \
    }                                                                          \
  }
bool is_little_endian(void);
void swap_16bit(void *x);
void swap_32bit(void *x);
void swap_64bit(void *x);

#endif
