#pragma once

#include "camera.cuh"
#include "image.cuh"
#include "tri_array.cuh"
#include "triangle.cuh"

Image render(TriangleArray primitives, Camera cam, unsigned int w, unsigned int h);
