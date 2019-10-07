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

    auto x_axis_len = abs(this->box.max_corner.x() - \
                          this->box.min_corner.x());
    auto x_axis_midpoint = (this->box.max_corner.x() + \
                            this->box.min_corner.x()) / 2.0;

    auto y_axis_len = abs(this->box.max_corner.y() - \
                          this->box.min_corner.y());
    auto y_axis_midpoint = (this->box.max_corner.y() + \
                            this->box.min_corner.y()) / 2.0;

    auto z_axis_len = abs(this->box.max_corner.z() - \
                          this->box.min_corner.z());
    auto z_axis_midpoint = (this->box.max_corner.z() + \
                            this->box.min_corner.z()) / 2.0;

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
        if (object->box.center().x() < x_axis_midpoint)
          left.push_back(object);
        else
          right.push_back(object);
      }
      else if (y_axis_len > z_axis_len){
        if (object->box.center().y() < y_axis_midpoint)
          left.push_back(object);
        else
          right.push_back(object);
      }
      else{
        if (object->box.center().z() < z_axis_midpoint)
          left.push_back(object);
        else
          right.push_back(object);
      }
    }

    if (left.size() == objects.size()){
      std::vector<std::shared_ptr<Object>> new_left;
      std::vector<std::shared_ptr<Object>> new_right;
      for(int i = 0; i < left.size() / 2; i++)
        new_left.push_back(left[i]);
      for(int i = left.size() / 2; i < left.size(); i++)
        new_right.push_back(left[i]);
    }
    else if (right.size() == objects.size()){
      std::vector<std::shared_ptr<Object>> new_left;
      std::vector<std::shared_ptr<Object>> new_right;
      for(int i = 0; i < right.size() / 2; i++)
        new_left.push_back(right[i]);
      for(int i = right.size() / 2; i < right.size(); i++)
        new_right.push_back(right[i]);
    }
    else{
      if (left.size() == 1)
        this->left = left[0];
      if (left.size() > 1)
        this->left = std::make_shared<AABBTree>(left, a_depth + 1);

      if (right.size() == 1)
        this->right = right[0];
      if (right.size() > 1)
        this->right = std::make_shared<AABBTree>(right, a_depth + 1);
    }
  }
}
