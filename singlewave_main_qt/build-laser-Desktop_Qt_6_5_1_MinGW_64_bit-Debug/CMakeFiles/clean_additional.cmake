# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\laser_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\laser_autogen.dir\\ParseCache.txt"
  "laser_autogen"
  )
endif()
