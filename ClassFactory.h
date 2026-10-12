#ifndef CLASSFACTORY_H
#define CLASSFACTORY_H

#include <tango/tango.h>
#include "Utils.h"

#if TANGO_VERSION >= TANGO_MAKE_VERSION(10, 3, 0)

namespace Automation1_ns {

Tango::DServer *constructor(Tango::DeviceClass *cl_ptr,
                            const std::string &name,
                            const std::string &desc,
                            Tango::DevState state,
                            const std::string &status);
}

#endif
#endif // CLASSFACTORY_H
