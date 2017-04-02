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

// Create a matrix with 5 rows and 5 columns, filled with random values.
Matrix d = Matrix::random(5, 5);

// Add 3 to each value in the matrix.
Matrix e = d + 3;
```

## Matrix Functions
View matrix.h for more details
```c++
// Add two matrices
.add()
// Get the dot product of two matrices
.dot()
// Multiply each element in A with the corresponding element in B
.multiply()
// Scalar operations
.add_scalar()
.multiply_scalar()
.divide_scalar()

// Transpose and rotate
.transpose()
.rotate_left()
.rotate_right()

// Other
.flip_columns()
.flip_rows()
.sum()
.max()
.min()
```
