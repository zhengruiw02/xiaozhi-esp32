#ifndef SH1106_DISPLAY_H
#define SH1106_DISPLAY_H

#include "display.h"

#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>

class Sh1106Display : public Display {
private:
    esp_lcd_panel_io_handle_t panel_io_ = nullptr;
    esp_lcd_panel_handle_t panel_ = nullptr;

    lv_obj_t* status_bar_ = nullptr;
    lv_obj_t* content_ = nullptr;
    lv_obj_t* container_ = nullptr;
    lv_obj_t* side_bar_ = nullptr;

    const lv_font_t* text_font_ = nullptr;
    const lv_font_t* icon_font_ = nullptr;

    virtual bool Lock(int timeout_ms = 0) override;
    virtual void Unlock() override;

    void SetupUI_128x64();
    void SetupUI_128x32();

public:
    Sh1106Display(void* i2c_master_handle, int width, int height, bool mirror_x, bool mirror_y,
                   const lv_font_t* text_font, const lv_font_t* icon_font);
    ~Sh1106Display();
};

#endif // SH1106_DISPLAY_H
