#include "settings_enums.h"

#include <assert.h>
#include <representations/GeometricObjectBase.h>

namespace hypro {

/// Recursive call of string to setting enum conversion
template <class Enum, class... Enums>
struct stringToSetting_Impl {
	static int toSetting( const std::string& name ) {
		auto result = Enum::_from_string_nothrow( name.c_str() );
		if ( result ) return result->_to_integral();
		return stringToSetting_Impl<Enums...>::toSetting( name );
	}
};

/// Base case of string to setting enum conversion
template <class Enum>
struct stringToSetting_Impl<Enum> {
	static int toSetting( const std::string& name ) {
		auto result = Enum::_from_string_nothrow( name.c_str() );
		if ( result ) return result->_to_integral();
		assert( false && "No enum was matched." );
		return -1;
	}
};

int stringToSetting( const std::string& name ) {
	return stringToSetting_Impl<
		  boxSetting_name,
		  supportFunctionSetting_name,
		  sfnSetting_name,
		  hPolytopeSetting_name,
		  carlPolytopeSetting_name,
		  tpolySetting_name,
		  StarsetSetting_name>::toSetting( name );
}

}  // namespace hypro