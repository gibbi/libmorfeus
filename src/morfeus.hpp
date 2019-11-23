#ifndef MoRFeus_HPP
#define MoRFeus_HPP

#include <stdint.h>

#ifdef WIN32
#include <windows.h>
#endif
#include <hidapi/hidapi.h>
#include <stdio.h>
#include <stdlib.h>

class MoRFeus {
 public:
  enum Function : uint8_t { MIXER = 0x00, GENERATOR = 0x01 };

  enum LedSetting : uint8_t {
    ALWAYS_ON = 0x00,
    SLEEP_10 = 0x01,
    SLEEP_60 = 0x02
  };

  MoRFeus(bool);
  ~MoRFeus();

  uint32_t getFrequency_Hz();
  void setFrequency_Hz(uint32_t);
  void setPower(uint8_t);
  void setLed(LedSetting);
  void setFunction(MoRFeus::Function f);
  void enableBiasTee(bool);

 private:
  void io();

  uint32_t actualFrequency;
  uint8_t power;
  bool biasTee;

  bool lock = true;

  Function function;
  LedSetting led;

  uint8_t data[16];

  hid_device* handle;
};

#endif