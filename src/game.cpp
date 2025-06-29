#include "engine.h"
#include "primitives.h"
#include "types.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <vector>

void Game::addObject(GameObject object) { this->objects.push_back(object); }

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "uniform mat4 model;\n"
                                 "void main(){\n"
                                 "  gl_Position = model * vec4(aPos, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

Game::Game() {
  this->win = makeWindow();

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "failed to init glad" << std::endl;
  }
  std::cout << "started shader" << std::endl;
  int success;
  char infoLog[512];
  unsigned int fragmentShader, vertexShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT\n" << infoLog << std::endl;
  }
  std::cout << "one shader" << std::endl;

  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX\n" << infoLog << std::endl;
  }

  this->shaderProgram = glCreateProgram();
  glAttachShader(this->shaderProgram, fragmentShader);
  glAttachShader(this->shaderProgram, vertexShader);
  glLinkProgram(this->shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  std::cout << "finished shader" << std::endl;
}

GameObject::GameObject(vec2 position, double size, float rotation, Game *parent,
                       int type) {
  this->position = position;
  this->size = size;
  this->rotation = rotation;
  this->parent = parent;
  this->type = type;
  if (this->type == TRIANGLE) {
    createTriangle(&this->VAO, &this->VBO);
  } else if (this->type == RECT) {
    createRect(&this->VAO, &this->VBO, &this->EBO);
  }
  parent->addObject(*this);
}

void GameObject::render() {
  /*
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "fumble" << std::endl;
    }

    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f,
    0.0f};

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    std::cout << "ok" << std::endl;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void
    *)0); glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  */
  // model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
  // model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0, 1.0, 0.0));
  /*
  while (!glfwWindowShouldClose(this->parent->win)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(this->parent->shaderProgram);
    this->transform = glm::mat4(1.0f);
    // model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
    this->transform = glm::rotate(this->transform, (float)glfwGetTime(),
                                  glm::vec3(0.0, 0.0, 1.0));
    GLuint modelLoc =
        glGetUniformLocation(this->parent->shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->transform));
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(this->parent->win);
    glfwPollEvents();
  }
*/
  glUseProgram(this->parent->shaderProgram);
  this->transform = glm::mat4(1.0f);
  this->transform = glm::translate(
      transform, glm::vec3(this->position.x, this->position.y, 0));
  this->transform = glm::rotate(this->transform, glm::radians(this->rotation),
                                glm::vec3(0.0, 0.0, 1.0));
  this->transform = glm::scale(transform, glm::vec3(this->size, this->size, 0));
  GLuint modelLoc = glGetUniformLocation(this->parent->shaderProgram, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->transform));
  glBindVertexArray(this->VAO);
  if (this->type == TRIANGLE) {
    glDrawArrays(GL_TRIANGLES, 0, 3);
  } else if (this->type == RECT) {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
  glfwPollEvents();
}

void Game::startDraw() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Game::endDraw() {
  glfwSwapBuffers(this->win);
  glfwPollEvents();
}
