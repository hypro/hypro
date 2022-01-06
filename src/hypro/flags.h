#pragma once

// clang-format off
#define SOLVER_GLPK 1
#define SOLVER_CLP 2
#define SOLVER_SMTRAT 3
#define SOLVER_ZTHREE 4
#define SOLVER_SOPLEX 5

/* #undef SUPPORT_MPFR */
/* #undef COMPARE_CDD */
/* #undef COMPARE_POLYMAKE */
/* #undef HYPRO_USE_CLP */
#define HYPRO_USE_GLPK
/* #undef HYPRO_GSL_INTEGRATION */
/* #undef HYPRO_USE_PPL */
/* #undef HYPRO_USE_OPENMP */
/* #undef HYPRO_USE_SMTRAT */
/* #undef HYPRO_USE_SOPLEX */
/* #undef HYPRO_USE_Z3 */
#define HYPRO_PRIMARY_SOLVER SOLVER_GLPK
/* #undef HYPRO_SECONDARY_SOLVER */
/* #undef USE_CLANG */
/* #undef EXTERNALIZE_CLASSES */
/* #undef HYPRO_LOGGING */
#define HYPRO_STATISTICS
/* #undef FORWARD_REACHABILITY_METHOD_2 */
#define QUICKHULL_USE_LOW_DIMENSIONAL_IMPROVEMENT
#define RESET_REFINEMENT
/* #undef CARL_OLD_INTERVALS */
/* #undef CARL_OLD_STRUCTURE */
/* #undef CARL_POLY_MEMBER_SUBSTITUTE */
/* #undef CARL_VARIABLE_VARIANTS */
#define CARL_LOGGING_POST_1910

#ifdef HYPRO_USE_SOPLEX
#define SOPLEX_WITH_GMP
#endif

// clang-format on
