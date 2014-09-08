

set(command "/usr/local/Cellar/cmake/3.0.1/bin/cmake;-Dgtest_force_shared_crt=ON;-DCXX=/usr/bin/clang++;-DCMAKE_CXX_FLAGS=-stdlib=libc++;-DCMAKE_CXX_FLAGS=-std=c++11;-DCMAKE_CXX_FLAGS=-DGTEST_USE_OWN_TR1_TUPLE=1;-GUnix Makefiles;/Users/jongan/Dropbox/HiWi job stuffs/hypro/src/resources/gtest-1.6.0")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/src/resources/src/googletest-stamp/googletest-configure-out.log"
  ERROR_FILE "/Users/jongan/Dropbox/HiWi job stuffs/hypro/build/src/resources/src/googletest-stamp/googletest-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /Users/jongan/Dropbox/HiWi job stuffs/hypro/build/src/resources/src/googletest-stamp/googletest-configure-*.log\n")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "googletest configure command succeeded.  See also /Users/jongan/Dropbox/HiWi job stuffs/hypro/build/src/resources/src/googletest-stamp/googletest-configure-*.log\n")
  message(STATUS "${msg}")
endif()
