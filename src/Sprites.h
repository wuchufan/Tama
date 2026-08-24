#pragma once
#include <Arduino.h>

// 'kuchipachi_animation1'/'kuchipachi_animation2', 100x100px, RGB565
extern const uint16_t idle_0[] PROGMEM;
extern const uint16_t idle_1[] PROGMEM;

extern const uint16_t smile_0 [] PROGMEM;
extern const uint16_t smile_1 [] PROGMEM;

extern const uint16_t* const idle_frames[];
extern const uint16_t* const smile_frames[];

extern const int IDLE_FRAME_COUNT;
extern const int SMILE_FRAME_COUNT;
extern const int SPRITE_SIZE[];

// 'main_background', 240x240px, RGB565
extern const uint16_t main_background[] PROGMEM;