#include <Eigen/Geometry>
#include "ray_intersect_triangle.h"

bool intersect_plane(
  const Ray & ray, const double min_t, const double max_t, const Eigen::RowVector3d &plane_point, const Eigen::RowVector3d &plane_normal, double & t)
{
    // From A2
  Eigen::RowVector3d e = ray.origin, d = ray.direction;

    double numerator = (plane_point - e).dot(plane_normal);
    double denumerator = d.dot(plane_normal);
    if (0 <= denumerator && denumerator<= 1e-6){
        if (0 <= numerator && numerator <= 1e-6){
            // ray lines in the plane
            // not sure if this is the right way to handle this or not
            t = min_t;
            return true;
        }else // they never intersect
            return false;
    }
    // They intersect, check if >= min_t
    t = numerator / denumerator;
    if (t >= min_t && t <= max_t){
        return true;
    }
    return false;
}

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  // Replace with your code here:
  // t = 0;

  Eigen::RowVector3d q = B - A;
  Eigen::RowVector3d p = C - A;
  Eigen::RowVector3d tri_n = (q).cross(p).normalized();
  double plane_t;
  if (intersect_plane(ray, min_t, max_t, A, tri_n, plane_t)){
      // we now need to check and see if the the ray is inside the
      // triangle
      Eigen::RowVector3d point = ray.origin + plane_t * ray.direction;
      Eigen::RowVector3d edge0 = B - A;
      Eigen::RowVector3d edge1 = C - B;
      Eigen::RowVector3d edge2 = A - C;

      Eigen::RowVector3d x0 = point - A;
      Eigen::RowVector3d x1 = point - B;
      Eigen::RowVector3d x2 = point - C;

      if (tri_n.dot(edge0.cross(x0)) > 0 &&
          tri_n.dot(edge1.cross(x1)) > 0 &&
          tri_n.dot(edge2.cross(x2)) > 0){
          t = plane_t;
          return true;
      }
  }
  return false;
}
