#include "gfx/shader.h"
#include "util/log.h"
#include <gfx/renderer.h>

void renderer_init(struct Renderer *renderer) {
  renderer->current_shader = SHADER_NONE;
  // Load shaders
  LOG_INFO("Initializing Renderer...\n");

  renderer->shaders[SHADER_TEST] =
      shader_create("../res/shader/vertex.glsl", "../res/shader/fragment.glsl")
          .ID;

  renderer->shaders[SHADER_COLOR] =
      shader_create("../res/shader/color_vertex.glsl",
                    "../res/shader/color_fragment.glsl")
          .ID;
  renderer->shaders[SHADER_BASIC_TEXTURE] =
      shader_create("../res/shader/texture_vertex.glsl",
                    "../res/shader/texture_fragment.glsl")
          .ID;
  LOG_GOOD("Renderer initialized successfully\n");
}
void renderer_destroy(struct Renderer *renderer) {
  LOG_INFO("Destroying Renderer...\n");
  for (size_t i = 0; i <= SHADER_LAST; i++) {
    glDeleteProgram(renderer->shaders[i]);
  }
  LOG_GOOD("Renderer destroyed successfully\n");
}
void renderer_use_shader(struct Renderer *renderer, enum ShaderType type) {
  if (renderer->current_shader == type) {
    return;
  }
  renderer->current_shader = type;
  shader_use(&(shader){.ID = renderer->shaders[type]});
}
void renderer_clear(void) {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
