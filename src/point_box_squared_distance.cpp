#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  auto center = 0.5 * (box.min_corner + box.max_corner);
  return (center - query).squaredNorm();
}
