/*
 * DS1307RTC.h - library for DS1307 RTC
 * This library is intended to be used with Arduino Time library functions
 */

#ifndef DS1307RTC_h
#define DS1307RTC_h

#include <TimeLib.h>

typedef enum
{
    sqwInvalid = -1,
    sqwLow = 0,
    sqwHigh,
    sqw1Hz,
    sqw4kHz,
    sqw8kHz,
    sqw32kHz
} sqwOutput_t;

// library interface description
class DS1307RTC
{
  // user-accessible "public" interface
  public:
    DS1307RTC();
    static time_t get();
    static bool set(time_t t);
    static bool read(tmElements_t &tm);
    static bool write(tmElements_t &tm);
    static bool chipPresent() { return exists; }
    static unsigned char isRunning();
    static void setCalibration(char calValue);
    static char getCalibration();

    static void setSqwOutput(sqwOutput_t);
    static sqwOutput_t getSqwOutput(void);
  private:
    static bool exists;
    static uint8_t dec2bcd(uint8_t num);
    static uint8_t bcd2dec(uint8_t num);
};

#ifdef RTC
#undef RTC // workaround for Arduino Due, which defines "RTC"...
#endif

extern DS1307RTC RTC;   // just for the constructor to init Wire

#endif
 

