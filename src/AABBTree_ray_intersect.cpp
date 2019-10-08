#include "AABBTree.h"
#include "MeshTriangle.h"
#include <ray_intersect_box.h>
#include <ray_intersect_triangle.h>

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const
{
  t = 0;
  // TODO CloudPoint
  if(ray_intersect_box(ray, this->box, min_t, max_t)){
    // try to cast the left/right to an AABB tree
    bool left_hit = false, right_hit = false;
    double left_t, right_t;
    if (this->left != NULL)
      left_hit = this->left->ray_intersect(ray, min_t, max_t, left_t, descendant);
    if (this->right != NULL)
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
    return true;
  }
  return false;
}

