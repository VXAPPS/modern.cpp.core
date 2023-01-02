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

set(RANGES_SRC ${CMAKE_BINARY_DIR}/_deps/ranges-src)
set(RANGES_INSTALL ${CMAKE_BINARY_DIR}/_deps/ranges-install)
set(RANGES_INCLUDE_DIR ${RANGES_INSTALL}/include)

if(CMAKE_CXX_COMPILER_ID MATCHES "[cC][lL][aA][nN][gG]" AND UNIX AND NOT APPLE)
  set(EXTRA_FLAGS -stdlib=libc++)
endif()

ExternalProject_Add(range-v3
  PREFIX ${RANGES_SRC}
  URL https://github.com/ericniebler/range-v3/archive/refs/tags/0.12.0.tar.gz
  URL_HASH SHA512=b8b632b8e0f2a3234ef61813212c237f648cd741e816ca57bd86f82f6459f7d755e2b70361d2aa43847874fb546a31a792ab1c3ba90292818ae7313438dc62d0
  # GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
  # GIT_TAG 0.12.0
  # GIT_SHALLOW 1
  CMAKE_ARGS
    -DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
    -DCMAKE_CXX_FLAGS=${EXTRA_FLAGS}
    -DCMAKE_OSX_ARCHITECTURES:STRING=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    -DCMAKE_INSTALL_PREFIX:PATH=${RANGES_INSTALL}
    -Dis_subproject:BOOL=OFF
    -DRANGE_V3_DOCS:BOOL=OFF
    -DRANGE_V3_TESTS:BOOL=OFF
    -DRANGE_V3_EXAMPLES:BOOL=OFF
    -DRANGE_V3_PERF:BOOL=OFF
  INSTALL_DIR ${RANGES_INSTALL}
  BUILD_BYPRODUCTS ${RANGES_LIBRARY}
  UPDATE_COMMAND ""
)

# We cannot use find_library because ExternalProject_Add() is performed at build time.
# And to please the property INTERFACE_INCLUDE_DIRECTORIES,
# we make the include directory in advance.
file(MAKE_DIRECTORY ${RANGES_INCLUDE_DIR})

add_library(range-v3::range-v3 INTERFACE IMPORTED GLOBAL)
set_property(TARGET range-v3::range-v3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${RANGES_INCLUDE_DIR})
add_dependencies(range-v3::range-v3 range-v3)

set(RANGES_ABSTRACT
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

/* ranges-v3 header */
#ifdef __clang__
 #pragma clang diagnostic push
 #pragma clang diagnostic ignored \"-Weverything\"
#endif
#ifdef __GNUC__
 #pragma GCC diagnostic push
 #pragma GCC diagnostic ignored \"-Weffc++\"
#endif
#include <range/v3/all.hpp>
#ifdef __GNUC__
 #pragma GCC diagnostic pop
#endif
#ifdef __clang__
 #pragma clang diagnostic pop
#endif

#if defined __clang__ || defined __GNUC__ && ( __GNUC__ == 10 || __GNUC__ == 9 ) || defined __APPLE__
namespace std {

  namespace ranges {

    using ::ranges::all_of\;
    using ::ranges::distance\;
    using ::ranges::transform\;
    using ::ranges::replace\;
    using ::ranges::search\;
    using ::ranges::sort\;
    using ::ranges::unique\;
  }
}
#endif
"
)

write_file(${RANGES_INCLUDE_DIR}/ranges ${RANGES_ABSTRACT})
