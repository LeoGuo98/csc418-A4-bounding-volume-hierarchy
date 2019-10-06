#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  B.min_corner(0) = B.min_corner(0) < A.min_corner(0)? \
                    B.min_corner(0): A.min_corner(0);
  B.min_corner(1) = B.min_corner(1) < A.min_corner(1)? \
                    B.min_corner(1): A.min_corner(1);
  B.min_corner(2) = B.min_corner(2) < A.min_corner(2)? \
                    B.min_corner(2): A.min_corner(2);
  B.min_corner(0) = B.min_corner(0) > A.min_corner(0)? \
                    B.min_corner(0): A.min_corner(0);
  B.min_corner(1) = B.min_corner(1) > A.min_corner(1)? \
                    B.min_corner(1): A.min_corner(1);
  B.min_corner(2) = B.min_corner(2) > A.min_corner(2)? \
                    B.min_corner(2): A.min_corner(2);
}
