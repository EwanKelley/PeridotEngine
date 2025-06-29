#include "engine.h"
#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

void print(const char *string) { std::cout << string << std::endl; }

GLFWwindow *makeWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *win = glfwCreateWindow(800, 800, "test", NULL, NULL);
  glfwMakeContextCurrent(win);
  return win;
}
