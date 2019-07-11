# I got some inspiration from
# https://stackoverflow.com/questions/17511496/create-a-shared-library-with-cmake

# Basic CMake version
cmake_minimum_required ( VERSION 3.2 )

# Get the project name from the current directory
get_filename_component ( projectname ${CMAKE_CURRENT_SOURCE_DIR} NAME )

# Name the project
project ( ${projectname}
          VERSION 0.0.1
          # DESCRIPTION "strompare is text comparison library"
		  LANGUAGES CXX )

# Locate Boost libraries: unit_test_framework
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.60 REQUIRED COMPONENTS unit_test_framework filesystem system)

# Enable C++11 features on gcc/clang
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
    #set(CMAKE_CXX_FLAGS "-std=c++11")
	add_compile_options(-std=c++11)
endif()

# Set warning level
if (MSVC)
  message("  Warning Level: MSVC")
  add_compile_options(/W4)
else()
  message("  Warning Level: GNU")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add sub-projects
add_subdirectory(stromparelib)
add_subdirectory(strompare_find_example)
add_subdirectory(stromparefiles)


#
# Dependencies
#

# Due to a cmake bug (no dependencies project/test) I define my own test target:
add_custom_target ( build-test COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${CMAKE_BINARY_DIR}/${projectname}_test )
#add_dependencies( test ${projectname}_test )
add_dependencies( ${projectname}_test ${projectname} )


# Doxygen Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/stromparelib/src/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY )
    add_custom_target ( doc
                        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
                        COMMENT "Generating API documentation with Doxygen" VERBATIM
                      )
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        add_custom_target ( docopen
                            ${CMAKE_CURRENT_SOURCE_DIR}/doc/html/index.html
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/html
                          )
    elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_custom_target ( docopen
                            xdg-open ${CMAKE_CURRENT_SOURCE_DIR}/doc/html/index.html
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc/html
                          )
    endif()

endif(DOXYGEN_FOUND)
