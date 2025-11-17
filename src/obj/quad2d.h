#ifndef QUAD2D_H
#define QUAD2D_H

#include "gfx/texture.h"
#include <gfx/gfx.h>
#include <gfx/vao.h>
#include <gfx/vbo.h>

enum QUAD2D_TYPE { QUAD2D_COLOR, QUAD2D_TEXTURE };

struct Quad2D {
  struct VAO vao;
  struct VBO vbo;
  struct VBO vbo_indices;
  struct Texture texture;
  enum QUAD2D_TYPE type;
};

struct Quad2D quad2d_create();
struct Quad2D quad2dt_create(const char *texture_path);
void quad2d_destroy(struct Quad2D *quad);
void quad2d_draw(struct Quad2D *quad);

#endif // !QUAD2D_H
