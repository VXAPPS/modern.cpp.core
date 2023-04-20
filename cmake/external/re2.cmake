#
# Copyright (c) 2022 Florian Becker <fb@vxapps.com> (VX APPS).
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

include(ExternalProject)

set(RE2_SRC ${CMAKE_BINARY_DIR}/_deps/re2-src)
set(RE2_INSTALL ${CMAKE_BINARY_DIR}/_deps/re2-install)
if(UNIX)
  set(RE2_LIBRARY ${RE2_INSTALL}/lib/libre2.a)
else()
  set(RE2_LIBRARY ${RE2_INSTALL}/lib/re2.lib)
endif()
set(RE2_OS_ARGS -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE})
set(RE2_INCLUDE_DIR ${RE2_INSTALL}/include)
if (WIN32)
  set(EXTRA_CXX_FLAGS "${EXTRA_CXX_FLAGS} /EHsc")
endif()

ExternalProject_Add(re2
  PREFIX ${RE2_SRC}
  GIT_REPOSITORY https://github.com/google/re2.git
  GIT_TAG 2023-03-01
  GIT_SHALLOW 1
  CMAKE_ARGS
    -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_STANDARD:STRING=${CMAKE_CXX_STANDARD}
    -DCMAKE_CXX_FLAGS:STRING=${EXTRA_CXX_FLAGS}
    -DCMAKE_OSX_ARCHITECTURES:STRING=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_INSTALL_PREFIX:PATH=${RE2_INSTALL}
    -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
    -DRE2_BUILD_TESTING:BOOL=OFF
    ${RE2_OS_ARGS}
  INSTALL_DIR ${RE2_INSTALL}
  BUILD_BYPRODUCTS ${RE2_LIBRARY}
  UPDATE_COMMAND ""
)

# We cannot use find_library because ExternalProject_Add() is performed at build time.
# And to please the property INTERFACE_INCLUDE_DIRECTORIES,
# we make the include directory in advance.
file(MAKE_DIRECTORY ${RE2_INCLUDE_DIR})

add_library(re2::re2 STATIC IMPORTED GLOBAL)
set_property(TARGET re2::re2 PROPERTY IMPORTED_LOCATION ${RE2_LIBRARY})
set_property(TARGET re2::re2 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${RE2_INCLUDE_DIR})
add_dependencies(re2::re2 re2)
