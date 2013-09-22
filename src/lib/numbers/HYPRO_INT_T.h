/**
 * Abstract base class for all integer number types.
 * Author: Benedikt Seidl
 * Version: September 2013
 */

#pragma once

#include "number_t.h"
#include <string>

namespace hypro
{
	template<class T>
	class HYPRO_INT_T : public number_t<T>
	{
            private:
                /**
                 * Members
                 */
                T       mValue;
                
            public:
                /**
                 * Constructors & Destructors
                 */
                HYPRO_INT_T();
                HYPRO_INT_T(const int _value);
                HYPRO_INT_T(const std::string _string);
                HYPRO_INT_T(const unsigned _value);
                ~HYPRO_INT_T();
                
                /**
                 * Arithmetic operators
                 */
	};
}
