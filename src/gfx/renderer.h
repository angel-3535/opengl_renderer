
#ifndef RENDERER_H
#define RENDERER_H

#include "gfx/gfx.h"
#include "util/types.h"

#define SHADER_LAST SHADER_BASIC_TEXTURE
enum ShaderType {
  SHADER_NONE = 0,
  SHADER_TEST,
  SHADER_COLOR,
  SHADER_BASIC_TEXTURE,
};

struct Renderer {
  enum ShaderType current_shader;
  u32 shaders[SHADER_LAST + 1];
};

void renderer_init(struct Renderer *renderer);
void renderer_destroy(struct Renderer *renderer);
void renderer_use_shader(struct Renderer *renderer, enum ShaderType type);
void renderer_clear(void);

#endif // !DEBUG
