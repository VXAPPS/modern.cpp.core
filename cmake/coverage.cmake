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

# Check prereqs
find_program(GCOV_PATH gcov)
find_program(LCOV_PATH  NAMES lcov lcov.bat lcov.exe lcov.perl)
#find_program(FASTCOV_PATH NAMES fastcov fastcov.py )
#find_program(GENHTML_PATH NAMES genhtml genhtml.perl genhtml.bat )
#find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/scripts/test)
find_program(CPPFILT_PATH NAMES c++filt)

if(CMAKE_CXX_COMPILER_ID MATCHES "[cC][lL][aA][nN][gG]")
  string(REPLACE "." ";" CLANG_VERSION_LIST ${CMAKE_CXX_COMPILER_VERSION})
  list(GET CLANG_VERSION_LIST 0 CLANG_MAJOR)
  if(APPLE)
    set(LLVM_PROFDATA_PATH xcrun llvm-profdata)
    set(LLVM_PROFDATA_PATH_FOUND TRUE)
    set(LLVM_COV_PATH xcrun llvm-cov)
    set(LLVM_COV_PATH_FOUND TRUE)
  else()
    find_program(LLVM_PROFDATA_PATH NAMES llvm-profdata-${CLANG_MAJOR} llvm-profdata)
    find_program(LLVM_COV_PATH NAMES llvm-cov-${CLANG_MAJOR} llvm-cov)
  endif()
  if(LLVM_PROFDATA_PATH_FOUND)
    add_custom_target(coverage-merge
      COMMAND ${LLVM_PROFDATA_PATH} merge --sparse ${CMAKE_BINARY_DIR}/tests/*.profraw -o coverage.profdata
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
      COMMENT "Merge coverage data")

    if(LLVM_COV_PATH_FOUND)
      get_property(TEST_TARGETS DIRECTORY "${CMAKE_SOURCE_DIR}/tests" PROPERTY BUILDSYSTEM_TARGETS)
      foreach(TEST_TARGET IN LISTS TEST_TARGETS)
        if(TEST_TARGET MATCHES "test_*")
          set(TEST_TARGETS_JOINED ${TEST_TARGETS_JOINED} --object=${TEST_TARGET})
        endif()
      endforeach()

      add_custom_target(coverage-report
        COMMAND ${LLVM_COV_PATH} show --instr-profile=${CMAKE_BINARY_DIR}/tests/coverage.profdata --format=text --Xdemangler=c++filt ${TEST_TARGETS_JOINED} > ${CMAKE_BINARY_DIR}/tests/coverage-clang-${CLANG_MAJOR}.txt
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
        COMMENT "Create coverage report"
        DEPENDS coverage-merge)

      add_custom_target(coverage
        COMMAND ${LLVM_COV_PATH} report --instr-profile=${CMAKE_BINARY_DIR}/tests/coverage.profdata ${TEST_TARGETS_JOINED} > ${CMAKE_BINARY_DIR}/tests/coverage-overview-clang-${CLANG_MAJOR}.txt
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
        COMMENT "Create coverage report"
        DEPENDS coverage-report)
    endif()
  endif()
#  get_property(ALL_TESTS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY TESTS)
#  foreach(SINGLE_TEST ${ALL_TESTS})
#    if(ASAN_OPTIONS)
#      set_tests_properties(${SINGLE_TEST} PROPERTIES ENVIRONMENT LLVM_PROFILE_FILE=${CMAKE_CURRENT_BINARY_DIR}/${SINGLE_TEST}.profraw ENVIRONMENT ${ASAN_OPTIONS})
#    else()
#      set_tests_properties(${SINGLE_TEST} PROPERTIES ENVIRONMENT LLVM_PROFILE_FILE=${CMAKE_CURRENT_BINARY_DIR}/${SINGLE_TEST}.profraw)
#    endif()
#  endforeach()
endif()
