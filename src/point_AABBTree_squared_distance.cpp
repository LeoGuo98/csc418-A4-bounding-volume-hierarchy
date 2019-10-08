#include "point_AABBTree_squared_distance.h"
#include "point_box_squared_distance.h"
#include "Object.h"
#include "CloudPoint.h"
#include <queue> // std::priority_queue
#include <limits.h>

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  std::priority_queue<std::pair<double, std::shared_ptr<Object>>> queue;
  double min_dist = std::numeric_limits<double>::infinity();
  double cur_dist = point_box_squared_distance(query, root->box);
  double sub_dist, left_dist, right_dist;
  std::shared_ptr<Object> cur_node;

  queue.push(std::make_pair(cur_dist, root));

  std::pair<double, std::shared_ptr<Object>> cur_pair;
  std::shared_ptr<CloudPoint> cloud_p;
  std::shared_ptr<AABBTree> tree_node;
  while(!queue.empty()){
    cur_pair = queue.top();
    sub_dist = cur_pair.first;
    cur_node = cur_pair.second;
    queue.pop();
    if (sub_dist < min_dist && sub_dist >= min_sqrd && sub_dist <= max_sqrd){
      cloud_p = std::dynamic_pointer_cast<CloudPoint>(cur_node);
      if(cloud_p){
          if(cloud_p->point_squared_distance(query, min_sqrd, max_sqrd, sub_dist, descendant)){
            if(sub_dist < min_dist){
              min_dist = sub_dist;
              descendant = cloud_p;
            }
          }
      }
      else{
        tree_node = std::dynamic_pointer_cast<AABBTree>(cur_node);

        left_dist = point_box_squared_distance(query, tree_node->left->box);
        right_dist = point_box_squared_distance(query, tree_node->right->box);

        queue.push(std::make_pair(left_dist, tree_node->left));
        queue.push(std::make_pair(right_dist, tree_node->right));
      }
    }
  }
  sqrd = min_dist;
  return (min_dist >= min_sqrd && min_dist <= max_sqrd);
}
