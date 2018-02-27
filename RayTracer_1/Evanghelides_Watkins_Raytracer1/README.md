For this assignment, we added in the intersect calculations for a sphere, triangle, plane and quad.
We also implemented the Phong shading for the scenes.

The sphere uses the quadratic equation determinant to see if an intersection has been made. If it 
has, the smallest positive root is used as the t value.

The triangle intersection is implemented using the Moller-Trumbore algorithm.

The plane uses the two vectors that define it to calculate the intersect.

The quad gets split into two triangles and an intersect is calculated for both. The one that is not NaN 
is used.

