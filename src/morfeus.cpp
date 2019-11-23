#include "morfeus.hpp"

#include <cstring>
#include <stdexcept>

enum MoRFeusFunction : uint8_t {
  frequency = 0x81,
  function = 0x82,
  power = 0x83,
  bias = 0x84,
  leds = 0x85
};

MoRFeus::MoRFeus(bool fastInit) {
  if (hid_init()) throw(std::runtime_error("could not init hid"));

  handle = hid_open(0x10c4, 0xeac9, NULL);

  if (!handle) {
    throw(std::runtime_error("could not open device"));
  }

  if (not fastInit) {
    // device is not yet activated and will only read back values
    setFrequency_Hz(100000000);
    setPower(0);
    setLed(LedSetting::ALWAYS_ON);
    setFunction(Function::MIXER);
    enableBiasTee(false);
  }

  lock = false;
}

MoRFeus::~MoRFeus() {
  hid_close(handle);
  hid_exit();
}

uint32_t MoRFeus::getFrequency_Hz() { return actualFrequency; }

void MoRFeus::setFrequency_Hz(uint32_t freq) {
  data[1] = MoRFeusFunction::frequency;

  memset(&data[2], 0, 4);

  data[6] = freq >> 24;
  data[7] = freq >> 16;
  data[8] = freq >> 8;
  data[9] = freq;

  io();

  actualFrequency = data[6] << 24;
  actualFrequency += data[7] << 16;
  actualFrequency += data[8] << 8;
  actualFrequency += data[9];
}

void MoRFeus::setPower(uint8_t pwr) {
  data[1] = MoRFeusFunction::power;
  memset(&data[2], pwr, 8);

  io();

  power = data[9];
}

void MoRFeus::enableBiasTee(bool bias) {
  data[1] = MoRFeusFunction::bias;
  memset(&data[2], (uint8_t)bias, 8);

  io();

  biasTee = (bool)data[9];
}

void MoRFeus::setLed(LedSetting m) {
  data[1] = MoRFeusFunction::leds;
  memset(&data[2], m, 8);

  io();

  led = (LedSetting)data[9];
}

void MoRFeus::setFunction(MoRFeus::Function f) {
  data[1] = MoRFeusFunction::function;
  memset(&data[2], f, 8);

  io();

  function = (Function)data[9];
}

void MoRFeus::io() {
  data[0] = lock ? 0x72 : 0x77;

  hid_write(handle, data, 16);
  hid_read(handle, data, 16);
}