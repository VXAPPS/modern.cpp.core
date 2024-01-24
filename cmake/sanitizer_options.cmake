#
# Copyright (c) 2023 Florian Becker <fb@vxapps.com> (VX APPS).
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

if(SANITIZER_ADDRESS)
  # clang-11 cannot allocate
  if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    string(REPLACE "." ";" VERSION_LIST ${CMAKE_CXX_COMPILER_VERSION})
    list(GET VERSION_LIST 0 CLANG_VERSION_MAJOR)
    if(CLANG_VERSION_MAJOR EQUAL 11)
      set(ASAN_OPTIONS ASAN_OPTIONS=use_sigaltstack=false)
      get_property(ALL_TESTS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY TESTS)
      set_tests_properties(${ALL_TESTS} PROPERTIES ENVIRONMENT ${ASAN_OPTIONS})
    endif()
  endif()

  # gcc needs LD_PRELOAD of libasan and ignore link order
  if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    set(ASAN_OPTIONS ASAN_OPTIONS=verify_asan_link_order=0)
    get_property(ALL_TESTS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY TESTS)
    set_tests_properties(${ALL_TESTS} PROPERTIES ENVIRONMENT ${ASAN_OPTIONS})
  endif()

  if(WIN32)
    set(ASAN_OPTIONS ASAN_OPTIONS=windows_hook_rtl_allocators=true)
    get_property(ALL_TESTS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY TESTS)
    set_tests_properties(${ALL_TESTS} PROPERTIES ENVIRONMENT ${ASAN_OPTIONS})

    # copy runtime library
    get_filename_component(ASAN_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
      file(COPY ${ASAN_DIR}/clang_rt.asan_dbg_dynamic-i386.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    else()
      file(COPY ${ASAN_DIR}/clang_rt.asan_dbg_dynamic-x86_64.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    endif()
  endif()
endif()
