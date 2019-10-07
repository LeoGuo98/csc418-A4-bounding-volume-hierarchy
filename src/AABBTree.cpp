#include <iostream>
#include <assert.h>
#include "AABBTree.h"
#include <Eigen/Geometry>
#include "insert_box_into_box.h"
#include <math.h>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth):
  depth(std::move(a_depth)),
  num_leaves(objects.size())
{
  int objects_size = objects.size();
  if (objects_size <= 1)
    exit(1);
  else{
    for (int i = 0; i < objects_size; i++){
      // Every object has a 'box'. MeshTriangle grows it on construction
      insert_box_into_box(objects[i]->box, this->box);
    }

    auto x_axis_len = this->box.max_corner.normalized()(0) - \
                      this->box.min_corner.normalized()(0);
    auto x_axis_midpoint = x_axis_len / 2.0;
    auto y_axis_len = this->box.max_corner.normalized()(1) - \
                      this->box.min_corner.normalized()(1);
    auto y_axis_midpoint = y_axis_len / 2.0;
    auto z_axis_len = this->box.max_corner.normalized()(2) - \
                      this->box.min_corner.normalized()(2);
    auto z_axis_midpoint = z_axis_len / 2.0;
    assert(!isinf(x_axis_len) && "X axis inf");
    assert(!isinf(y_axis_len) && "Y axis inf");
    assert(!isinf(z_axis_len) && "Z axis inf");
    std::vector<std::shared_ptr<Object>> left;
    std::vector<std::shared_ptr<Object>> right;
    std::shared_ptr<Object> object;
    // TODO CLEAN UP
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
    else if (left.size() > 1)
      *this->left = AABBTree(left, a_depth + 1);

    if (right.size() == 1)
      this->right = right[0];
    else if (right.size() > 1)
      *this->right = AABBTree(right, a_depth + 1);
  }
}
