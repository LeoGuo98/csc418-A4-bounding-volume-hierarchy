#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

// double squared_distance(const int &x1, const int &x2){
//   // actually, 3D
//   return sqrt((pow(x1, 2) + pow(x2, 2)));
// }
void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  I = -1;
  sqrD = 0;

  // double min_dist = std::numeric_limits<double>::infinity();
  // int points_size = points.size();
  // for (int i = 0; i < points_size; i++){
  //   auto point = points[i];
  // }
}
