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

if(UNIX)
  if(CORE_MASTER_PROJECT)
    set(${PROJECT_NAME}_source Serial.cpp Serial.h unixservice/main.cpp)
  else()
    set(${PROJECT_NAME}_source Serial.cpp Serial.h)
  endif()
endif()

add_library(${PROJECT_NAME}
  ../.github/workflows/integrate.yml
  ../README.md
  ${3RDPARTY_DIR}/source_location.hpp
  CPU.cpp
  CPU.h
  Demangle.cpp
  Demangle.h
  DoubleUtils.cpp
  DoubleUtils.h
  Exec.cpp
  Exec.h
  Keyboard.cpp
  Keyboard.h
  Logger.cpp
  Logger.h
  Logger_any.h
  Logger_container.h
  Logger_enum.h
  StringUtils.cpp
  StringUtils.h
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
  ${${PROJECT_NAME}_source}
)

if(NOT HAVE_RANGES)
  set(${PROJECT_NAME}_includes ${RANGES_INCLUDE_DIR})
endif()

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${3RDPARTY_DIR}
  ${SOURCE_DIR}
  ${SOURCE_DIR}/templates
  PRIVATE
  ${${PROJECT_NAME}_includes}
)

if(UNIX AND NOT APPLE)
  set(${PROJECT_NAME}_libs ${X11_LIBRARIES})
endif()
if(APPLE AND NOT IOS)
  set(${PROJECT_NAME}_libs ${FOUNDATION})
endif()

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  magic_enum
  re2::re2
  ${${PROJECT_NAME}_libs}
)
