# Installation {#installation}

After having installed all necessary [dependencies](@ref dependencies), the library can be compiled out of source and installed using _cmake_. In the following we assume a build folder named 'build' will be used. The following terminal commands will allow for a build with the default settings enabled:

~~~.bash
cmake ..
make resources
make
~~~

To install the library to your system, use

~~~.bash
make install
~~~

Examples
--------

Each provided example file comes with its own target, which can be build by using the examples name, i.e. use

~~~.bash
make example_zonotope
~~~

to build an example showing the basic usage of the zonotope representation. Each built example binary can be found in the folder build/bin/.
