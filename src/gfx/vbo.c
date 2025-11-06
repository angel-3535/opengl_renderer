#include "vbo.h"

struct VBO vbo_create(GLint type, bool dynamic) {
  struct VBO self;
  glGenBuffers(1, &self.handle);
  self.type = type;
  self.dynamic = dynamic;
  vbo_bind(self);
  return self;
}
void vbo_bind(struct VBO self) { glBindBuffer(self.type, self.handle); }
void vbo_destroy(struct VBO self) { glDeleteBuffers(1, &self.handle); }
void vbo_buffer(struct VBO self, void *data, size_t offset, size_t count) {
  glBufferData(self.type, count, data,
               self.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
