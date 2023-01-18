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

function(make_test target)
  project(test_${target})

  add_executable(${PROJECT_NAME}
    ${PROJECT_NAME}.cpp
  )

  target_link_libraries(${PROJECT_NAME}
    PRIVATE
    modern.cpp::core
    GTest::gtest_main
  )

  gtest_add_tests(${PROJECT_NAME}
    SOURCES ${PROJECT_NAME}.cpp
  )
endfunction()

make_test(csv)
make_test(demangle)
make_test(floating_point)

project(test_format)

add_executable(${PROJECT_NAME}
  ${PROJECT_NAME}.cpp
)

if(NOT HAVE_FORMAT)
  set(${PROJECT_NAME}_libs fmt::fmt)
endif()

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  modern.cpp::core
  GTest::gtest_main
  ${${PROJECT_NAME}_libs}
)

gtest_add_tests(${PROJECT_NAME}
  SOURCES ${PROJECT_NAME}.cpp
)

make_test(line)
make_test(magic_enum)
make_test(point)
make_test(rect)
make_test(size)
make_test(string_utils)

if(CORE_MASTER_PROJECT AND CMAKE_BUILD_TYPE STREQUAL Debug)
  include(${CMAKE}/coverage.cmake)
  include(${CMAKE}/sanitizer_options.cmake)
  include(${CMAKE}/test_options.cmake)
endif()
