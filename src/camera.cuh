#pragma once

#include "point.cuh"
#include "ray.cuh"
#include "vector.cuh"

struct Camera {
  Point3 position;
  Point3 lower_left;
  Vec3 vertical;
  Vec3 horizontal;

  Camera(float vfov, float aspect, Point3 look_from, Point3 look_at);

  __host__ __device__ Ray get_ray(float u, float v) const;
};
