
#include "gfx/gfx.h"
#include "gfx/renderer.h"
#include "gfx/shader.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/window.h"
#include "glad/gl.h"
#include "obj/quad2d.h"
#include "state.h"
#include "util/log.h"
#include "util/types.h"
#include <stdio.h>
#include <stdlib.h>

// global application state
struct State g_state;
struct Quad2D quad;

void init(void) {
  LOG_INFO("Initializing application...\n");
  renderer_init(&g_state.renderer);
  renderer_use_shader(&g_state.renderer, SHADER_TEST);
  quad = quad2dt_create("../res/textures/wall.jpg");
}

void destroy(void) {
  LOG_INFO("Destroying application...\n");
  quad2d_destroy(&quad);
  renderer_destroy(&g_state.renderer);
}

void update(void) {
  if (window.keyboard.keys[GLFW_KEY_ESCAPE].down)
    glfwSetWindowShouldClose(window.handle, GLFW_TRUE);
}

void render(void) {
  renderer_clear();
  renderer_use_shader(&g_state.renderer, SHADER_TEST);
  quad2d_draw(&quad);
}

i32 main(i32 argc, char *argv[]) {
  window_create(init, destroy, update, render);
  window_loop();

  return EXIT_SUCCESS;
}
