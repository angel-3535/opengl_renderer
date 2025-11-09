#include "shader.h"
#include "glad/gl.h"
#include "util/log.h"
#include "util/types.h"
#include <stdio.h>
#include <stdlib.h>

GLuint _shader_compile(const char *filepath, GLenum type) {
  i32 success;
  char infoLog[512];

  LOG_INFO("Reading Shader Source File: %s\n", filepath);
  FILE *fptr = fopen(filepath, "rb");
  if (fptr == NULL)
    LOG_AND_EXIT("Couldn't Open Vertex Shader Source File\n");

  fseek(fptr, 0, SEEK_END);
  long length = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);

  char *src = calloc(1, length);
  if (!src) {
    fclose(fptr);
    LOG_AND_EXIT("Coulnt allocate memory for vertex shader\n");
  }

  fread(src, 1, length, fptr);
  fclose(fptr);

  LOG_INFO("Compiling Shader...\n");
  LOG_INFO("Shader Source Length: %ld bytes\n", length);
  LOG_WARN("Shader Source:\n%s\n", src);
  GLuint handle = glCreateShader(type);
  glShaderSource(handle, 1, (const GLchar *const *)&src,
                 (const GLint *)&length);
  glCompileShader(handle);

  glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
  LOG_INFO("Checking vertex shader compile status...\n");
  if (!success) {
    glGetShaderInfoLog(handle, 512, NULL, infoLog);
    free(src);
    LOG_AND_EXIT("VERTEX SHADER ERROR: %s\n", infoLog);
  }

  free(src);
  return handle;
}

shader shader_create(const char *vs, const char *fs) {
  LOG_INFO("Creating shader program from \nvertex shader: %s \nand \nfragment "
           "shader: %s\n",
           vs, fs);
  int success;
  char infoLog[512];

  LOG_INFO("Compiling vertex shader...\n");
  u32 vs_prog = _shader_compile(vs, GL_VERTEX_SHADER);
  LOG_GOOD("VERTEX SHADER COMPILED SUCCESSFULLY\n");

  LOG_INFO("Compiling fragment shader...\n");
  u32 fs_prog = _shader_compile(fs, GL_FRAGMENT_SHADER);
  LOG_GOOD("FRAGMENT SHADER COMPILED SUCCESSFULLY\n");

  u32 shader_prog = glCreateProgram();
  glAttachShader(shader_prog, vs_prog);
  glAttachShader(shader_prog, fs_prog);

  glLinkProgram(shader_prog);

  glUseProgram(shader_prog);

  LOG_GOOD("SHADER PROGRAM LINKED SUCCESSFULLY\n");
  return (shader){.ID = shader_prog};
}

void shader_use(shader *s) { glUseProgram(s->ID); }

void setBool(const char *name, bool value, shader *s) {
  glUniform1i(glGetUniformLocation(s->ID, name), (i32)value);
}
void setI32(const char *name, i32 value, shader *s) {
  glUniform1i(glGetUniformLocation(s->ID, name), value);
}
void setF32(const char *name, f32 value, shader *s) {
  glUniform1f(glGetUniformLocation(s->ID, name), value);
}
