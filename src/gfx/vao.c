#include "vao.h"
#include <util/log.h>

struct VAO vao_create() {
  struct VAO self;
  glGenVertexArrays(1, &self.handle);
  vao_bind(self);
  return self;
}
void vao_destroy(struct VAO self) { glDeleteVertexArrays(1, &self.handle); }
void vao_bind(struct VAO self) { glBindVertexArray(self.handle); }

void vao_attrib(struct VAO self, size_t ammount, struct attribute attr[]) {
  vao_bind(self);
  GLsizei stride = 0;
  void *offset = 0;
  for (size_t i = 0; i < ammount; i++) {
    attr[i].index = i;
    LOG_INFO("Attribute %u: size=%d, type=%u, normalized=%u\n", attr[i].index,
             attr[i].size, attr[i].type, attr[i].normalized);
    stride += attr[i].size * sizeof(attr[i].type);
  }

  for (size_t i = 0; i < ammount; i++) {
    glVertexAttribPointer(i, attr[i].size, attr[i].type, attr[i].normalized,
                          stride, offset);
    glEnableVertexAttribArray(i);
    offset += attr[i].size * sizeof(attr[i].type);
  }
}
