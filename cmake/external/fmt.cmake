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

set(FMT_SRC ${CMAKE_BINARY_DIR}/_deps/fmt-src)
set(FMT_INSTALL ${CMAKE_BINARY_DIR}/_deps/fmt-install)
if (UNIX)
  if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(FMT_LIBRARY ${FMT_INSTALL}/lib/libfmt.a)
  else()
    set(FMT_LIBRARY ${FMT_INSTALL}/lib/libfmtd.a)
  endif()
else()
  if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(FMT_LIBRARY ${FMT_INSTALL}/lib/fmt.lib)
  else()
    set(FMT_LIBRARY ${FMT_INSTALL}/lib/fmtd.lib)
  endif()
endif()
set(FMT_INCLUDE_DIR ${FMT_INSTALL}/include)

ExternalProject_Add(fmt
  PREFIX ${FMT_SRC}
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 9.1.0
  GIT_SHALLOW 1
  CMAKE_ARGS -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER} -DCMAKE_OSX_ARCHITECTURES:STRING=${CMAKE_OSX_ARCHITECTURES} -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX:PATH=${FMT_INSTALL} -DFMT_MASTER_PROJECT:BOOL=OFF -DFMT_INSTALL:BOOL=ON -DFMT_PEDANTIC:BOOL=ON -DFMT_WERROR:BOOL=ON
  INSTALL_DIR ${FMT_INSTALL}
  BUILD_BYPRODUCTS ${FMT_LIBRARY}
  UPDATE_COMMAND ""
)

set(FMT_ABSTRACT
"/*
* Copyright (c) 2022 Florian Becker <fb@vxapps.com> (VX APPS).
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its
*    contributors may be used to endorse or promote products derived from
*    this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* stl header */
#include <utility>

/* fmt header */
#ifdef __clang__
 #pragma clang diagnostic push
 #pragma clang diagnostic ignored \"-Weverything\"
#endif
#ifdef __GNUC__
 #pragma GCC diagnostic push
 #pragma GCC diagnostic ignored \"-Weffc++\"
#endif
#include <fmt/core.h>
#ifdef __GNUC__
 #pragma GCC diagnostic pop
#endif
#ifdef __clang__
 #pragma clang diagnostic pop
#endif

namespace std {

 template <typename... T>
 std::string format( fmt::format_string<T...> fmt, T &&...args ) {

   return fmt::format( fmt, std::forward<T>( args )... )\;
 }
}
"
)

write_file(${FMT_INCLUDE_DIR}/format ${FMT_ABSTRACT})
