#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
#include "MeshTriangle.h"
#include "AABBTree.h"
// Hint: use a list as a queue
#include <list>
#include <iostream>

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > &
    leaf_pairs)
{
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> queue;
  std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> node_pair;
  std::shared_ptr<Object> node_a, node_b;
  std::shared_ptr<MeshTriangle> mesh_t_a, mesh_t_b;
  std::shared_ptr<AABBTree> tree_a, tree_b;
  if (box_box_intersect(rootA->box, rootB->box))
    queue.push_back(std::make_pair(rootA, rootB));
  while (!queue.empty()){
    node_pair = queue.front();
    node_a = node_pair.first;
    node_b = node_pair.second;
    queue.pop_front();

    mesh_t_a = std::dynamic_pointer_cast<MeshTriangle>(node_a);
    mesh_t_b = std::dynamic_pointer_cast<MeshTriangle>(node_b);

    if (mesh_t_a && mesh_t_b)
      leaf_pairs.push_back(std::make_pair(mesh_t_a, mesh_t_b));
    else if (mesh_t_a){
    node_pair = queue.front();
      tree_b = std::dynamic_pointer_cast<AABBTree>(node_b);
      if (box_box_intersect(node_a->box, tree_b->left->box))
        queue.push_back(std::make_pair(node_a, tree_b->left));
      if (box_box_intersect(node_a->box, tree_b->right->box))
        queue.push_back(std::make_pair(node_a, tree_b->right));
    }
    else if (mesh_t_b){
      tree_a = std::dynamic_pointer_cast<AABBTree>(node_a);
      if (box_box_intersect(node_b->box, tree_a->left->box))
        queue.push_back(std::make_pair(tree_a->left, node_b));
      if (box_box_intersect(node_b->box, tree_a->right->box))
        queue.push_back(std::make_pair(tree_a->right, node_b));
    }
    else{
      tree_a = std::dynamic_pointer_cast<AABBTree>(node_a);
      tree_b = std::dynamic_pointer_cast<AABBTree>(node_b);
      if (box_box_intersect(tree_a->left->box, tree_b->left->box))
        queue.push_back(std::make_pair(tree_a->left, tree_b->left));
      if (box_box_intersect(tree_a->left->box, tree_b->right->box))
        queue.push_back(std::make_pair(tree_a->left, tree_b->right));
      if (box_box_intersect(tree_a->right->box, tree_b->left->box))
        queue.push_back(std::make_pair(tree_a->right, tree_b->left));
      if (box_box_intersect(tree_a->right->box, tree_b->right->box))
        queue.push_back(std::make_pair(tree_a->right, tree_b->right));
    }
  }
}
