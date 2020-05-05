#include "util/type_handling/dispatch.h"
#include "util/type_handling/representation_enums.h"
#include "util/type_handling/settings_enums.h"

#include <iostream>
#include <string>

namespace hypro {

struct Functor {
  template <typename Representation> void operator()(representation_name name) {
    // Do something with the representation
    if (name == Representation::type()) {
      std::cout << "This worked. Representation is " << Representation::type()
                << std::endl;
    } else {
      std::cout << "Whoops?" << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  assert(argc == 3);
  std::string representationStr{argv[1]};
  std::string settingStr{argv[2]};

  representation_name representation =
      stringToRepresentation[representationStr];
  int setting = stringToSetting(representation, settingStr);

  dispatch(representation, setting, Functor{});

  return 0;
}

} // namespace hypro