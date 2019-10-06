#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  auto min_vertex_x = a(0) < b(0) && a(0) < c(0)? a(0): \
                      b(0) < c(0)? b(0): c(0);
  auto min_vertex_y = a(1) < b(1) && a(1) < c(1)? a(1): \
                      b(1) < c(1)? b(1): c(1);
  auto min_vertex_z = a(2) < b(2) && a(2) < c(2)? a(2): \
                      b(2) < c(2)? b(2): c(2);
  auto max_vertex_x = a(0) > b(0) && a(0) > c(0)? a(0): \
                      b(0) > c(0)? b(0): c(0);
  auto max_vertex_y = a(1) > b(1) && a(1) > c(1)? a(1): \
                      b(1) > c(1)? b(1): c(1);
  auto max_vertex_z = a(2) > b(2) && a(2) > c(2)? a(2): \
                      b(2) > c(2)? b(2): c(2);

  B.min_corner(0) = B.min_corner(0) < min_vertex_x? B.min_corner(0): \
                    min_vertex_x;
  B.min_corner(1) = B.min_corner(0) < min_vertex_y? B.min_corner(1): \
                    min_vertex_y;
  B.min_corner(2) = B.min_corner(0) < min_vertex_z? B.min_corner(2): \
                    min_vertex_z;
  B.max_corner(0) = B.max_corner(0) < min_vertex_x? B.min_corner(0): \
                    min_vertex_x;
  B.max_corner(1) = B.max_corner(1) < min_vertex_y? B.min_corner(1): \
                    min_vertex_y;
  B.max_corner(2) = B.max_corner(2) < min_vertex_z? B.min_corner(2): \
                    min_vertex_z;
}


