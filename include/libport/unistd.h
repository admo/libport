#ifndef LIBPORT_UNISTD_H
# define LIBPORT_UNISTD_H

# include <libport/detect-win32.h>
# include <libport/windows.hh> // Get sleep wrapper

# include <libport/config.h>

// This is traditional Unix file.
# ifdef LIBPORT_HAVE_UNISTD_H
#  include <unistd.h>
# endif

// OSX does not have O_LARGEFILE.  No information was found whether
// some equivalent flag is needed or not.  Other projects simply do as
// follows.
# ifndef O_LARGEFILE
#  define O_LARGEFILE 0
# endif

// This seems to be its WIN32 equivalent.
// http://msdn2.microsoft.com/en-us/library/ms811896(d=printer).aspx#ucmgch09_topic7.
# if defined WIN32 || defined LIBPORT_WIN32
#  include <io.h>
# endif

/*---------.
| access.  |
`---------*/

# ifdef WIN32
// Windows does not define access() or the corresponding constants.
// http://msdn.microsoft.com/en-us/library/1w06ktdy(VS.80).aspx
#  define F_OK 0
#  define W_OK 2
#  define R_OK 4
#  define access _access
# endif

/*--------.
| chdir.  |
`--------*/

# ifdef WIN32
#  include <direct.h>
#  define chdir _chdir
# endif

/*--------------.
| closesocket.  |
`--------------*/

# ifdef WIN32
#  include <winsock2.h>
# endif

/*--------------.
| closeSocket.  |
`--------------*/

namespace libport
{

  inline
  int
  closeSocket(int socket)
  {
# if defined WIN32
    return closesocket(socket);
# else
    return close(socket);
# endif
  }

}

/*---------.
| getcwd.  |
`---------*/

# if !defined LIBPORT_HAVE_GETCWD
#  if defined LIBPORT_HAVE__GETCWD
#   define getcwd _getcwd
#  elif defined LIBPORT_URBI_ENV_AIBO
    // Will be defined in libport/unistd.cc.
#  else
#   error I need either getcwd() or _getcwd()
#  endif
# endif

#endif // !LIBPORT_UNISTD_H
