#include <pangolin/pangolin.h>
#include <torch/torch.h>

#include <iostream>

int main() {
  auto x = torch::zeros({2, 5});
  std::cout << x << std::endl;
  pangolin::CreateWindowAndBind("Viewer", 600, 600);

  glEnable(GL_DEPTH_TEST);

  pangolin::DestroyWindow("Viewer");
  pangolin::QuitAll();
  return 0;
}
