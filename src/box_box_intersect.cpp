#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  // easy for axis-aligned boxes...
  // if (A.min_corner.x() <= B.max_corner.x() || A.max_corner.x() >= B.min_corner.x()){
  //   if (A.min_corner.y() <= B.max_corner.y() || A.max_corner.y() >= B.min_corner.y()){
  //     if (A.min_corner.z() <= B.max_corner.z() || A.max_corner.z() >= B.min_corner.z()){
  //       return false;
  //     }
  //   }
  // }
  // return true;
  bool ret;
  for (int i = 0; i < 3; i++){
    if(A.min_corner(i) <= B.min_corner(i) && B.min_corner(i) <= A.max_corner(i))
      ret = true;
    else if (A.min_corner(i) <= B.max_corner(i) && B.max_corner(i) <= A.max_corner(i))
      ret = true;
    else if (B.min_corner(i) <= A.min_corner(i) && A.min_corner(i) <= B.max_corner(i))
      ret = true;
    else if (B.min_corner(i) <= A.max_corner(i) && A.max_corner(i) <= B.max_corner(i))
      ret = true;
    else
      return false;
  }
  return ret;
}

