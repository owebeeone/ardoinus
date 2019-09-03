**ardOinus - an Embedded Programming Module API for Arduino in C++**

This software is licensed under the MIT License, see the LICENSE.txt file
for more detail.

ArdOinus is an embedded application framework allowing composition
of re-usable modules targetted for embedded microcontroller applications.

See [the reference guide](bit.ly/2lBFpq7) for more complete information.

ArdOinus aims to be true to the C++ philosophy that you don't pay for what
you don't need (at run time) and hence makes heavy use of C++ templates.
The extensive use of templates results in requiring the minimum version 
of C++11 compiler support.

The main re-usable component is the "module". The module interface is 
described in the ModuleBase class template. It provides 4 static methods and
contains no instance state however client modules can instantiate a module
object if the module requires it. Multiple modules are combinable into an
Applicatiion. The Application class template will combine the given modules, 
this can be considered akin the to "main" function in a C++ program.

Resource collision is handled as a compile time error. Each module must 
define it's parameters and each parameter defines it's claim on resources.
Compile time detection of resource collision is highly desirable since an
invalid allocation does not even result in a runnable program and error 
messages indicate the errormeaning shorter development cycle.
 
This library also abstracts the basic digital GPIO functions in Arduino 
together with the basic time functions. See the ardo::OutputPin and 
ardo::InputPin classes. Open Collector/Drain modes are supported.
