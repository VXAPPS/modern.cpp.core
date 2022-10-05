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

include(CheckCSourceCompiles)
include(CheckIncludeFiles)

check_include_file_cxx(format HAVE_FORMAT_INCLUDE)
if(HAVE_FORMAT_INCLUDE)
  check_cxx_source_compiles(
    "#include <format>
    int main() { std::string nodiscard = std::format( \"The answer is {}.\", 42 ); (void)nodiscard; return 0; }"
    HAVE_FORMAT
  )
endif()

check_include_file_cxx(source_location HAVE_SOURCE_LOCATION_INCLUDE)
if(HAVE_SOURCE_LOCATION_INCLUDE)
  check_cxx_source_compiles(
    "#include <source_location>
    int main() { const std::source_location location = std::source_location::current(); (void)location; return 0; }"
    HAVE_SOURCE_LOCATION
  )
endif()

check_include_file_cxx(span HAVE_SPAN_INCLUDE)
if(HAVE_SPAN_INCLUDE)
  check_cxx_source_compiles(
    "#include <span>
    int main(int argc, char **argv) { std::span args( argv, static_cast<std::size_t>( argc ) ); return 0; }"
    HAVE_SPAN
  )
endif()
