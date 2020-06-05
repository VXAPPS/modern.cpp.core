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
#include <CPU.h>

/** SGX information leaf. */
constexpr unsigned int sgxLeaf = 12;

/** Maximum subleafs to read out. */
constexpr unsigned int maximumSubLeafs = 10;

int main() {

  VX::CPU cpu;
  std::cout << std::hex << cpu.eax() << " " << cpu.ebx() << " " << cpu.ecx() << " " << cpu.edx() << " " << std::dec <<  std::endl;

  std::cout << "Stepping: " << cpu.stepping() << std::endl;
  std::cout << "Model: " << cpu.model() << std::endl;
  std::cout << "Family: " << cpu.family() << std::endl;
  std::cout << "Type: " << cpu.type() << std::endl;
  std::cout << "Extended model: " << cpu.extendedModel() << std::endl;
  std::cout << "Extended family: " << cpu.extendedFamily() << std::endl;

  std::cout << "SMX support: " << cpu.smxSupport() << std::endl;

  std::cout << std::endl << "Extended features" << std::endl;

  std::cout << "SGX support: " << cpu.sgxSupport() << std::endl;
  std::cout << "SGX launch control support: " << cpu.sgxLaunchControlSupport() << std::endl;

  std::cout << std::endl << "SGX features" << std::endl;

  std::cout << "SGX version 1 support: " << cpu.sgxVersion1Support() << std::endl;
  std::cout << "SGX version 2 support: " << cpu.sgxVersion2Support() << std::endl;
  std::cout << "Maximum enclave size: " << cpu.maximumEnclaveSize() << std::endl;
  std::cout << "Maximum enclave size 64: " << cpu.maximumEnclaveSize64() << std::endl;

  for ( unsigned int i = 1; i < maximumSubLeafs; i++ ) {

    std::cout << std::endl << "SGX subleaf " << i << std::endl;
    cpu.updateNativeId( sgxLeaf, i );
    std::cout << std::hex << cpu.eax() << " " << cpu.ebx() << " " << cpu.ecx() << " " << cpu.edx() << " " << std::endl;
  }
  return 0;
}
