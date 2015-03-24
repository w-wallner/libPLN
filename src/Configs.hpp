
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
    NO_FILTER,
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

typedef struct
{
    double  T_val;
}
TimeConfig;

typedef struct
{
    size_t  ForgetTh;
}
PerformanceConfig;

typedef struct
{
    SampleConfig            SampleConf;
    KW_FilterConfig         KwConf;
    KW_ImplOption           KwImplOption;
    HP_FilterConfig         HpConf;
    InterpolationConfig     InterpolConf;
    TimeConfig              TimeConf;
    PerformanceConfig       PerformanceConf;
}
TdEstimatorConfig;

// =========================================================================
// Function declarations
// =========================================================================


#endif
