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
