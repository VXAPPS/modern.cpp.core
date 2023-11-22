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

project(modern.cpp.core)

add_library(${PROJECT_NAME}
  CPU.cpp
  CPU.h
  Demangle.cpp
  Demangle.h
  Exec.cpp
  Exec.h
  Keyboard.cpp
  Keyboard.h
  Logger.cpp
  Logger.h
  Logger_any.h
  Logger_container.h
  Logger_enum.h
  Serial.cpp
  Serial.h
  StringUtils.cpp
  StringUtils.h
  StringUtils_apple.cpp
  StringUtils_apple.h
  Timestamp.cpp
  Timestamp.h
  Timing.cpp
  Timing.h
  templates/Cpp23.h
  templates/CSVWriter.h
  templates/FloatingPoint.h
  templates/Line.h
  templates/Point.h
  templates/Rect.cpp
  templates/Rect.h
  templates/SharedQueue.h
  templates/Singleton.h
  templates/Size.h
  templates/Timer.h
  templates/TypeCheck.h
  unixservice/main.cpp
)

add_library(modern.cpp::core ALIAS ${PROJECT_NAME})

if(NOT APPLE)
  set(${PROJECT_NAME}_source ${${PROJECT_NAME}_source} StringUtils_apple.cpp)
endif()
if(WIN32)
  set(${PROJECT_NAME}_source ${${PROJECT_NAME}_source} Serial.cpp)
endif()
if(NOT CORE_MASTER_PROJECT OR WIN32)
  set(${PROJECT_NAME}_source ${${PROJECT_NAME}_source} unixservice/main.cpp)
endif()
set_source_files_properties(${${PROJECT_NAME}_source} PROPERTIES HEADER_FILE_ONLY TRUE)

target_compile_definitions(${PROJECT_NAME}
  PUBLIC
  $<$<BOOL:${HAVE_JTHREAD}>:HAVE_JTHREAD>
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${3RDPARTY_DIR}
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/templates
)

if(UNIX AND NOT APPLE)
  set(${PROJECT_NAME}_libs ${X11_LIBRARIES})
elseif(APPLE AND NOT IOS)
  set(${PROJECT_NAME}_libs ${FOUNDATION})
endif()

if(NOT HAVE_RANGES)
  set(${PROJECT_NAME}_libs ${${PROJECT_NAME}_libs} range-v3::range-v3)
endif()

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  magic_enum::magic_enum
  re2::re2
  absl::raw_hash_set # re2 is using them
  absl::str_format_internal # re2 is using them
  Threads::Threads # re2 is using them
  ${${PROJECT_NAME}_libs}
)

add_custom_target(${PROJECT_NAME}_3rdparty
  SOURCES
  ${3RDPARTY_DIR}/jthread.hpp
  ${3RDPARTY_DIR}/source_location.hpp
  ${3RDPARTY_DIR}/stop_token.hpp
)

add_custom_target(${PROJECT_NAME}_documentation
  SOURCES
  ../docs/corefoundation-doxygen-web.tag.xml
  ../docs/cppreference-doxygen-web.tag.xml
  ../docs/Doxyfile.in
  ../docs/footer.html
  ../docs/header.html
  ../docs/magic_enum-doxygen-web.tag.xml
  ../docs/post_doxygen.py
  ../README.md
)

add_custom_target(${PROJECT_NAME}_workflows
  SOURCES
  ../.github/workflows/linux-codeql.yml
  ../.github/workflows/linux.yml
  ../.github/workflows/macos-codeql.yml
  ../.github/workflows/macos.yml
  ../.github/workflows/windows-codeql.yml
  ../.github/workflows/windows.yml
)
