#pragma once

namespace hypro {

struct VPolytopeSettings{
    static constexpr bool checkVerticesBeforeConversion = true;
    static constexpr bool useLpForPointContainment = true;
};

} // hypro
