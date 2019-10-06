#include "AABBTree.h"
#include <ray_intersect_box.h>

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const
{
  t = 0;
  return false;
}

