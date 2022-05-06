# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/bayus/Documents/iklanlive-plugin/_deps/zlib-src"
  "/home/bayus/Documents/iklanlive-plugin/_deps/zlib-build"
  "/home/bayus/Documents/iklanlive-plugin/_deps/zlib-subbuild/zlib-populate-prefix"
  "/home/bayus/Documents/iklanlive-plugin/_deps/zlib-subbuild/zlib-populate-prefix/tmp"
  "/home/bayus/Documents/iklanlive-plugin/_deps/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp"
  "/home/bayus/Documents/iklanlive-plugin/_deps/zlib-subbuild/zlib-populate-prefix/src"
  "/home/bayus/Documents/iklanlive-plugin/_deps/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/bayus/Documents/iklanlive-plugin/_deps/zlib-subbuild/zlib-populate-prefix/src/zlib-populate-stamp/${subDir}")
endforeach()
