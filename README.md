This is a matrix library for c++.

Example usage:

```c++
// Creates a matrix
Matrix m = Matrix::create({
  {0, 1},
  {2, 3},
  {4, 5}
});

m.log();
// Outputs:
// [0  1]
// [2  3]
// [4  5]

// Create a matrix with 2 rows and 3 columns, filled with zeros.
Matrix b = Matrix::zerofill(2, 3);

// Get the dot product of m and b
Matrix c = m * b;

c.log();
// Outputs:
// [0  0  0]
// [0  0  0]
```
