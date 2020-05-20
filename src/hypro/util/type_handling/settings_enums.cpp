#include "settings_enums.h"

#include <assert.h>

namespace hypro {

template <class Enum, class... Enums>
struct stringToSetting_Impl {
	static int toSetting( const std::string& name ) {
		auto result = Enum::_from_string_nothrow( name.c_str() );
		if ( result ) return result->_to_integral();
		return stringToSetting_Impl<Enums...>::toSetting( name );
	}
};

template <class Enum>
struct stringToSetting_Impl<Enum> {
	static int toSetting( const std::string& name ) {
		auto result = Enum::_from_string_nothrow( name.c_str() );
		if ( result ) return result->_to_integral();
		assert( false && "No enum was matched." );
	}
};

int stringToSetting( const std::string& name ) {
	return stringToSetting_Impl<
		boxSetting_name, 
		supportFunctionSetting_name, 
		sfnSetting_name,
		tpolySetting_name >::toSetting( name );
}

}  // namespace hypro