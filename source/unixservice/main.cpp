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

/* system header */
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>

/* stl header */
#include <fstream>
#include <sstream>
#include <string>

constexpr auto DAEMON_NAME = "Demo";

/* For security purposes, we don't allow any arguments to be passed into the daemon */
int main() {

  // DAEMONIZE START
  /* Define variables */
  pid_t pid, sid;

  /* Fork the current process */
  pid = fork();
  /* The parent process continues with a process ID greater than 0 */
  if ( pid > 0 ) {

    exit( EXIT_SUCCESS );
  }
  /* A process ID lower than 0 indicates a failure in either process */
  else if ( pid < 0 ) {

    exit( EXIT_FAILURE );
  }
  /* The parent process has now terminated, and the forked child process will continue */
  /* (the pid of the child process was 0) */

  /* Since the child process is a daemon, the umask needs to be set so files and logs can be written */
  umask( 0 );

  /* Open system logs for the child process */
  openlog( DAEMON_NAME, LOG_NOWAIT | LOG_PID, LOG_USER );
  syslog( LOG_NOTICE, "Successfully started %s", DAEMON_NAME );

  // Generate a session ID for the child process
  sid = setsid();
  /* Ensure a valid SID for the child process */
  if ( sid < 0 ) {

    /* Log failure and exit */
    syslog( LOG_ERR, "Could not generate session ID for child process" );

    /* If a new session ID could not be generated, we must terminate the child process */
    /* or it will be orphaned */
    exit( EXIT_FAILURE );
  }

  /* Change the current working directory to a directory guaranteed to exist */
  if ( ( chdir( "/" ) ) < 0 ) {

    /* Log failure and exit */
    syslog( LOG_ERR, "Could not change working directory to /" );

    /* If our guaranteed directory does not exist, terminate the child process to ensure */
    /* the daemon has not been hijacked */
    exit( EXIT_FAILURE );
  }

  /* A daemon cannot use the terminal, so close standard file descriptors for security reasons */
  close( STDIN_FILENO );
  close( STDOUT_FILENO );
  close( STDERR_FILENO );

  /* Ensure only one copy */
  std::stringstream ss;
  ss << "/var/run/" << DAEMON_NAME << ".pid";
  std::string pidfile = ss.str();

  std::ifstream fileCheck( pidfile );
  /* Try to lock file - or even check if its available on c++ */
  if ( !fileCheck.good() ) {

    /* Couldn't get lock on lock file */
    /* NOTE: In c++ it is not (yet) possible to lock a file */
    std::ofstream fileCreate;
    fileCreate.open( pidfile );
    if ( !fileCreate.is_open() ) {

      /* Couldn't create lock file */
      syslog( LOG_INFO, "Could not create PID lock file %s, exiting", pidfile.c_str() );
      exit( EXIT_FAILURE );
    }
    fileCreate.close();
  }

  std::ofstream file;
  file.open( pidfile, std::ofstream::out | std::ofstream::in );
  if ( !file.is_open() ) {

    /* Couldn't open lock file */
    syslog( LOG_INFO, "Could not open PID lock file %s, exiting", pidfile.c_str() );
    exit( EXIT_FAILURE );
  }

  /* Read pid from file, if there is any, find if the process is running - EXIT */
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string currentPid = buffer.str();

  /* Get and format PID */
  std::string str = std::to_string( getpid() );
  if ( !currentPid.empty() && currentPid != str ) {

    /* Couldn't open lock file */
    syslog( LOG_INFO, "Service allready running as PID %s, exiting", currentPid.c_str() );
    exit( EXIT_FAILURE );
  }

  /* write pid to lockfile */
  file << str;
  file.close();
  // DAEMONIZE END

  // SERVICE START
  /* Daemon-specific intialization should go here */

  // SERVICE END

  // CLEANUP START
  /* Close system logs for the child process */
  syslog( LOG_NOTICE, "Stopping %s", DAEMON_NAME );
  closelog();

  /* Remove content of file */
  std::ofstream ofs;
  ofs.open( pidfile, std::ofstream::out | std::ofstream::trunc );
  ofs.close();
  // CLEANUP END

  /* Terminate the child process when the daemon completes */
  exit( EXIT_SUCCESS );
}
