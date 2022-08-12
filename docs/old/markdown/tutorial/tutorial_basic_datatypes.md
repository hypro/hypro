# Basic Datatypes {#tutorial_basic_datatypes}

Most data structures in HyPro are built from few basic datatypes apart from the commonly known types provided by the
standard library.

## Vectors and matrices

HyPro uses data structures provided by [Eigen3](https://eigen.tuxfamily.org/) internally to represent _vectors_ and _
matrices_.
We use `typedefs` for arbitrary-sized vectors and matrices which are referred to by `vector_t<N>` and `matrix_t<N>`
respectively (where `N` is a template-parameter for the underlying number representation).
Vectors are per default _row vectors_, i.e., a _d_-dimensional vector is a dx1-matrix.
Here we shortly present their construction and refer to
the [Eigen3 documentation](https://eigen.tuxfamily.org/index.php?title=Main_Page#Documentation) for further details.

```c++
using Number = double;

// create an uninitialized 3-dimensional vector
hypro::vector_t<Number> my_vec_1 = hypro::vector_t<Number>(3);
// create a 3-dimensional vector filled with zeros
hypro::vector_t<Number> my_vec_2 = hypro::vector_t<Number>::Zero(3);
// create a 3-dimensional vector filled with ones
hypro::vector_t<Number> my_vec_3 = hypro::vector_t<Number>::Ones(3);

// initialization to set my_vec_1 to (1,2,3)^T, indices are 0-indexed
my_vec_1(0) = 1;
my_vec_1(1) = 2;
my_vec_1(2) = 3;

// for convenience, Eigen3 overloads streaming operators for initialization
my_vec_1 << 1,2,3;
```

Similarly, matrices can be constructed:

```c++
using Number = double;

// create an uninitialized 3x4-matrix
hypro::matrix_t<Number> my_mat_1 = hypro::matrix_t<Number>(3,4);
// create a 3x4-matrix filled with zeros
hypro::matrix_t<Number> my_mat_2 = hypro::matrix_t<Number>::Zero(3,4);
// create a 3x4-matrix filled with ones
hypro::matrix_t<Number> my_mat_3 = hypro::matrix_t<Number>::Ones(3,4);
// create a 3x3 identity-matrix
hypro::matrix_t<Number> my_id_mat = hypro::matrix_t<Number>::Identity(3);

// coefficient-wise initialization
my_mat_2(0,0) = 1;
my_mat_2(1,2) = 2;
my_mat_2(2,0) = 3;
my_mat_2(3,1) = 4;
/* my_mat_2 now should be
1 0 0 0
0 0 2 0
3 0 0 0
0 4 0 0
*/

// for convenience, Eigen3 overloads streaming operators for initialization
my_mat_2 << 1,0,0,0,
            0,0,2,0,
            3,0,0,0,
            0,4,0,0;
```

## Intervals {#tutorial_intervals}

Intervals are commonly used in HyPro for various applications.
Internally we rely on the implementation shipped with [CArL](https://github.com/smtrat/carl).

```c++
using Number = double;

// construction of a weak-bounded interval [1,2]
carl::Interval<Number> my_intv_1{1,2};
// explicit construction of the same interval with bound types
carl::Interval<Number> my_intv_2 = carl::Interval<Number>(1, carl::BoundType::WEAK, 2, carl::BoundType::WEAK);
```