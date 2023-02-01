# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/notyhelper_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/notyhelper_autogen.dir/ParseCache.txt"
  "CMakeFiles/server_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/server_autogen.dir/ParseCache.txt"
  "notyhelper_autogen"
  "server_autogen"
  )
endif()
