#pragma once
// enables default constructors
#define BETTER_ENUMS_DEFAULT_CONSTRUCTOR( Enum ) \
  public:                                        \
	Enum() = default;
#include "enum.h"