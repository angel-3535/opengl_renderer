
#ifndef VAO_H
#define VAO_H

#include "gfx/gfx.h"
struct attribute {
  GLuint index;
  GLint size;
  GLenum type;
  GLboolean normalized;
};
struct VAO {
  GLuint handle;
};

struct VAO vao_create();
void vao_bind(struct VAO vao);
void vao_destroy(struct VAO vao);
void vao_attrib(struct VAO self, size_t ammount, struct attribute attr[]);

#endif // !VAO_H
