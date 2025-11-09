

#include "quad2d.h"
#include "gfx/renderer.h"
#include "state.h"
#include "util/log.h"
#include "util/types.h"

static const f32 vertices[] = {
    // inidices        // uv
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // top left
};

static const u32 indices[] = {
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

struct Quad2D quad2d_create(enum QUAD2D_TYPE type) {
  struct Quad2D quad;
  quad.type = type;

  quad.vao = vao_create();
  vao_bind(quad.vao);
  quad.vbo = vbo_create(GL_ARRAY_BUFFER, false);
  vbo_bind(quad.vbo);
  vbo_buffer(quad.vbo, (void *)vertices, 0, sizeof(vertices));

  quad.vbo_indices = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);
  vbo_bind(quad.vbo_indices);
  vbo_buffer(quad.vbo_indices, (void *)indices, 0, sizeof(indices));

  vao_attrib(quad.vao, 2,
             (struct attribute[]){
                 {.size = 3, .type = GL_FLOAT, .normalized = GL_FALSE},
                 {.size = 2, .type = GL_FLOAT, .normalized = GL_FALSE}});
  return quad;
}
void quad2d_destroy(struct Quad2D *quad) {
  vao_destroy(quad->vao);
  vbo_destroy(quad->vbo);
  vbo_destroy(quad->vbo_indices);
}
void quad2d_draw(struct Quad2D *quad) {
  vao_bind(quad->vao);
  if (quad->type == QUAD2D_TEXTURE) {
    renderer_use_shader(&g_state.renderer, SHADER_BASIC_TEXTURE);
    glEnable(GL_TEXTURE_2D);
  }
  renderer_use_shader(&g_state.renderer, SHADER_COLOR);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
