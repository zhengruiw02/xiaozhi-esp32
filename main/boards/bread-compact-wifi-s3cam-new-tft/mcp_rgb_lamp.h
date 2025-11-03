#ifndef __MCP_RGB_LAMP_CONTROLLER_H__
#define __MCP_RGB_LAMP_CONTROLLER_H__

#include "mcp_server.h"

#include <driver/gpio.h>

class RGBLampController {
private:
    bool power_ = false;
    gpio_num_t gpio_num_r;
    gpio_num_t gpio_num_g;
    gpio_num_t gpio_num_b;

public:
    RGBLampController(gpio_num_t gpio_num_r_, gpio_num_t gpio_num_g_, gpio_num_t gpio_num_b_) : gpio_num_r(gpio_num_r_), gpio_num_g(gpio_num_g_), gpio_num_b(gpio_num_b_) {
        gpio_config_t config = {
            .pin_bit_mask = ((1ULL << gpio_num_r) | (1ULL << gpio_num_g) | (1ULL << gpio_num_b)),
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE,
        };
        ESP_ERROR_CHECK(gpio_config(&config));
        gpio_set_level(gpio_num_r, 0);
        gpio_set_level(gpio_num_g, 0);
        gpio_set_level(gpio_num_b, 0);

        auto& mcp_server = McpServer::GetInstance();
        mcp_server.AddTool("self.rgb_lamp.get_state", "Get the power state of the lamp", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
            return power_ ? "{\"power\": true}" : "{\"power\": false}";
        });

        mcp_server.AddTool("self.rgb_lamp.turn_on_white", "Turn on the lamp as white color", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
            power_ = true;
            gpio_set_level(gpio_num_r, 1);
            gpio_set_level(gpio_num_g, 1);
            gpio_set_level(gpio_num_b, 1);
            return true;
        });

        mcp_server.AddTool("self.rgb_lamp.turn_on_red", "Turn on the lamp as red color", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
            power_ = true;
            gpio_set_level(gpio_num_r, 1);
            gpio_set_level(gpio_num_g, 0);
            gpio_set_level(gpio_num_b, 0);
            return true;
        });


        mcp_server.AddTool("self.rgb_lamp.turn_on_green", "Turn on the lamp as green color", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
            power_ = true;
            gpio_set_level(gpio_num_r, 0);
            gpio_set_level(gpio_num_g, 1);
            gpio_set_level(gpio_num_b, 0);
            return true;
        });

        mcp_server.AddTool("self.rgb_lamp.turn_on_blue", "Turn on the lamp as blue color", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
            power_ = true;
            gpio_set_level(gpio_num_r, 0);
            gpio_set_level(gpio_num_g, 0);
            gpio_set_level(gpio_num_b, 1);
            return true;
        });

        mcp_server.AddTool("self.rgb_lamp.turn_off", "Turn off the lamp", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
            power_ = false;
            gpio_set_level(gpio_num_r, 0);
            gpio_set_level(gpio_num_g, 0);
            gpio_set_level(gpio_num_b, 0);
            return true;
        });
    }
};

#endif