#include "AABBTree.h"
#include "insert_box_into_box.h"
#include "ray_intersect_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth):
  depth(std::move(a_depth)),
  num_leaves(objects.size())
{
  int objects_size = objects.size();
  for (int i = 0; i < objects_size; i++){
  }
}

bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const
{
  t = 0;
  return(this->ray_intersect(ray, min_t, max_t, t, descendant));
}
