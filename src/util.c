#include "util.h"
#include <stdint.h>

const bm_ip_addr multicast_global_addr = {{0x3FF, 0x0, 0x0, 0x1000000}, 0};
const bm_ip_addr multicast_ll_addr = {{0x2FF, 0x0, 0x0, 0x1000000}, 0};

uint32_t time_remaining(uint32_t start, uint32_t current, uint32_t timeout) {
  int32_t remaining = (int32_t)((start + timeout) - current);

  if (remaining < 0) {
    remaining = 0;
  }

  return remaining;
}

bool is_little_endian(void) {
  static const uint32_t endianness = 1;
  return (*(uint8_t *)&endianness);
}

void swap_16bit(void *x) {
  uint16_t *swp = (uint16_t *)x;
  *swp = (*swp << 8) | (*swp >> 8);
}
void swap_32bit(void *x) {
  uint32_t *swp = (uint32_t *)x;
  *swp = (*swp << 24) | ((*swp & 0xFF00) << 8) | ((*swp >> 8) & 0xFF00) |
         (*swp >> 24);
}
void swap_64bit(void *x) {
  uint64_t *swp = (uint64_t *)x;
  *swp = (*swp << 56) | ((*swp & 0x0000FF00) << 40) |
         ((*swp & 0x00FF0000) << 24) | ((*swp & 0xFF000000) << 8) |
         ((*swp >> 8) & 0xFF000000) | ((*swp >> 24) & 0x00FF0000) |
         ((*swp >> 40) & 0x0000FF00) | (*swp >> 56);
}

// leap year calulator expects year argument as years offset from 1970
#define LEAP_YEAR(Y)                                                           \
  (((1970 + Y) > 0) && !((1970 + Y) % 4) &&                                    \
   (((1970 + Y) % 100) || !((1970 + Y) % 400)))

#define SECS_PER_MIN (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY (SECS_PER_HOUR * 24UL)
#define MICROSECONDS_PER_SECOND (1000000)

static const uint8_t MONTH_DAYS[] = {
    31, 28, 31, 30, 31, 30, 31,
    31, 30, 31, 30, 31}; // API starts months from 1, this array starts from 0
static const uint8_t MONTH_DAYS_LEAP_YEAR[] = {
    31, 29, 31, 30, 31, 30, 31,
    31, 30, 31, 30, 31}; // API starts months from 1, this array starts from 0

/*!
  Convert date (YYYYMMDDhhmmss) into unix timestamp(UTC)

  \param[in] year - Full year (2022, for example)
  \param[in] month - Month starting at 1
  \param[in] day - Day starting at 1
  \param[in] hour - Hour starting at 0 and ending at 23
  \param[in] minute - Minute starting at 0 and ending at 59
  \param[in] second - Minute starting at 0 and ending at 59
  \return UTC seconds since Jan 1st 1970 00:00:00
*/
uint32_t utc_from_date_time(uint16_t year, uint8_t month, uint8_t day,
                            uint8_t hour, uint8_t minute, uint8_t second) {
  int i;
  uint32_t seconds;

  // seconds from 1970 till 1 jan 00:00:00 of the given year
  seconds = (year - 1970) * (SECS_PER_DAY * 365);
  for (i = 1970; i < year; i++) {
    if (LEAP_YEAR(i - 1970)) {
      seconds += SECS_PER_DAY; // add extra days for leap years
    }
  }

  // add days for this year, months start from 1
  for (i = 1; i < month; i++) {
    if ((i == 2) && LEAP_YEAR(year - 1970)) {
      seconds += SECS_PER_DAY * 29;
    } else {
      seconds +=
          SECS_PER_DAY * MONTH_DAYS[i - 1]; //monthDay array starts from 0
    }
  }
  seconds += (day - 1) * SECS_PER_DAY;
  seconds += hour * SECS_PER_HOUR;
  seconds += minute * SECS_PER_MIN;
  seconds += second;
  return seconds;
}

#define DAYS_PER_YEAR (365)
#define DAYS_PER_LEAP_YEAR (DAYS_PER_YEAR + 1)

static uint32_t get_days_for_year(uint32_t year) {
  return LEAP_YEAR(year - 1970) ? DAYS_PER_LEAP_YEAR : DAYS_PER_YEAR;
}

static const uint8_t *get_days_per_month(uint32_t year) {
  return LEAP_YEAR(year - 1970) ? MONTH_DAYS_LEAP_YEAR : MONTH_DAYS;
}

/*!
  Convert unix timestamp(UTC) in microseconds to date (YYYYMMDDhhmmss)

  \param[in] utc_us - utc in microseconds
  \param[out] UtcDateTime - date time
  \return None
*/
void date_time_from_utc(uint64_t utc_us, UtcDateTime *date_time) {
  // TODO - Do we really need this?
  // configASSERT(dateTime);

  // year
  uint64_t days = (utc_us / MICROSECONDS_PER_SECOND) / SECS_PER_DAY;
  date_time->year = 1970;
  while (days >= get_days_for_year(date_time->year)) {
    days -= get_days_for_year(date_time->year);
    date_time->year++;
  }

  // months
  const uint8_t *monthDays = get_days_per_month(date_time->year);
  date_time->month = 1;
  while (days >= monthDays[date_time->month - 1]) {
    days -= monthDays[date_time->month - 1];
    date_time->month++;
  }

  // days
  date_time->day = days + 1;

  uint64_t secondsRemaining = (utc_us / MICROSECONDS_PER_SECOND) % SECS_PER_DAY;
  // hours
  date_time->hour = secondsRemaining / SECS_PER_HOUR;

  // minutes
  date_time->min = (secondsRemaining / SECS_PER_MIN) % SECS_PER_MIN;

  // seconds
  date_time->sec = secondsRemaining % SECS_PER_MIN;

  // useconds
  date_time->usec = utc_us % MICROSECONDS_PER_SECOND;
}