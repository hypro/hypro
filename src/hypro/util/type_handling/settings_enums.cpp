#include "settings_enums.h"

namespace hypro {

int stringToSetting( representation_name Rep, const std::string& name ) {
	switch ( Rep ) {
		case representation_name::box:
			return static_cast<int>( stringToBoxSetting.at( name ) );
	}
}
}