// #include "iot/thing.h"
// #include "board.h"
// #include "audio_codec.h"

// #include <esp_log.h>

// #define TAG "RGB"

// namespace iot {

// // 这里仅定义 RGB 的属性和方法，不包含具体的实现
// class RGB : public Thing {
// public:
//     RGB() : Thing("RGB", userDev2Name) {
//         // 定义设备的属性
//         properties_.AddNumberProperty("color", "当前颜色", [this]() -> int {
//             return Board::GetInstance().GetRGBColor();
//         });

//         // 定义设备可以被远程执行的指令
//         methods_.AddMethod("SetColor", "设置颜色", ParameterList({
//             Parameter("color", "由三个字节组成第一个字节为红色第二个字节为绿色第三个字节为蓝色, 格式为0xRRGGBB", kValueTypeNumber, true)
//         }), [this](const ParameterList& parameters) {
//             Board::GetInstance().SetRGBColor(static_cast<int32_t>(parameters["color"].number()));
//         });
//     }
// };

// } // namespace iot

// DECLARE_THING(RGB);


// #ifndef __MCP_RGB_STRIP_CONTROLLER_H__
// #define __MCP_RGB_STRIP_CONTROLLER_H__

// #include "mcp_server.h"

// #include <driver/gpio.h>

// #define TAG "MCP_RGB_STRIP"


// class RGBStripController {
// private:
//     bool power_ = false;
//     gpio_num_t gpio_num_;

// public:
//     RGBStripController(gpio_num_t gpio_num) : gpio_num_(gpio_num) {
//         gpio_config_t config = {
//             .pin_bit_mask = (1ULL << gpio_num_),
//             .mode = GPIO_MODE_OUTPUT,
//             .pull_up_en = GPIO_PULLUP_DISABLE,
//             .pull_down_en = GPIO_PULLDOWN_DISABLE,
//             .intr_type = GPIO_INTR_DISABLE,
//         };
//         ESP_ERROR_CHECK(gpio_config(&config));
//         gpio_set_level(gpio_num_, 0);

//         auto& mcp_server = McpServer::GetInstance();
//         mcp_server.AddTool("self.rgb_strip.get_state", "Get the power state of the rgb strip", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
//             return power_ ? "{\"power\": true}" : "{\"power\": false}";
//         });

//         mcp_server.AddTool("self.rgb_strip.turn_on", "Turn on the rgb strip", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
//             power_ = true;
//             gpio_set_level(gpio_num_, 1);
//             return true;
//         });

//         mcp_server.AddTool("self.rgb_strip.turn_off", "Turn off the rgb strip", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
//             power_ = false;
//             gpio_set_level(gpio_num_, 0);
//             return true;
//         });
//     }
// };

// class RGBStripController {
// private:
//     bool power_ = false;
//     gpio_num_t gpio_num_;

// public:
//     RGBStripController(gpio_num_t gpio_num_r_, gpio_num_t gpio_num_g_, gpio_num_t gpio_num_b_) : gpio_num_r(gpio_num_r_), gpio_num_g(gpio_num_g_), gpio_num_b(gpio_num_b_) {
//         gpio_config_t config = {
//             .pin_bit_mask = ((1ULL << gpio_num_r) | (1ULL << gpio_num_g) | (1ULL << gpio_num_b)),
//             .mode = GPIO_MODE_OUTPUT,
//             .pull_up_en = GPIO_PULLUP_DISABLE,
//             .pull_down_en = GPIO_PULLDOWN_DISABLE,
//             .intr_type = GPIO_INTR_DISABLE,
//         };
//         ESP_ERROR_CHECK(gpio_config(&config));
//         gpio_set_level(gpio_num_r, 0);
//         gpio_set_level(gpio_num_g, 0);
//         gpio_set_level(gpio_num_b, 0);

//         auto& mcp_server = McpServer::GetInstance();
//         mcp_server.AddTool("self.rgb_lamp.get_state", "Get the power state of the lamp", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
//             return power_ ? "{\"power\": true}" : "{\"power\": false}";
//         });

//         mcp_server.AddTool("self.rgb_lamp.turn_on_white", "Turn on the lamp as white color", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
//             power_ = true;
//             gpio_set_level(gpio_num_r, 1);
//             gpio_set_level(gpio_num_g, 1);
//             gpio_set_level(gpio_num_b, 1);
//             return true;
//         });

//         mcp_server.AddTool("self.rgb_lamp.turn_on_red", "Turn on the lamp as red color", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
//             power_ = true;
//             gpio_set_level(gpio_num_r, 1);
//             gpio_set_level(gpio_num_g, 0);
//             gpio_set_level(gpio_num_b, 0);
//             return true;
//         });


//         mcp_server.AddTool("self.rgb_lamp.turn_on_green", "Turn on the lamp as green color", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
//             power_ = true;
//             gpio_set_level(gpio_num_r, 0);
//             gpio_set_level(gpio_num_g, 1);
//             gpio_set_level(gpio_num_b, 0);
//             return true;
//         });

//         mcp_server.AddTool("self.rgb_lamp.turn_on_blue", "Turn on the lamp as blue color", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
//             power_ = true;
//             gpio_set_level(gpio_num_r, 0);
//             gpio_set_level(gpio_num_g, 0);
//             gpio_set_level(gpio_num_b, 1);
//             return true;
//         });

//         mcp_server.AddTool("self.rgb_lamp.turn_off", "Turn off the lamp", PropertyList(), [this](const PropertyList& properties) -> ReturnValue {
//             power_ = false;
//             gpio_set_level(gpio_num_r, 0);
//             gpio_set_level(gpio_num_g, 0);
//             gpio_set_level(gpio_num_b, 0);
//             return true;
//         });
//     }
// };

// #endif