#pragma once
#include "types.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class Game;

class GameObject {
  Game *parent;
  unsigned int VBO, VAO, EBO;
  int type;

public:
  vec2 position;
  double size;
  float rotation;
  GameObject(vec2 position, double size, float rotation, Game *parent,
             int type);
  void render();
  glm::mat4 transform;
};

class Game {
public:
  GLFWwindow *win;
  Game();
  std::vector<GameObject> objects;
  void addObject(GameObject);
  unsigned int shaderProgram;

  void startDraw();
  void endDraw();
};
