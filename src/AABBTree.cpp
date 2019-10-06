#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth):
  depth(std::move(a_depth)),
  num_leaves(objects.size())
{
  int objects_size = objects.size();
  if (objects_size > 1){
    for (int i = 0; i < objects_size; i++){
      insert_box_into_box(objects[i]->box, this->box);
    }

    auto x_axis_len = this->box.max_corner(0) - this->box.min_corner(0);
    auto x_axis_midpoint = x_axis_len / 2.0;
    auto y_axis_len = this->box.max_corner(1) - this->box.min_corner(1);
    auto y_axis_midpoint = y_axis_len / 2.0;
    auto z_axis_len = this->box.max_corner(2) - this->box.min_corner(2);
    auto z_axis_midpoint = z_axis_len / 2.0;
    std::vector<std::shared_ptr<Object>> left;
    std::vector<std::shared_ptr<Object>> right;
    std::shared_ptr<Object> object;
    for (int i = 0; i < objects_size; i++){
      object = objects[i];
      if(x_axis_len > y_axis_len && x_axis_len > z_axis_len){
        if (object->box.center()(0) < x_axis_midpoint)
          left.push_back(object);
        else
          right.push_back(object);
      }
      else if (y_axis_len > z_axis_len){
        if (object->box.center()(1) < y_axis_midpoint)
          left.push_back(object);
        else
          right.push_back(object);
      }
      else{
        if (object->box.center()(2) < z_axis_midpoint)
          left.push_back(object);
        else
          right.push_back(object);
      }
    }
    if (left.size() == 1)
      this->left = left[0];
    else
      *this->left = AABBTree(left, a_depth + 1);
    if (right.size() == 1)
      this->right = right[0];
    else
      *this->right = AABBTree(right, a_depth + 1);
  }
}
