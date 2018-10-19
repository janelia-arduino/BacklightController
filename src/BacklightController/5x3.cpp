// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace backlight_controller
{
namespace constants
{
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=1270,
  .version_major=1,
  .version_minor=0,
};

const long channel_count = CHANNEL_COUNT;

const size_t enable_all_pin = 52;

const size_t channel_pins[CHANNEL_COUNT] =
{
  2,
  6,
  29,
  30,
  35,
  36,
  22,
  23,
  14,
  15,
  16,
  17,
  18,
  19,
  20,
  21,
};

const size_t ir_light_channels[IR_LIGHT_CHANNEL_COUNT] =
{
  8,
  10,
  12,
  14,
};

const size_t visible_light_channels[VISIBLE_LIGHT_CHANNEL_COUNT] =
{
  9,
  11,
  13,
  15,
};

const size_t high_power_channels[HIGH_POWER_CHANNEL_COUNT] =
{
  0,
  1,
  2,
  3,
};

const size_t low_power_channels[LOW_POWER_CHANNEL_COUNT] =
{
  4,
  5,
  6,
  7,
};

// Pins

// Units

// Properties

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
