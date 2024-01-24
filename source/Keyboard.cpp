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

/* c header */
#include <cstdint> // std::int32_t, std::uint32_t, std::int64_t
#ifdef __linux__
  #include <cstring> // strerror_r
#endif

/* stl header */
#ifdef __linux__
  #include <vector>
#endif

#ifdef _MSC_VER
  #include <Windows.h>
#elif defined __APPLE__
  #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Welaborated-enum-base"
  #endif
  #include <Carbon/Carbon.h>
  #ifdef __clang__
    #pragma clang diagnostic pop
  #endif
#else
  #if 1
    #include <X11/Xlib.h>
    #include <X11/keysym.h>
  #else
    #include <fcntl.h> // open
    #include <iostream>
    #include <linux/kd.h>
    #include <sys/ioctl.h>
    #include <unistd.h> // close
  #endif
#endif

/* local header */
#include "Keyboard.h"

namespace vx::keyboard {

  bool isCapsLockActive() noexcept {

    bool isActive = false;

#ifdef _MSC_VER
    if ( GetAsyncKeyState( VK_CAPITAL ) & 0x0001 ) {

      isActive = true;
    }
#elif defined __APPLE__

  #if 1
    /* Variant 1 Carbon.framework */
    KeyMap keyMap {};
    GetKeys( keyMap );

    constexpr std::uint32_t five = 5U;
    constexpr std::uint32_t thirtyone = 31U;
    const std::uint32_t index = kVK_CapsLock >> five;
    const std::uint32_t shift = kVK_CapsLock & thirtyone;

    isActive = ( ( keyMap[ index ].bigEndianValue >> shift ) & 1U ) != 0;
  #else
    /* Variant 2 CoreGraphics.framework */
    isActive = CGEventSourceKeyState( kCGEventSourceStateHIDSystemState, kVK_CapsLock );
  #endif

#else

  #if 1
    /* Variant 1 X11. */
    Display *display = XOpenDisplay( nullptr );
    XKeyboardState keyboardState {};
    XGetKeyboardControl( display, &keyboardState );
    isActive = keyboardState.led_mask & 1U;
    XCloseDisplay( display );
  #else
    /* Variant 2 ioctl */
    const std::int32_t descriptor = ::open( "/dev/console", O_RDONLY | O_NOCTTY );
    if ( descriptor == -1 ) {

      constexpr std::int32_t len = 128;
      std::vector<std::int8_t> buffer( len );
      std::cout << "Unable to open console port: /dev/console. Error: " << strerror_r( errno, buffer.data(), buffer.size() ) << std::endl;
    }
    std::int64_t result = 0;
    if ( ::ioctl( descriptor, KDGKBLED, &result ) == -1 ) {

      perror( "ioctl" );
    }
    ::close( descriptor );
  #endif

#endif
    return isActive;
  }
}
