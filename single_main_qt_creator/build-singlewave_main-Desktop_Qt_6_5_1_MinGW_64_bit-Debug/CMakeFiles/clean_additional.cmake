# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\singlewave_main_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\singlewave_main_autogen.dir\\ParseCache.txt"
  "singlewave_main_autogen"
  )
endif()
