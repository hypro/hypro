/**
 * Abstract base class for all floating number types.
 * Autho: Benedikt Seidl
 * Version: September 2013
 */

#ifndef HYPRO_FLOAT_T_H_
#define HYPRO_FLOAT_T_H_

#include "number_t.h"

namespace hypro
{
	template<class T>
	class HYPRO_FLOAT_T : public number_t<T>
	{
	};
}

#endif /*HYPRO_FLOAT_T_H_*/
