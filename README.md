# cmake debug project
CMake function file(GET_RUNTIME_DEPENDENCIES) seems to ignore libraries sometimes.

In this project, the CMake option USE_TEXT_CODECS determines if the executable 
will use the text codecs available in Qt::Core5Compat library. But this library is
unconditionally linked to the executable, so it is needed by the runtime linker and
the execution will fail if it is not available at runtime.

When this option USE_TEXT_CODECS is OFF the funtion file(GET_RUNTIME_DEPENDENCIES) omits 
the Qt::Core5Compat library.
