#ifndef GFXWINDOW_H
#define GFXWINDOW_H

#include "../util/types.h"
#include "gfx.h"
#define GLFW_INCLUDE_NONE

#define WINDOW_TITLE "3d Engine"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

struct Button {
  bool down, last;
  u32 pressed_frame;
};

struct Keyboard {
  struct Button keys[GLFW_KEY_LAST];
};

typedef void (*FWindow)(void);
struct Window {
  GLFWwindow *handle;
  struct Keyboard keyboard;
  uv2 size;
  u32 frames;
  FWindow init, destroy, update, render;
};

extern struct Window window;

bool is_key_pressed(i32 key);
bool is_key_down(i32 key);
void window_loop(void);
void window_create(FWindow init, FWindow destroy, FWindow update,
                   FWindow render);
#endif
