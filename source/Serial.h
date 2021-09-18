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

#pragma once

/* stl header */
#include <string>

/**
 * @brief vx (VX APPS) namespace.
 */
namespace vx {

  /**
   * @brief The Baudrate speed enum.
   */
  enum class Baudrate {

    Speed9600 = 9000, /**< Baudrate of 9600. */
    Speed19200 = 19200, /**< Baudrate of 19200. */
    Speed38400 = 38400, /**< Baudrate of 38400. */
    Speed57600 = 57600 /**< Baudrate of 57600. */
  };

  /**
   * @brief Serial communication class.
   * @author Florian Becker <fb\@vxapps.com> (VX APPS)
   */
  class Serial {

  public:
    /**
     * @brief Default constructor for Serial.
     * @param _path   Device path.
     * @param _baudrate   Baudrate.
     */
    explicit Serial( const std::string &_path,
                     Baudrate _baudrate = Baudrate::Speed9600 );

    /**
     * @brief Delete copy assign.
     */
    Serial( Serial const & ) = delete;

    /**
     * @brief Delete move assign.
     */
    Serial( Serial && ) = delete;

    /**
     * @brief Delete copy assign.
     * @return Nothing.
     */
    Serial &operator=( Serial const & ) = delete;

    /**
     * @brief Delete move assign.
     * @return Nothing.
     */
    Serial &operator=( Serial && ) = delete;

    /**
     * @brief Default destructor for Serial.
     */
    virtual ~Serial();

    /**
     * @brief Is the serial device open?
     * @return True, if open - otherwise false.
     */
    inline bool isOpen() const { return m_isOpen; }

    /**
     * @brief Flush the serial port.
     * @return True, if flushing is successful - otherwise false.
     */
    bool flush() const;

    /**
     * @brief Write data to the serial device.
     * @param _data   Date written to the device.
     * @return True, if the data writing was successful - otherwise false.
     */
    bool write( const std::string &_data ) const;

    /**
     * @brief Read data from the serial device.
     * @return Data read from the serial device.
     */
    std::string read() const;

    /**
     * @brief Descriptor of the current device.
     * @return The descriptor of the serial device - -1 is not a valid descriptor.
     */
    inline int descriptor() const { return m_descriptor; }

    /**
     * @brief Close connection to serial device.
     */
    void close();

  private:
    /**
     * @brief Member if device is open.
     */
    bool m_isOpen = false;

    /**
     * @brief Member for descriptor.
     */
    int m_descriptor = -1;
  };
}
