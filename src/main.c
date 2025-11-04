
#include "gfx/gfx.h"
#include "gfx/shader.h"
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
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
};

u32 VBO;
u32 VAO;
shader shader_program;

void init(void) {

  LOG_INFO("Initializing application...\n");
  shader_program =
      createShader("../res/shader/vertex.glsl", "../res/shader/fragment.glsl");

  useShader(&shader_program);
  LOG_GOOD("Using shader program ID: %u\n", shader_program.ID);
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(f32),
                        (void *)(3 * sizeof(f32)));
  glEnableVertexAttribArray(1);
}
void destroy(void) {}

void update(void) {
  if (window.keyboard.keys[GLFW_KEY_ESCAPE].down)
    glfwSetWindowShouldClose(window.handle, GLFW_TRUE);
}

void render(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  useShader(&shader_program);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

i32 main(i32 argc, char *argv[]) {
  window_create(init, destroy, update, render);
  window_loop();

  return EXIT_SUCCESS;
}
