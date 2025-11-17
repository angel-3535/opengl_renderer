
#include "glad/gl.h"
#include "util/log.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <gfx/texture.h>

struct Texture texture_lff(const char *path) {
  struct Texture t;
  glGenTextures(1, &t.handle);
  glBindTexture(GL_TEXTURE_2D, t.handle);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  u8 *data = stbi_load(path, &t.size[0], &t.size[1], &t.channels, 0);

  if (!data) {
    LOG_AND_EXIT("FAILED TO GENERATE TEXTURE FROM PATH: %s", path);
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t.size[0], t.size[1], 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  return t;
}

void texture_destroy(struct Texture *texture) {
  glDeleteTextures(1, &texture->handle);
}

void texture_bind(struct Texture *texture) {
  glBindTexture(GL_TEXTURE_2D, texture->handle);
}

void texture_arr_bind(struct Texture *texture[], size_t count) {
  for (size_t i = 0; i < count; i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, texture[i]->handle);
  }
}
