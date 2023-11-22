#
# Copyright (c) 2020 Florian Becker <fb@vxapps.com> (VX APPS).
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

if(NOT CMAKE_CXX_COMPILER_ID MATCHES Clang)
  return()
endif()

set(WARNING_FLAGS

  # Own parameter
  -Wno-c++98-compat # C++11
  -Wno-c++98-compat-pedantic # C++11
  -Wno-c++2a-extensions
  -Wno-padded

  # absl dependency
#  -Wno-c++20-compat
#  -Wno-tautological-type-limit-compare
#  -Wno-float-equal
#  -Wno-double-promotion
#  -Wno-global-constructors
#  -Wno-gcc-compat
#  -Wno-unreachable-code-break
#  -Wno-switch-enum
#  -Wno-weak-vtables
#  -Wno-exit-time-destructors
#  -Wno-comma
#  -Wno-thread-safety-negative
#  -Wno-zero-as-null-pointer-constant
#  -Wno-format-nonliteral
#  -Wno-unused-template
#  -Wno-deprecated
#  -Wno-old-style-cast
#  -Wno-missing-noreturn
#  -Wno-missing-variable-declarations
#  -Wno-atomic-implicit-seq-cst
#  -Wno-unused-macros
#  -Wno-disabled-macro-expansion
)

foreach(WARNING_FLAG ${WARNING_FLAGS})
  set(WARNING_FLAGS_SPACED "${WARNING_FLAGS_SPACED} ${WARNING_FLAG}")
endforeach()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Werror -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS_SPACED}")

if(UNIX AND NOT APPLE)
  set(EXTRA_CXX_FLAGS -stdlib=libc++)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_CXX_FLAGS} -lc++abi -fuse-ld=lld")
endif()

if(CORE_MASTER_PROJECT AND CMAKE_BUILD_TYPE STREQUAL Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
endif()
