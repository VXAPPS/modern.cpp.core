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
  set(${PROJECT_NAME}_os_src Serial.cpp Serial.h) # unixservice/main.cpp)
endif()

add_library(${PROJECT_NAME}
  ../.github/workflows/integrate.yml
  ../README.md
  ${3RDPARTY_DIR}/magic_enum.hpp
  CPU.cpp
  CPU.h
  DoubleUtils.cpp
  DoubleUtils.h
  Exec.cpp
  Exec.h
  Keyboard.cpp
  Keyboard.h
  StringUtils.cpp
  StringUtils.h
  Timing.cpp
  Timing.h
  templates/CSVWriter.h
  templates/SharedQueue.h
  templates/Singleton.h
  templates/Timer.h
  ${${PROJECT_NAME}_os_src}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/templates ${3RDPARTY_DIR})
