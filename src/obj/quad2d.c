

#include "quad2d.h"
#include "gfx/renderer.h"
#include "state.h"
#include "util/log.h"
#include "util/types.h"

static const f32 vertices_tex[] = {
    // inidices        // uv
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // top left
};

static const f32 vertices_col[] = {
    // inidices       //  Color

    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
    0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, // top right
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 1.0f  // top left
};

static const u32 indices[] = {
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

struct Quad2D quad2d_create() {
  struct Quad2D quad;
  quad.type = QUAD2D_COLOR;

  quad.vao = vao_create();
  vao_bind(quad.vao);
  quad.vbo = vbo_create(GL_ARRAY_BUFFER, false);
  vbo_bind(quad.vbo);
  vbo_buffer(quad.vbo, (void *)vertices_col, 0, sizeof(vertices_col));

  quad.vbo_indices = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);
  vbo_bind(quad.vbo_indices);
  vbo_buffer(quad.vbo_indices, (void *)indices, 0, sizeof(indices));

  vao_attrib(quad.vao, 2,
             (struct attribute[]){
                 {.size = 3, .type = GL_FLOAT, .normalized = GL_FALSE},
                 {.size = 3, .type = GL_FLOAT, .normalized = GL_FALSE}});
  return quad;
}

struct Quad2D quad2dt_create(const char *texture_path) {
  struct Quad2D quad;
  quad.type = QUAD2D_TEXTURE;
  quad.texture = texture_lff(texture_path);

  quad.vao = vao_create();
  vao_bind(quad.vao);
  quad.vbo = vbo_create(GL_ARRAY_BUFFER, false);
  vbo_bind(quad.vbo);
  vbo_buffer(quad.vbo, (void *)vertices_tex, 0, sizeof(vertices_tex));

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
  switch (quad->type) {
  case QUAD2D_COLOR:
    renderer_use_shader(&g_state.renderer, SHADER_COLOR);
    break;
  case QUAD2D_TEXTURE:
    renderer_use_shader(&g_state.renderer, SHADER_BASIC_TEXTURE);
    texture_bind(&quad->texture);
    glEnable(GL_TEXTURE_2D);
    break;
  default:
    LOG_ERROR("Unknown Quad2D type: %d\n", quad->type);
    return;
  }

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
