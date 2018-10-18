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
