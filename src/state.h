#ifndef STATE_H
#define STATE_H

#include "gfx/renderer.h"
#include "gfx/window.h"
struct State {
  struct Window *window;
  struct Renderer renderer;
};

extern struct State g_state;

#endif // !STATE_H
