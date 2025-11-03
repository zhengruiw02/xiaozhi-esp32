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
