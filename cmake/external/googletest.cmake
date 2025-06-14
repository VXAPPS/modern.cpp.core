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

set(GOOGLETEST_SRC ${CMAKE_BINARY_DIR}/_deps/googletest-src)
set(GOOGLETEST_INSTALL ${CMAKE_BINARY_DIR}/_deps/googletest-install)
if(UNIX)
  set(GOOGLETEST_LIBRARY ${GOOGLETEST_INSTALL}/lib/libgtest.a)
  set(GOOGLETEST_OS_ARGS -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE})
else()
  set(GOOGLETEST_LIBRARY ${GOOGLETEST_INSTALL}/lib/gtest.lib)
  set(GOOGLETEST_OS_ARGS -Dgtest_force_shared_crt:BOOL=ON -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE})
endif()
set(GOOGLETEST_INCLUDE_DIR ${GOOGLETEST_INSTALL}/include)

ExternalProject_Add(GTest
  PREFIX ${GOOGLETEST_SRC}
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
  GIT_SHALLOW 1
  CMAKE_ARGS
    -DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
    -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_STANDARD:STRING=${CMAKE_CXX_STANDARD}
    -DCMAKE_CXX_FLAGS:STRING=${EXTRA_CXX_FLAGS}
    -DCMAKE_OSX_ARCHITECTURES:STRING=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_INSTALL_PREFIX:PATH=${GOOGLETEST_INSTALL}
    -Dgtest_build_tests:BOOL=OFF
    -Dgtest_build_samples:BOOL=OFF
    -DBUILD_GMOCK:BOOL=OFF
    ${GOOGLETEST_OS_ARGS}
  INSTALL_DIR ${GOOGLETEST_INSTALL}
  BUILD_BYPRODUCTS ${GOOGLETEST_LIBRARY}
  UPDATE_COMMAND ""
)

# We cannot use find_library because ExternalProject_Add() is performed at build time.
# And to please the property INTERFACE_INCLUDE_DIRECTORIES,
# we make the include directory in advance.
file(MAKE_DIRECTORY ${GOOGLETEST_INCLUDE_DIR})

add_library(GTest::gtest_main STATIC IMPORTED GLOBAL)
set_property(TARGET GTest::gtest_main PROPERTY IMPORTED_LOCATION ${GOOGLETEST_LIBRARY})
set_property(TARGET GTest::gtest_main PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${GOOGLETEST_INCLUDE_DIR})
add_dependencies(GTest::gtest_main GTest)
