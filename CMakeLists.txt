cmake_minimum_required(VERSION 3.19)

project(cmake_bug
  VERSION 1.0.0
  LANGUAGES CXX
)

message(STATUS "CMake version: ${CMAKE_VERSION}")

find_package(Qt6 6.11 REQUIRED COMPONENTS Core Core5Compat)

qt_standard_project_setup()

qt_add_executable(cmake_bug
    main.cpp
)

target_link_libraries(cmake_bug
    PRIVATE
        Qt::Core
        Qt::Core5Compat
)

install(TARGETS cmake_bug
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(CODE [[
  file(GET_RUNTIME_DEPENDENCIES
    EXECUTABLES $<TARGET_FILE:cmake_bug>
    RESOLVED_DEPENDENCIES_VAR _r_deps
    UNRESOLVED_DEPENDENCIES_VAR _u_deps
    CONFLICTING_DEPENDENCIES_PREFIX _conflicts
  )
  foreach(_file ${_r_deps})
    message(STATUS "Dependency: ${_file}")
  endforeach()
  foreach(_file ${_conflicts_FILENAMES})
    message(STATUS "Conflict: ${_file}")
    message(STATUS "  ${_file} paths: ${_conflicts_${_file}}")
  endforeach()
  foreach(_file ${_u_deps})
    message(STATUS "Unresolved: ${_file}")
  endforeach()
]])
