#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // header
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.header = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 33);
            lv_obj_set_style_bg_color(obj, lv_color_darken(lv_color_hex(0x093f98), 64), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 72, 3);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "SMART PLANT");
        }
        {
            // time_label
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.time_label = obj;
            lv_obj_set_pos(obj, 5, 43);
            lv_obj_set_size(obj, 156, 77);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // hour
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.hour = obj;
            lv_obj_set_pos(obj, 36, 52);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "00");
        }
        {
            // symbol
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.symbol = obj;
            lv_obj_set_pos(obj, 81, 55);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, ":");
        }
        {
            // minute
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.minute = obj;
            lv_obj_set_pos(obj, 93, 52);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "00");
        }
        {
            // thu
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.thu = obj;
            lv_obj_set_pos(obj, 35, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "T5");
        }
        {
            // day
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.day = obj;
            lv_obj_set_pos(obj, 79, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "12");
        }
        {
            // slash
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.slash = obj;
            lv_obj_set_pos(obj, 101, 90);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "/");
        }
        {
            // month
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.month = obj;
            lv_obj_set_pos(obj, 110, 88);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "02");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 5, 130);
            lv_obj_set_size(obj, 155, 100);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_radial(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // sensor
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sensor = obj;
            lv_obj_set_pos(obj, 54, 122);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Sensors");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 170, 130);
            lv_obj_set_size(obj, 143, 100);
            lv_obj_set_style_radius(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 211, 122);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Controls");
        }
        {
            // light
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.light = obj;
            lv_obj_set_pos(obj, 246, 146);
            lv_obj_set_size(obj, 50, 25);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x7b7b7b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_ext_click_area(obj, 15);
        }
        {
            // pump
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.pump = obj;
            lv_obj_set_pos(obj, 247, 190);
            lv_obj_set_size(obj, 50, 25);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x7b7b7b), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_ext_click_area(obj, 15);
        }
        {
            // wifi
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.wifi = obj;
            lv_obj_set_pos(obj, 267, 0);
            lv_obj_set_size(obj, 46, 33);
            lv_image_set_src(obj, &img_wifi);
            lv_image_set_scale(obj, 150);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 500, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 206, 55);
            lv_obj_set_size(obj, 85, 85);
            lv_arc_set_value(obj, 50);
            lv_arc_set_bg_start_angle(obj, 180);
            lv_arc_set_bg_end_angle(obj, 0);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0x26d100), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // rain_collect
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.rain_collect = obj;
            lv_obj_set_pos(obj, 15, 170);
            lv_obj_set_size(obj, 30, 30);
            lv_image_set_src(obj, &img_humanity);
            lv_image_set_scale(obj, 120);
            lv_obj_set_style_image_recolor(obj, lv_color_lighten(lv_color_hex(0x008df4), 0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 500, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // rain_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.rain_bar = obj;
            lv_obj_set_pos(obj, 50, 180);
            lv_obj_set_size(obj, 96, 10);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 186, 135);
            lv_obj_set_size(obj, 48, 48);
            lv_image_set_src(obj, &img_light);
            lv_image_set_scale(obj, 220);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 170, 33);
            lv_obj_set_size(obj, 50, 50);
            lv_image_set_src(obj, &img_cold);
            lv_image_set_scale(obj, 120);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0x1994ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 500, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 276, 41);
            lv_obj_set_size(obj, 41, 37);
            lv_image_set_src(obj, &img_fire);
            lv_image_set_scale(obj, 85);
            lv_obj_set_style_image_recolor(obj, lv_color_hex(0xfc0707), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_image_recolor_opa(obj, 500, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp = obj;
            lv_obj_set_pos(obj, 228, 77);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "0");
        }
        {
            // temp_sympol_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp_sympol_1 = obj;
            lv_obj_set_pos(obj, 255, 72);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "o");
        }
        {
            // temp_sympol_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp_sympol_2 = obj;
            lv_obj_set_pos(obj, 262, 83);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "C");
        }
        {
            // stats_soil
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stats_soil = obj;
            lv_obj_set_pos(obj, 74, 138);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Fine");
        }
        {
            // stats_soil_number
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stats_soil_number = obj;
            lv_obj_set_pos(obj, 81, 155);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "100");
        }
        {
            // weather
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.weather = obj;
            lv_obj_set_pos(obj, 11, 200);
            lv_obj_set_size(obj, 30, 30);
            lv_image_set_src(obj, &img_sun);
            lv_image_set_scale(obj, 120);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // rain_stats
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.rain_stats = obj;
            lv_obj_set_pos(obj, 72, 207);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Sun");
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 186, 178);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_pump);
            lv_image_set_scale(obj, 220);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // soil_img
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.soil_img = obj;
            lv_obj_set_pos(obj, 2, 130);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_soil);
            lv_image_set_scale(obj, 130);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 1) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_main();
}