# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Media_Player_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Media_Player_autogen.dir\\ParseCache.txt"
  "Media_Player_autogen"
  )
endif()
