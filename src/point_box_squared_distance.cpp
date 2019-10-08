#include "point_box_squared_distance.h"

// TODO Optimize - clean up
double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  Eigen::RowVector3d closest_point;
  double query_axis, max_axis, min_axis;
  // Find closest point ON the box
  for (int i = 0; i < 3; i++){
    query_axis = query(i);
    max_axis = box.max_corner(i);
    min_axis = box.min_corner(i);
    if (query_axis > max_axis)
      closest_point(i) = max_axis;
    else if (query_axis < min_axis)
      closest_point(i) = min_axis;
    // in the middle - set to closest edge
    else{
      if (abs(query_axis - max_axis) <
          abs(query_axis - min_axis))
        closest_point(i) = max_axis;
      else
        closest_point(i) = min_axis;
    }
  }
  return (closest_point - query).squaredNorm();
}
