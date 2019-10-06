#include "AABBTree.h"
#include "insert_box_into_box.h"

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
}
