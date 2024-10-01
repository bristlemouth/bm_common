#ifndef __BM_UTIL_H__
#define __BM_UTIL_H__

#include <stdbool.h>
#include <stdint.h>
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
#define member_size(type, member) (sizeof(((type *)0)->member))

#define bm_err_check(e, f)                                                     \
  if (e == BmOK) {                                                             \
    e = f;                                                                     \
    if (e != BmOK) {                                                           \
      printf("err: %d at %s:%d\n", e, __FILE__, __LINE__);                     \
    }                                                                          \
  }
#define bm_err_check_print(e, f, format, ...)                                  \
  if (e == BmOK) {                                                             \
    e = f;                                                                     \
    if (e != BmOK) {                                                           \
      printf("err: %d at %s:%d\n" format, e, __FILE__, __LINE__, __VA_ARGS__); \
    }                                                                          \
  }

//TODO: this is a placeholder until ip addresses are figured out
typedef struct {
  uint32_t addr[4];
  uint8_t reserved;
} bm_ip_addr;

extern const bm_ip_addr multicast_global_addr;
extern const bm_ip_addr multicast_ll_addr;

uint32_t time_remaining(uint32_t start, uint32_t current, uint32_t timeout);
bool is_little_endian(void);
void swap_16bit(void *x);
void swap_32bit(void *x);
void swap_64bit(void *x);

//TODO: make this endian agnostic and platform agnostic
/*!
  Extract 64-bit node id from IP address

  \param *ip address to extract node id from
  \return node id
*/
static inline uint64_t ip_to_nodeid(void *ip) {
  uint32_t high_word = ((uint32_t *)(ip))[2];
  uint32_t low_word = ((uint32_t *)(ip))[3];
  if (is_little_endian()) {
    swap_32bit(&high_word);
    swap_32bit(&low_word);
  }
  return (uint64_t)high_word << 32 | (uint64_t)low_word;
}

#endif
