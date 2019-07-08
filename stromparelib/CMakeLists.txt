# Get the name from the current directory
get_filename_component(subprojectname ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Name the project
project ( ${projectname}
          VERSION 0.0.1
          # DESCRIPTION "strompare is text comparison library"
		  LANGUAGES CXX )
		  
#
# Library
#
		  
# Add the source files. Avoid file(GLOB SRC_FILES ...)
configure_file(src/${projectname}version.h.in ${projectname}version.h @ONLY)
add_library ( ${projectname} SHARED
              ../include/strompare.h
              ../include/strompare/ngram.h
              ../include/strompare/ngramsearch.h
              ../include/strompare/levenshtein.h
              src/strompare.cpp
              src/levenshtein.cpp
              src/ngram.cpp
              src/ngramsearch.cpp
)

# Add INCLUDE folder
target_include_directories ( ${projectname} PRIVATE ../include )
target_include_directories ( ${projectname} PRIVATE include )
target_include_directories ( ${projectname} PRIVATE src )
target_include_directories ( ${projectname} PRIVATE ${CMAKE_BINARY_DIR} )

# Link library
target_link_libraries ( ${projectname} ${CMAKE_EXE_LINKER_FLAGS} )

# Set VERSION property
set_target_properties ( ${projectname}
                        PROPERTIES VERSION ${PROJECT_VERSION}
					               SOVERSION 0
					               PUBLIC_HEADER ../include/strompare.h )

configure_file(src/${projectname}.pc.in ${projectname}.pc @ONLY)

#
# Test
#

# Add the source files. Avoid file(GLOB SRC_FILES ...)
add_executable ( ${projectname}_test
                 ../include/strompare.h
                 ../include/strompare/ngram.h
                 ../include/strompare/ngramsearch.h
                 ../include/strompare/levenshtein.h
                 test/levenshteintest.cpp
                 test/dameraulevenshteintest.cpp
                 test/versiontest.cpp
                 test/ngramtest.cpp
                 test/ngramsearchtest.cpp
				 test/testcountries.h
				 test/testnouns.h
)

# Add INCLUDE folder
target_include_directories ( ${projectname}_test PRIVATE ../include )
target_include_directories ( ${projectname}_test PRIVATE include )
target_include_directories ( ${projectname}_test PRIVATE ${Boost_INCLUDE_DIRS} )

# Link library
target_link_libraries ( ${projectname}_test ${projectname} ${Boost_LIBRARIES} ${CMAKE_EXE_LINKER_FLAGS} )

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
