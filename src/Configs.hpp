
#ifndef CONFIGS_HPP_
#define CONFIGS_HPP_

// =========================================================================
// Includes
// =========================================================================

#include <cstddef>

// =========================================================================
// Defines
// =========================================================================

// =========================================================================
// Type definitions
// =========================================================================

typedef struct
{
    double  f_s;
    double  T_val;
    size_t  TdVecLen;
}
SampleConfig;

typedef enum
{
    USE_SHORTCUTS,
    FORCE_GENERIC
}
KW_ImplOption;

typedef struct
{
    unsigned int    Seed;
    double          Qd;
    double          alpha;
    size_t          FilterLen;
}
KW_FilterConfig;

typedef enum
{
    BLACKMAN,
    NONE
}
HP_FilterType;

typedef struct
{
    HP_FilterType   Type;
    double          f_c_nom;
    size_t          FilterLen;
    size_t          Cnt;
}
HP_FilterConfig;

typedef enum
{
    LINEAR_INTERPOLATION,
    CUBIC_SPLINE_INTERPOLATION
}
InterpolationType;

typedef struct
{
    InterpolationType   Type;
}
InterpolationConfig;

// =========================================================================
// Function declarations
// =========================================================================


#endif
