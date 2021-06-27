//

#include "setl_support.h"

#if HAS_STDIOSTREAM
#include <iostream>
#endif



#include "tests/ardOinus_test.h"

#include "tests/setl_templ_utils_test.h"
#include "pwe_serial.h"
#include "tests/pwe_serial_test.h"

#include "tests/setl_time_test.h"
#include "tests/setl_time_unit_test.h"

#include "circular_buffer.h"

#include "type_for_size.h"
#include "tests/type_for_size_test.h"

#include "tests/setl_cyclic_int_test.h"

#include "tests/circular_buffer_test.h"

#include "tests/ardo_singleton_test.h"


#if HAS_STDIOSTREAM

int main(int, char **)
{
  std::cout << "Hello world!\n";

  std::cout << "successfull tests = " << setl_test::runAllTests() << "\n";

  std::cout << "Goodbye world!\n";
}

#endif
