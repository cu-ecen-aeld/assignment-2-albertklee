/*
 * ASSIGNMENT INSTRUCTIONS
 * 
 * Write a program as described below
 * 
 *   - Accepts the following arguments: the first argument is a full
 *     path to a file (including filename) on the filesystem, referred
 *     to below as writefile; the second argument is a text string which
 *     will be written within this file, referred to below as writestr
 * 
 *   - Exits with value 1 error and print statements if any of the
 *     arguments above were not specified
 * 
 *   - Creates a new file with name and path writefile with content
 *     writestr, overwriting any existing file and creating the path if
 *     it doesn’t exist. Exits with value 1 and error print statement if
 *     the file could not be created.
 * 
 * and these additional instructions:
 * 
 *   - One difference from the write.sh instructions in Assignment 1: 
 *     You do not need to make your "writer" utility create directories
 *     which do not exist.  You can assume the directory is created by
 *     the caller.
 * 
 *   - Setup syslog logging for your utility using the LOG_USER
 *     facility.
 * 
 *   - Use the syslog capability to write a message “Writing <string> to
 *     <file>” where <string> is the text string written to file (second
 *     argument) and <file> is the file created by the script.  This
 *     should be written with LOG_DEBUG level.
 * 
 *   - Use the syslog capability to log any unexpected errors with
 *     LOG_ERR level.
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

int main (int argc, char *argv[], char *envp[])
{
  /* file descriptor for the file we write */
  int fd;

  /* bytes written to our file */
  ssize_t written;

  /* syslog setup */
  openlog(NULL, LOG_CONS, LOG_USER);

  /* Argument sanity check */
  if (argc != 3)
  {
    syslog(LOG_ERR, "requires writefile and writestr arguments");
    exit(1);
  }

  /* Argument processing */
  const char *writefile = argv[1];
  const char *writestr  = argv[2];

  /* Compute size of writestr, and also limit to avoid problems */
  const size_t length = strnlen(writestr, SSIZE_MAX);

  /* Output debugging information */
  syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

  /* Create our file and handle error conditions */
  fd = creat(writefile, 0644);
  if (fd == -1)
  {
    syslog(LOG_ERR, "Error creating %s: %s", writefile, strerror(errno));
    exit(1);
  }

  /* Write content to our file and check the result */
  written = write(fd, writestr, length);
  if (written != length)
  {
    syslog(LOG_WARNING, "expected %zu bytes written, but wrote %zu", length, written);
  }

  /* Close the file, while checking its result */
  if (close (fd) == -1)
  {
    syslog(LOG_ERR, "cannot close file");
    exit(1);
  }
}
