#include "engine.h"
#include "game.h"
#include "primitives.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
  print("test");
  Game game = Game();
  GameObject obj = GameObject({0.0f, 0.0f}, 1.0f, 45.0f, &game, RECT);
  GameObject obj2 = GameObject({0.5f, 0.0f}, 1.0f, 45.0f, &game, TRIANGLE);
  while (1) {
    game.startDraw();
    obj.render();
    obj2.render();
    game.endDraw();
    obj.size += 0.0001;
    obj.rotation += 0.1;
  };
  return 0;
}
