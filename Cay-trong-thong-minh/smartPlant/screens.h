#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    _SCREEN_ID_LAST = 1
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *header;
    lv_obj_t *obj0;
    lv_obj_t *time_label;
    lv_obj_t *hour;
    lv_obj_t *symbol;
    lv_obj_t *minute;
    lv_obj_t *thu;
    lv_obj_t *day;
    lv_obj_t *slash;
    lv_obj_t *month;
    lv_obj_t *sensor;
    lv_obj_t *light;
    lv_obj_t *pump;
    lv_obj_t *wifi;
    lv_obj_t *obj1;
    lv_obj_t *rain_collect;
    lv_obj_t *rain_bar;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *temp;
    lv_obj_t *temp_sympol_1;
    lv_obj_t *temp_sympol_2;
    lv_obj_t *stats_soil;
    lv_obj_t *stats_soil_number;
    lv_obj_t *weather;
    lv_obj_t *rain_stats;
    lv_obj_t *soil_img;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/