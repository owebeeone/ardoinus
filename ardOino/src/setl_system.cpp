#include "setl_system.h"

#include <iostream>

void setl::System::logDebugFatal(const char * message)
{
  std::cerr << message << std::endl;
}
