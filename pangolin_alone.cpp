#include <pangolin/pangolin.h>

#include <iostream>

int main() {
  pangolin::CreateWindowAndBind("Viewer", 600, 600);

  glEnable(GL_DEPTH_TEST);

  pangolin::DestroyWindow("Viewer");
  pangolin::QuitAll();
  return 0;
}
