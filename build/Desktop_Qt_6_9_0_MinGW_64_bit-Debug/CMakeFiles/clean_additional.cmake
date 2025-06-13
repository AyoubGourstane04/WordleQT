# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\wordle_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\wordle_autogen.dir\\ParseCache.txt"
  "wordle_autogen"
  )
endif()
