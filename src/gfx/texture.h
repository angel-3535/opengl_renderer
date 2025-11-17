
#ifndef TEXTURE_H
#define TEXTURE_H

#include "util/types.h"
#include <cglm/cglm.h>
#include <gfx/gfx.h>

struct Texture {
  u32 handle;
  i32 channels;
  ivec2 size;
};

// load texture from file
struct Texture texture_lff(const char *path);
void texture_destroy(struct Texture *texture);
void texture_arr_bind(struct Texture *texture[], size_t count);
void texture_bind(struct Texture *texture);

#endif
