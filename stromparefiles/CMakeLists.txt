# Get the name from the current directory
get_filename_component(subprojectname ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Name the project
project ( ${subprojectname}
          VERSION 0.0.1
          # DESCRIPTION "strompare is text comparison library"
		  LANGUAGES CXX )

# Add the source files. Avoid file(GLOB SRC_FILES ...)
add_executable ( ${subprojectname}
                 ../include/strompare.h
                 ../include/strompare/ngram.h
                 ../include/strompare/ngramsearch.h
                 ../include/strompare/levenshtein.h
                 src/${subprojectname}.cpp
)

# Add INCLUDE folder
target_include_directories ( ${subprojectname} PRIVATE ${Boost_INCLUDE_DIRS} )
target_include_directories ( ${subprojectname} PRIVATE ../include )
target_include_directories ( ${subprojectname} PRIVATE include )

# Link library
target_link_libraries ( ${subprojectname} ${projectname} ${Boost_LIBRARIES} ${CMAKE_EXE_LINKER_FLAGS} )