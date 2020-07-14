#include "representations/GeometricObjectBase.h"
#include "util/type_handling/dispatch.h"
#include "util/type_handling/representation_enums.h"
#include "util/type_handling/settings_enums.h"

#include <iostream>
#include <string>

using namespace hypro;

namespace hypro {
namespace examples {
struct Functor {
	template <typename Representation>
	void operator()( representation_name name ) {
		// Do something with the representation
		if ( name == Representation::type() ) {
			std::cout << "This worked. Representation is " << Representation::type()
					  << std::endl;
		} else {
			std::cout << "Whoops?" << std::endl;
		}
	}
};
}  // namespace examples
}  // namespace hypro

int main( int argc, char **argv ) {
	assert( argc == 3 );
	std::string representationStr{ argv[1] };
	std::string settingStr{ argv[2] };

	representation_name representation = representation_name::_from_string( representationStr.c_str() );
	int setting = stringToSetting( settingStr );

	dispatch<double, Converter<double>>( representation, setting, hypro::examples::Functor{},
										 representation );

	return 0;
}