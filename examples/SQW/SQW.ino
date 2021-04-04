#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

// the SQW output of the RTC has to be wired to an interrupt pin of
// the arduino, that pin has to be configured below (default pin 2)

#define RTC_SQW_PIN    2    // pin 2 (square wave generator -> interrupt)

volatile boolean rtcFlag = false;

void rtcTimerIsr()
{
  rtcFlag = true;
}

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC SQW output Test");
  Serial.println("-------------------------");

  tmElements_t tm;
  if (!RTC.read(tm))
  {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
  }

  // 1 Hz to trigger only every second
  RTC.setSqwOutput(sqw1Hz);
  
  // configure interrupt pin
  pinMode(RTC_SQW_PIN, INPUT);
  digitalWrite(RTC_SQW_PIN, HIGH);
  attachInterrupt(digitalPinToInterrupt(RTC_SQW_PIN), rtcTimerIsr, RISING);
}

void loop() {
  tmElements_t tm;

  // 1s RTC timer
  if (rtcFlag)
  {
    rtcFlag = false;

    RTC.read(tm);
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  }
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}