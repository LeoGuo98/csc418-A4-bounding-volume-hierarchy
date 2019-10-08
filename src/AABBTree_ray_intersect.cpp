#include "AABBTree.h"
#include "MeshTriangle.h"
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
    // won't descend into if it doesn't even hit the box
    descendant = this->left;
    left_hit = this->left->ray_intersect(ray, min_t, max_t, left_t, descendant);
    descendant = this->right;
    right_hit = this->right->ray_intersect(ray, min_t, max_t, right_t, descendant);

    if (left_hit && right_hit){
      t = left_t < right_t? left_t: right_t;
      descendant = left_t < right_t? this->left: this->right;
    }
    else if (left_hit){
      descendant = this->left;
      t = left_t;
    }
    else if (right_hit){
      descendant = this->right;
      t = right_t;
    }
    else
      return false;
    std::cout << "T "<<t<<std::endl;
    return true;
  }
  return false;
}

