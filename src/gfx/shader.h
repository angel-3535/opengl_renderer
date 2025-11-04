
#ifndef SHADER_H
#define SHADER_H

#include "util/log.h"
#include "util/types.h"
#include <gfx/gfx.h>

typedef struct shader {
  u32 ID;
} shader;

shader createShader(const char *vs, const char *fs);
void useShader(shader *s);

void setBool(const char *name, bool value, shader *s);
void setI32(const char *name, i32 value, shader *s);
void setF32(const char *name, f32 value, shader *s);

#endif // !SHADER_H
