/*
 * Copyright (c) 2020 Florian Becker <fb@vxapps.com> (VX APPS).
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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

/* apple header */
#ifdef __APPLE__
  #include <CoreFoundation/CoreFoundation.h>
#endif

/* stl header */
#include <string>
#include <vector>

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief Trim from end of string (right).
   * @param _string   String to trim.
   * @param _trim   What signs to trim
   * Default: Space, tabs, return, new line and form feed.
   * @return Right trimmed string.
   */
  std::string &rightTrim( std::string &_string,
                          const std::string &_trim = {} );

  /**
   * @brief Trim from beginning of string (left).
   * @param _string   String to trim.
   * @param _trim   What signs to trim
   * Default: Space, tabs, return, new line and form feed.
   * @return Left trimmed string.
   */
  std::string &leftTrim( std::string &_string,
                         const std::string &_trim = {} );

  /**
   * @brief Trim from both ends of string (right then left).
   * @param _string   String to trim.
   * @param _trim   What signs to trim
   * Default: Space, tabs, return, new line and form feed.
   * @return Both ends trimmed string.
   */
  std::string &trim( std::string &_string,
                     const std::string &_trim = {} );

  /**
   * @brief Check if string starts with start.
   * @param _string   String to check.
   * @param _start   Start check.
   * @return True, if string starts with start - otherwise false.
   */
  bool startsWith( const std::string &_string,
                   const std::string &_start );

  /**
   * @brief Check if string ends with start.
   * @param _string   String to check.
   * @param _end   End check.
   * @return True, if string ends with end - otherwise false.
   */
  bool endsWith( const std::string &_string,
                 const std::string &_end );

  /**
   * @brief Tokenize string by separator.
   * @param _string   String to split.
   * @param _separator   Separator for the splitting.
   * @return Splitted list of splits.
   */
  std::vector<std::string> tokenize( const std::string &_string,
                                     const std::string &_separator );

#ifdef __APPLE__
  /**
   * @brief Returns standard string from CFStringRef.
   * @return Standard string from CFStringRef.
   */
  std::string fromCFStringRef( CFStringRef _stringRef );
#endif
}
