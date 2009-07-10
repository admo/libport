#ifndef LIBPORT_SYS_STAT_H_
# define LIBPORT_SYS_STAT_H_

# include <sys/stat.h>
# include <libport/detect-win32.h>

# ifdef WIN32

#  ifndef S_ISDIR
#   define S_ISDIR(x) (((x) & S_IFMT) == S_IFDIR)
#  endif

int mkdir(const char *path, mode_t mode);

# endif

# include <libport/sys/stat.hxx>

#endif /* !LIBPORT_SYS_STAT_H_ */
