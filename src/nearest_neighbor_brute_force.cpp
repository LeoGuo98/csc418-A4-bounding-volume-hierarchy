#include "nearest_neighbor_brute_force.h"
#include <iostream>
#include <limits>// std::numeric_limits<double>::infinity();

double squared_distance(const Eigen::RowVector3d &x1, const Eigen::RowVector3d &x2){
  // actually, 3D
  return (x1 - x2).squaredNorm();
}
void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  I = -1;
  sqrD = 0;

  double current_dist, min_dist = std::numeric_limits<double>::infinity();
  int points_size = points.size();
  Eigen::RowVector3d point;
  for (int i = 0; i < points_size; i += 3){
    for (int j = 0; j < 3; j++)
      point(j) = points(i, j);
    if((current_dist = squared_distance(point, query)) < min_dist){
      I = i;
      min_dist = current_dist;
    }
  }
}
