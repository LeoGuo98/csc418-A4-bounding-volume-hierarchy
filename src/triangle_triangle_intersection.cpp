#include "triangle_triangle_intersection.h"
#include "Ray.h"
#include "ray_intersect_triangle.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  // Simply, construct a 'ray' for each edge of the second triangle
  // and use the ray intersect triangle function, where min/max are defined
  // by the line that edge
  double min_t = 0, max_t = 1, t;
  Ray ray(Eigen::Vector3d(0, 0, 0), Eigen::Vector3d(0, 0, 0));

  ray.origin = B0;
  ray.direction = B1 - B0;
  if(ray_intersect_triangle(ray, A0, A1, A2, min_t, max_t, t))
    return true;

  ray.origin = B1;
  ray.direction = B2 - B1;
  if(ray_intersect_triangle(ray, A0, A1, A2, min_t, max_t, t))
    return true;

  ray.origin = B0;
  ray.direction = B2 - B0;
  if(ray_intersect_triangle(ray, A0, A1, A2, min_t, max_t, t))
    return true;

  return false; 
}
