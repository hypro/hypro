#pragma once

#include "../../representations/GeometricObjectBase.h"
#include "better_enums/enum.h"

#include <string>

namespace hypro {

/**
 * @brief Converts a settings string to an enum-type.
 *
 * @param name
 * @return int
 */
int stringToSetting( const std::string& name );

}  // namespace hypro