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

/* stl header */
#include <iostream>

/* modern.cpp.core header */
#include <Exec.h>

int main() {

  int code = 0;
  std::string result = "EXIT_SUCCESS";
  std::string pipe = {};

  std::cout << "----- Result: EXIT_SUCCESS stdout" << std::endl;
  pipe = VX::exec( "../pipe/pipe 0 2>/dev/null" );
  code = VX::result();
  if ( code != EXIT_SUCCESS ) {

    result = "EXIT_FAILURE";
  }
  std::cout << "'" << pipe << "'" << std::endl;
  std::cout << "Result: " << result << std::endl;

  std::cout << "----- Result: EXIT_SUCCESS mixed stdout and stderr" << std::endl;
  pipe = VX::exec( "../pipe/pipe 0 2>&1" );
  code = VX::result();
  if ( code != EXIT_SUCCESS ) {

    result = "EXIT_FAILURE";
  }
  std::cout << "'" << pipe << "'" << std::endl;
  std::cout << "Result: " << result << std::endl;

  std::cout << "----- Result: EXIT_FAILURE stdout" << std::endl;
  pipe = VX::exec( "../pipe/pipe 1 2>/dev/null" );
  code = VX::result();
  if ( code != EXIT_SUCCESS ) {

    result = "EXIT_FAILURE";
  }
  std::cout << "'" << pipe << "'" << std::endl;
  std::cout << "Result: " << result << std::endl;

  std::cout << "----- Result: EXIT_FAILURE mixed stdout and stderr" << std::endl;
  pipe = VX::exec( "../pipe/pipe 1 2>&1" );
  code = VX::result();
  if ( code != EXIT_SUCCESS ) {

    result = "EXIT_FAILURE";
  }
  std::cout << "'" << pipe << "'" << std::endl;
  std::cout << "Result: " << result << std::endl;

  return EXIT_SUCCESS;
}