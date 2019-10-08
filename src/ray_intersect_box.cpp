#include "ray_intersect_box.h"
#include <iostream>

// @ credit - code derived given explanation in book, with extension description
// to the 3D as described by Scratch a Pixel. (https://www.scratchapixel.com/index.php?redirect)
bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  // method extended to 3D case from textbook
  Eigen::Vector3d inv_dir(1.0 / ray.direction(0),
                          1.0 / ray.direction(1),
                          1.0 / ray.direction(2));

  float hit_t_min, hit_t_max, t_y_min, t_y_max, t_z_min, t_z_max; // use float for the +inf/-inf
  float box_x_min = box.min_corner(0);
  float box_y_min = box.min_corner(1);
  float box_z_min = box.min_corner(2);
  float box_x_max = box.max_corner(0);
  float box_y_max = box.max_corner(1);
  float box_z_max = box.max_corner(2);

  // Solve for x/y line intersects
  if (inv_dir(0) > 0){
    hit_t_min = (box_x_min - ray.origin(0)) * inv_dir(0);
    hit_t_max = (box_x_max - ray.origin(0)) * inv_dir(0);
  }
  else{
    hit_t_min = (box_x_max - ray.origin(0)) * inv_dir(0);
    hit_t_max = (box_x_min - ray.origin(0)) * inv_dir(0);
  }
  if (inv_dir(1) > 0){
    t_y_min = (box_y_min - ray.origin(1)) * inv_dir(1);
    t_y_max = (box_y_max - ray.origin(1)) * inv_dir(1);
  }
  else{
    t_y_min = (box_y_max - ray.origin(1)) * inv_dir(1);
    t_y_max = (box_y_min - ray.origin(1)) * inv_dir(1);
  }
  if (inv_dir(2) > 0){
    t_z_min = (box_z_min - ray.origin(2)) * inv_dir(2);
    t_z_max = (box_z_max - ray.origin(2)) * inv_dir(2);
  }
  else{
    t_z_min = (box_z_max - ray.origin(2)) * inv_dir(2);
    t_z_max = (box_z_min - ray.origin(2)) * inv_dir(2);
  }

  if ((hit_t_min > t_y_max) || (t_y_min > hit_t_max))
      return false;
  hit_t_min = t_y_min > hit_t_min? t_y_min: hit_t_min;
  hit_t_max = t_y_max < hit_t_max? t_y_max: hit_t_max;

  // now compare against z
  if ((hit_t_min > t_z_max) || (t_z_min > hit_t_max))
      return false;
  hit_t_min = t_z_min > hit_t_min? t_z_min: hit_t_min;
  hit_t_max = t_z_max < hit_t_max? t_z_max: hit_t_max;


  return (hit_t_min >= min_t <= max_t || hit_t_max >= min_t <= max_t);
}
