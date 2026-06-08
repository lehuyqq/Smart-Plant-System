#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_wifi;
extern const lv_img_dsc_t img_cold;
extern const lv_img_dsc_t img_fire;
extern const lv_img_dsc_t img_sun;
extern const lv_img_dsc_t img_humanity;
extern const lv_img_dsc_t img_light;
extern const lv_img_dsc_t img_rain;
extern const lv_img_dsc_t img_pump;
extern const lv_img_dsc_t img_soil;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[9];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/