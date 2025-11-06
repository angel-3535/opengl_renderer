
#include "gfx/gfx.h"
#include "gfx/shader.h"
#include "gfx/vao.h"
#include "gfx/vbo.h"
#include "gfx/window.h"
#include "glad/gl.h"
#include "util/log.h"
#include "util/types.h"
#include <stdio.h>
#include <stdlib.h>

struct Window window;

f32 vertices[] = {
    // positions         // colors
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f, // top left
    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, // top right
};

u32 indices[] = {
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

struct VBO vbo;
struct VBO vbo_indices;
struct VAO vao;
shader shader_program;

void init(void) {

  LOG_INFO("Initializing application...\n");
  shader_program =
      createShader("../res/shader/vertex.glsl", "../res/shader/fragment.glsl");

  useShader(&shader_program);
  LOG_GOOD("Using shader program ID: %u\n", shader_program.ID);

  vao = vao_create();
  vbo = vbo_create(GL_ARRAY_BUFFER, false);
  vbo_indices = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);
  vbo_buffer(vbo_indices, indices, 0, sizeof(indices));
  vbo_buffer(vbo, vertices, 0, sizeof(vertices));
  vao_attrib(vao, 2,
             (struct attribute[]){
                 {.size = 3, .type = GL_FLOAT, .normalized = GL_FALSE},
                 {.size = 3, .type = GL_FLOAT, .normalized = GL_FALSE}});
}

void destroy(void) {
  LOG_INFO("Destroying application...\n");
  vao_destroy(vao);
  vbo_destroy(vbo);
}

void update(void) {
  if (window.keyboard.keys[GLFW_KEY_ESCAPE].down)
    glfwSetWindowShouldClose(window.handle, GLFW_TRUE);
}

void render(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  useShader(&shader_program);
  vao_bind(vao);
  // glDrawArrays(GL_TRIANGLES, 0, 4);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

i32 main(i32 argc, char *argv[]) {
  window_create(init, destroy, update, render);
  window_loop();

  return EXIT_SUCCESS;
}
