#include "AABBTree.h"
#include "MeshTriangle.h"
#include "CloudPoint.h"
#include <limits.h>
#include <ray_intersect_box.h>
#include <ray_intersect_triangle.h>
#include <iostream>

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const
{
  if(ray_intersect_box(ray, this->box, min_t, max_t)){
    bool left_hit = false, right_hit = false;
    double left_t = std::numeric_limits<double>::infinity();
    double right_t = std::numeric_limits<double>::infinity();
    std::shared_ptr<Object> left_descendant, right_descendant;
    // won't descend into if it doesn't even hit the box
    left_hit = this->left->ray_intersect(ray, min_t, max_t, left_t, left_descendant);
    right_hit = this->right->ray_intersect(ray, min_t, max_t, right_t, right_descendant);

    if (left_hit && right_hit){
      t = left_t < right_t? left_t: right_t;
      descendant = left_t < right_t? left_descendant: right_descendant;
    }
    else if (left_hit){
      t = left_t;
      descendant = left_descendant;
    }
    else if (right_hit){
      t = right_t;
      descendant = right_descendant;
    }
    else
      return false;

    std::shared_ptr<MeshTriangle> mesh_t;
    if (t == left_t && left_hit){
      mesh_t = std::dynamic_pointer_cast<MeshTriangle>(this->left);
      if (mesh_t)
        descendant = this->left;
    }
    if(t == right_t && right_hit){
      mesh_t = std::dynamic_pointer_cast<MeshTriangle>(this->right);
      if (mesh_t)
        descendant = this->right;
    }
    return true;
  }
  return false;
}

