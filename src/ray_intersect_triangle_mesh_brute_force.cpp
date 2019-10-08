#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <limits.h>
#include <iostream>
#include <math.h>

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  hit_t = 0;
  hit_f = 0;

  bool ret;
  int f_rows = F.rows();
  double best_t = std::numeric_limits<double>::infinity();

  Eigen::RowVector3d a, b, c; // vertices of triangle
  for (int i = 0; i < f_rows; i++){
    // for (int j = 0; j < 3; j++){
    //   a(j) = V(F(i, 0), j);
    //   b(j) = V(F(i, 1), j);
    //   c(j) = V(F(i, 2), j);
    // }
    a = V.row(F(i, 0));
    b = V.row(F(i, 1));
    c = V.row(F(i, 2));
    if (ray_intersect_triangle(ray, a, b, c, min_t, max_t, hit_t)){
      if (hit_t < best_t){
        best_t = hit_t;
        hit_f = i;
      }
    }
  }
  hit_t = best_t;
  return (!isinf(best_t));
}
