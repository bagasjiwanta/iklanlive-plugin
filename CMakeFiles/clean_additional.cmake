# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/iklanlive-plugin_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/iklanlive-plugin_autogen.dir/ParseCache.txt"
  "iklanlive-plugin_autogen"
  )
endif()
