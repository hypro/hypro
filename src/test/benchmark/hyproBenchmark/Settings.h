/**
 * @brief General benchmark settings.
 * 
 * @file Settings.h
 * @author Stefan Schupp
 * @date 2018-09-28
 */


namespace benchmark
{
    struct Settings
    {
        constexpr std::size_t maxDimension = 20;        // maximal dimension for benchmark objects
        constexpr std::size_t iterations = 1000;        // number of iterations per benchmark
    };
} // benchmark
