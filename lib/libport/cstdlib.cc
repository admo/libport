#include <libport/detect-win32.h>
#include <string>
#include <libport/cstdlib>

#if defined MSVC || defined __MINGW32__

extern "C"
{
  int
  setenv(const char* key, const char* value, int overwrite)
  {
    if (!overwrite && getenv(key))
      return 0;
#if defined __MINGW32__ // MinGW has no _putenv_s
    return _putenv((std::string(key) + "=" + value).c_str());
#else
    return _putenv_s(key, value);
#endif
  }

  int
  unsetenv(const char* key)
  {
    // Windows refuses 0 as a value.  But passing "" actually unsets
    // the envvar.
    return setenv(key, "", 1);
  }
}

#endif

#ifdef MSVC

extern "C"
{
  long long
  strtoll(const char* nptr, char** endptr, int base)
  {
    return _strtoi64(nptr, endptr, base);
  }
}

#endif
