#include "camera.cuh"
#include "obj.cuh"
#include "render.cuh"
#include "tri_array.cuh"
#include "triangle.cuh"

#include <cmath>
#include <filesystem>
#include <iostream>
#include <vector>

int main() {
  auto scene = load_obj("res/teapot.obj");

  Camera cam(M_PI / 4.0, 1.0, { 0, 5, 5.83 }, { 0, 0, 0 });

  Image out = render(scene.primitives, cam, 1920, 1080);
  out.to_png("output.png");
  return 0;
}
