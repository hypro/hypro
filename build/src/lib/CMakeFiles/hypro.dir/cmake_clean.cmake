file(REMOVE_RECURSE
  "../../lib/libhypro.pdb"
  "../../lib/libhypro.dylib"
)

# Per-language clean rules from dependency scanning.
foreach(lang)
  include(CMakeFiles/hypro.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
