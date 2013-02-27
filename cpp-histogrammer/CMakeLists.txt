cmake_minimum_required (VERSION 2.6)
set (PROJECT histogrammer)

set (HEADERS  xydata_template.h qpoint.h qglobal_part.h makehist.h)
set (SOURCES qpoint.cpp makehist.cpp main.cpp)
 
project (${PROJECT})
find_library(LIBRARIES NAMES m PATH_SUFFIXES dynamic)
include_directories ( ${PROJECT_SOURCE_DIR})
 
if (MSVC)
  add_definitions (/W3)
elseif (CMAKE_COMPILER_IS_GNUCXX)
  add_definitions (-Wall -pedantic)
else ()
  message ("Unknown compiler")
endif ()
 
source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_executable (${PROJECT} ${HEADERS} ${SOURCES})

#linking
target_link_libraries (${PROJECT} ${LIBRARIES} )
