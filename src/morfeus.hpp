#ifndef MoRFeus_HPP
#define MoRFeus_HPP

#include <stdint.h>

#include <fstream>

class MoRFeus {
 public:
  enum Function : uint8_t { MIXER = 0x00, GENERATOR = 0x01 };

  enum LedSetting : uint8_t {
    ALWAYS_ON = 0x00,
    SLEEP_10 = 0x01,
    SLEEP_60 = 0x02
  };

  MoRFeus(std::string device, bool);
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

  std::fstream dev;
  uint8_t data[16];
};

#endif