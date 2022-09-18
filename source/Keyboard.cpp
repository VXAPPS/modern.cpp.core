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

#ifdef _MSC_VER
  #include <Windows.h>
#elif defined __APPLE__
  #include <Carbon/Carbon.h>
#else
  #if 1
    #include <X11/Xlib.h>
    #include <X11/keysym.h>
  #else
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
  #endif
#endif

/* local header */
#include "Keyboard.h"

namespace vx::keyboard {

  bool isCapsLockActive() {

    bool isActive = false;

#ifdef _MSC_VER
    if ( GetAsyncKeyState( VK_CAPITAL ) & 0x0001 ) {

      isActive = true;
    }
#elif defined __APPLE__

#if 1
    /* Variant 1 Carbon.framework */
    KeyMap keyMap;
    GetKeys( keyMap );

    int index = kVK_CapsLock >> 5;
    int shift = kVK_CapsLock & 31;

    isActive = ( ( keyMap[ index ].bigEndianValue >> shift ) & 1 ) != 0;
#else
    /* Variant 2 CoreGraphics.framework */
    isActive = CGEventSourceKeyState( kCGEventSourceStateHIDSystemState, kVK_CapsLock );
#endif

#else

#if 1
    /* Variant 1 X11 */
    Display *display = XOpenDisplay( nullptr );
    XKeyboardState keyboardState {};
    XGetKeyboardControl( display, &keyboardState );
    isActive = keyboardState.led_mask & 1U;
    XCloseDisplay( display );
#else
    /* Variant 2 ioctl */
//    int fd = open( "/dev/console", O_RDONLY );
//    if ( fd == -1 ) {

      //
//    }
//    ioctl( fd, 0x4B32, 0x04 );
//    close( fd );
#endif

#endif
    return isActive;
  }
}
