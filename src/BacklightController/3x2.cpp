// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

namespace backlight_controller
{
namespace constants
{
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=1271,
  .version_major=1,
  .version_minor=0,
};

const long channel_count = CHANNEL_COUNT;

const size_t enable_all_pin = 2;

const size_t channel_pins[CHANNEL_COUNT] =
{
  3,
  4,
  5,
  6,
  14,
  15,
  16,
  17,
  18,
  19,
};

const size_t ir_backlight_channels[IR_BACKLIGHT_CHANNEL_COUNT] =
{
  8,
};

const size_t visible_backlight_channels[VISIBLE_BACKLIGHT_CHANNEL_COUNT] =
{
  9,
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
const long ir_backlight_power_max_default[IR_BACKLIGHT_CHANNEL_COUNT] =
{
  ir_backlight_power_max_element_default,
};

const long visible_backlight_power_max_default[VISIBLE_BACKLIGHT_CHANNEL_COUNT] =
{
  visible_backlight_power_max_element_default,
};

const long high_power_power_max_default[HIGH_POWER_CHANNEL_COUNT] =
{
  high_power_power_max_element_default,
  high_power_power_max_element_default,
  high_power_power_max_element_default,
  high_power_power_max_element_default,
};

const long low_power_power_max_default[LOW_POWER_CHANNEL_COUNT] =
{
  low_power_power_max_element_default,
  low_power_power_max_element_default,
  low_power_power_max_element_default,
  low_power_power_max_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
