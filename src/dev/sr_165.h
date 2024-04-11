#pragma once

#include "daisy_core.h"
#include "per/gpio.h"

namespace daisy
{

const size_t kMaxSr165DaisyChain
    = 16; /**< Maximum Number of chained devices Connect device's QH' pin to the next chips serial input*/

/** @addtogroup shiftregister
    @{
    */

/**
   @brief Device Driver for 8-bit shift register. \n
   CD74HC165 - 8-bit  parallel to serial input shift
   @author Nick Donaldson
   @date Apr 2024
   @note Adapted from shensley sr_595 driver
*/
class ShiftRegister165
{
  public:
    struct Config
    {
        Pin data;
        Pin clk;
        Pin load;
    };

    ShiftRegister165() {}
    ~ShiftRegister165() {}

    void Init(const Config& config, size_t num_daisy_chained = 1);

    // /** Sets the state of the specified output.
    //     \param idx The index starts with QA on the first device and ends with QH on the last device.
    // \param state A true state will set the output HIGH, while a false state will set the output LOW.
    // */
    // // void Set(uint8_t idx, bool state);

    void Update();

    inline uint8_t Read(size_t chain_idx = 0) const
    {
        chain_idx = (chain_idx > kMaxSr165DaisyChain - 1) ? kMaxSr165DaisyChain
                                                          : chain_idx;
        return state_[chain_idx];
    }

  private:
    GPIO    data_, clk_, load_;
    uint8_t state_[kMaxSr165DaisyChain];
    size_t  num_devices_;
};

} // namespace daisy
/** @} */
