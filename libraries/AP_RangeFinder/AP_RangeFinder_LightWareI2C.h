#pragma once

#include "RangeFinder.h"
#include "RangeFinder_Backend.h"
#include <AP_HAL/I2CDevice.h>

class AP_RangeFinder_LightWareI2C : public AP_RangeFinder_Backend
{

public:
    // static detection function
    static AP_RangeFinder_Backend *detect(RangeFinder::RangeFinder_State &_state,
                                          AP_HAL::OwnPtr<AP_HAL::I2CDevice> dev);

    // update state
    void update(void);

protected:

    virtual MAV_DISTANCE_SENSOR _get_mav_distance_sensor_type() const override {
        return MAV_DISTANCE_SENSOR_LASER;
    }

private:
    // constructor
    AP_RangeFinder_LightWareI2C(RangeFinder::RangeFinder_State &_state, AP_HAL::OwnPtr<AP_HAL::I2CDevice> dev);

    bool write_bytes(uint8_t *write_buf_u8, uint32_t len_u8);
    bool fx20_disable_address_tagging();
    bool fx20_product_name_check();
    bool fx20_send_and_expect(const char* send, const char* expected_reply);
    bool fx20_set_lost_signal_confirmations();
    bool fx20_wait_on_reply(uint8_t *rx_two_bytes);
    bool init();
    bool legacy_init();
    bool fx20_init();
    void legacy_timer();
    void fx20_timer();

    // get a reading
    bool legacy_get_reading(uint16_t &reading_cm);
    bool fx20_get_reading(uint16_t &reading_cm);
    AP_HAL::OwnPtr<AP_HAL::I2CDevice> _dev;
};
