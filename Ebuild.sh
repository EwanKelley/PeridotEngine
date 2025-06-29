g++ -c -fPIC -lglfw3 -lGL -lGLU -lm src/*.cpp src/glad.c &&
  echo "done 1" &&
  g++ -shared -lglfw3 -lGL -lGLU -lm -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor -o libengine.so *.o &&
  echo "done 2" &&
  g++ src/main.cpp -L. -lengine -lglfw3 -o exec &&
  rm *.o
