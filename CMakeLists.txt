# I got some inspiration from
# https://stackoverflow.com/questions/17511496/create-a-shared-library-with-cmake

# Basic CMake version
cmake_minimum_required ( VERSION 3.5 )

# Get the project name from the current directory
get_filename_component ( projectname ${CMAKE_CURRENT_SOURCE_DIR} NAME )

# Name the project
project ( ${projectname}
          VERSION 0.0.1
          DESCRIPTION "strompare is text comparison library"
		  LANGUAGES CXX )

# Locate Boost libraries: unit_test_framework, date_time and regex
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.59 REQUIRED COMPONENTS unit_test_framework date_time regex)

# Enable C++11 features on gcc/clang
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
    set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

# Add the source files. Avoid file(GLOB SRC_FILES ...)
configure_file(src/${projectname}version.h.in ${projectname}version.h @ONLY)
add_library ( ${projectname} SHARED
              include/strompare.h
              src/strompare.cpp
)

# Set VERSION property
set_target_properties ( ${projectname}
                        PROPERTIES VERSION ${PROJECT_VERSION}
					               SOVERSION 0
					               PUBLIC_HEADER include/strompare.h )

configure_file(src/${projectname}.pc.in ${projectname}.pc @ONLY)

# Add the source files. Avoid file(GLOB SRC_FILES ...)
add_executable ( ${projectname}_test
                 include/strompare.h
                 test/stromparetest.cpp
)

# Add INCLUDE folder
target_include_directories ( ${projectname} PRIVATE include )
target_include_directories ( ${projectname} PRIVATE src )
target_include_directories ( ${projectname} PRIVATE ${CMAKE_BINARY_DIR} )

target_include_directories ( ${projectname}_test PRIVATE include )
target_include_directories ( ${projectname}_test PRIVATE ${Boost_INCLUDE_DIRS} )

# Link library
target_link_libraries ( ${projectname}_test ${projectname} )
target_link_libraries ( ${projectname}_test ${Boost_LIBRARIES} )

# Define Installation
include(GNUInstallDirs)

if(WIN32)
    install ( TARGETS ${projectname}
              RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
              PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )
else()
    install ( TARGETS ${projectname}
              LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
              PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )
endif()

install(FILES ${CMAKE_BINARY_DIR}/${projectname}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# Define Tests
enable_testing()
add_test ( ${projectname}_test ${CMAKE_BINARY_DIR}/${projectname}_test )

# Run the tests on every build
add_custom_command(TARGET ${projectname}_test POST_BUILD COMMAND ${projectname}_test )

# Dependencies
# Due to a cmake bug (no dependencies project/test) I define my own test target:
add_custom_target ( build-test COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${CMAKE_BINARY_DIR}/${projectname}_test )
#add_dependencies( test ${projectname}_test )
add_dependencies( ${projectname}_test ${projectname} )

# Doxygen Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/src/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY )
    add_custom_target ( doc
                        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
                        COMMENT "Generating API documentation with Doxygen" VERBATIM
                      )
endif(DOXYGEN_FOUND)
