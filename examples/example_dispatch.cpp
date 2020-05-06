#include "representations/GeometricObjectBase.h"
#include "util/type_handling/dispatch.h"
#include "util/type_handling/representation_enums.h"
#include "util/type_handling/settings_enums.h"

#include <iostream>
#include <string>

using namespace hypro;

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

int main( int argc, char **argv ) {
	assert( argc == 3 );
	std::string representationStr{argv[1]};
	std::string settingStr{argv[2]};

	representation_name representation = stringToRepresentation.at( representationStr );
	int setting = stringToSetting( representation, settingStr );

	dispatch<double, Converter<double>>( representation, setting, Functor{},
										 representation );

	return 0;
}