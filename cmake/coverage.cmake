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

if(CMAKE_CXX_COMPILER_ID MATCHES "[cC][lL][aA][nN][gG]")
  string(REPLACE "." ";" CLANG_VERSION_LIST ${CMAKE_CXX_COMPILER_VERSION})
  list(GET CLANG_VERSION_LIST 0 CLANG_MAJOR)
  if(APPLE)
    set(LLVM_PROFDATA_EXECUTABLE xcrun llvm-profdata)
    set(LLVM_COV_EXECUTABLE xcrun llvm-cov)
  else()
    find_program(LLVM_PROFDATA_EXECUTABLE NAMES llvm-profdata-${CLANG_MAJOR} llvm-profdata)
    find_program(LLVM_COV_EXECUTABLE NAMES llvm-cov-${CLANG_MAJOR} llvm-cov)
  endif()
  if(LLVM_PROFDATA_EXECUTABLE)
    add_custom_target(coverage-merge
      COMMAND ${LLVM_PROFDATA_EXECUTABLE} merge --sparse ${CMAKE_CURRENT_BINARY_DIR}/*.profraw -o coverage.profdata
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Merging coverage data")

    if(LLVM_COV_EXECUTABLE)
      get_property(TEST_TARGETS DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} PROPERTY BUILDSYSTEM_TARGETS)
      foreach(TEST_TARGET IN LISTS TEST_TARGETS)
        if(TEST_TARGET MATCHES test_*)
          set(TEST_TARGETS_JOINED ${TEST_TARGETS_JOINED} --object=${CMAKE_CURRENT_BINARY_DIR}/${TEST_TARGET})
        endif()
      endforeach()

      add_custom_target(coverage-report
        COMMAND ${LLVM_COV_EXECUTABLE} show --instr-profile=${CMAKE_CURRENT_BINARY_DIR}/coverage.profdata --format=text --Xdemangler=c++filt ${TEST_TARGETS_JOINED} > ${CMAKE_CURRENT_BINARY_DIR}/coverage.clang-${CLANG_MAJOR}.txt
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating coverage report"
        DEPENDS coverage-merge)

      add_custom_target(coverage
        COMMAND ${LLVM_COV_EXECUTABLE} report --instr-profile=${CMAKE_CURRENT_BINARY_DIR}/coverage.profdata ${TEST_TARGETS_JOINED} > ${CMAKE_CURRENT_BINARY_DIR}/coverage.overview.clang-${CLANG_MAJOR}.txt
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating coverage"
        DEPENDS coverage-report)
    endif()
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  find_program(GCOV_EXECUTABLE gcov)
  find_program(LCOV_EXECUTABLE NAMES lcov lcov.bat lcov.exe lcov.perl)
  find_program(CPPFILT_EXECUTABLE NAMES c++filt)
endif()
