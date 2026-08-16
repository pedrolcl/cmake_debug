cmake_minimum_required(VERSION 3.19)

project(cmake_debug
  VERSION 1.0.0
  LANGUAGES CXX
)

option(USE_TEXT_CODECS "Use Qt::Core5Compat text codecs" OFF)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Core5Compat)

message(STATUS "Using text codecs: ${USE_TEXT_CODECS}")
message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "CMake prefix: ${CMAKE_PREFIX_PATH}")
message(STATUS "Qt version: ${Qt6_VERSION}")
message(STATUS "Qt directory: ${Qt6_DIR}")
message(STATUS "Qt qmake: ${QT_QMAKE_EXECUTABLE}")

execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} "-query" "QT_INSTALL_PREFIX"
  OUTPUT_VARIABLE QT_PREFIX
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Qt prefix: ${QT_PREFIX}")

execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} "-query" "QT_INSTALL_LIBS"
  OUTPUT_VARIABLE QT_LIBS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Qt libs: ${QT_LIBS}")

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    main.cpp
)

if (USE_TEXT_CODECS)
target_compile_definitions(${PROJECT_NAME} PRIVATE USE_TEXT_CODECS)
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Core5Compat
)

if (DEFINED ENV{GITHUB_OUTPUT})
    file(APPEND
        "$ENV{GITHUB_OUTPUT}"
        "config_version=${PROJECT_VERSION}\n"
    )
endif()

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(CODE "
  file(GET_RUNTIME_DEPENDENCIES
    EXECUTABLES $<TARGET_FILE:${PROJECT_NAME}>
    DIRECTORIES ${QT_PREFIX} ${QT_LIBS}
    RESOLVED_DEPENDENCIES_VAR _r_deps
    UNRESOLVED_DEPENDENCIES_VAR _u_deps
    CONFLICTING_DEPENDENCIES_PREFIX _conflicts
  )
  foreach(_file \${_r_deps})
    message(STATUS \"Dependency: \${_file}\")
  endforeach()
  foreach(_file \${_conflicts_FILENAMES})
    message(STATUS \"Conflict: \${_file}\")
    message(STATUS \"  \${_file} paths: \${_conflicts_\${_file}}\")
  endforeach()
  foreach(_file \${_u_deps})
    message(STATUS \"Unresolved: \${_file}\")
  endforeach()
")
