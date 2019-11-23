
#include <stdint.h>

#include <thread>

#include "morfeus.hpp"

int main(void) {
  MoRFeus morfeus(false);
  /*for (uint32_t i = 0; i < 30; i++) {
    mixer.setFrequency_Hz(1000000000 + i * 1000000);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }*/
  morfeus.enableBiasTee(true);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  morfeus.enableBiasTee(false);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  morfeus.setPower(7);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  morfeus.setLed(MoRFeus::LedSetting::ALWAYS_ON);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  morfeus.setLed(MoRFeus::LedSetting::SLEEP_10);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  morfeus.setLed(MoRFeus::LedSetting::SLEEP_60);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  morfeus.setFunction(MoRFeus::Function::MIXER);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  morfeus.setFunction(MoRFeus::Function::GENERATOR);
}