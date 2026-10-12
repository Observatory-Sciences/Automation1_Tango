#ifndef UTILS_H
#define UTILS_H

#include <tango/tango.h>

#ifndef TANGO_MAKE_VERSION
  #define TANGO_MAKE_VERSION(major, minor, patch) ((major) * 10000 + (minor) * 100 + (patch))
#endif // !TANGO_MAKE_VERSION

#ifndef TANGO_VERSION
  #define TANGO_VERSION TANGO_MAKE_VERSION(TANGO_VERSION_MAJOR, TANGO_VERSION_MINOR, TANGO_VERSION_PATCH)
#endif // !TANGO_VERSION

#endif // UTILS_H
