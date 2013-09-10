/**
 * Abstract base class for all integer number types.
 * Autho: Benedikt Seidl
 * Version: September 2013
 */

#ifndef HYPRO_INT_T_H_
#define HYPRO_INT_T_H_

#include "number_t.h"

namespace hypro
{
	template<class T>
	class HYPRO_INT_T : public number_t<T>
	{
	};
}

#endif /*HYPRO_INT_T_H_*/
