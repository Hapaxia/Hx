#Hx
*by Hapax (2014-2015)*
(http://github.com/Hapaxia)

C++11 required.

Almost everything is within the "hx" namespace (it will be clearly stated if it is not).
All sub-namespaces will begin with a capital letter.

Future modules can depend upon other modules, especially Plinth.

You can include a module using its named header or using a list header in its directory.
e.g. for Plinth: `<Hx/Plinth.hpp>` or `<Hx/Plinth/all.hpp>`

* **Plinth** - foundation module: common, basic, or just small things and can be required by other modules.
* **Plinth/SFML** - foundation module extension for SFML: common or basic, or just small things for SFML. Can be required by other modules that use SFML.
* **Kairos** - timing module: event sequencing, flexible clocks (alterable speed and direction), fps information, timestep simplification.

Make sure you have the modules in the base folder ("Hx") and add the root of the base folder to your include path, then use the Hx in your inclusions e.g. location "c:/libraries/Hx", path should include "c:/libraries", then - for example - `#include <Hx/Plinth/Generic.hpp>`

It is assumed that you know how to build from the include and src folders. It would probably help to include CMake stuff here but CMake does not like me.

Examples are provided for examples of the use of some of the features. If you think a function/class/include/module should have an example, feel free to get in touch. Examples require the module that they are from and may also require other modules and/or libraries. These will be stated.

* Plinth "standard" list (`<Hx/Plinth/standard.hpp>`) has no external dependencies.
* Plinth "sfml" list (`<Hx/Plinth/sfml.hpp>`) requires SFML library.
* Including `<Hx/Plinth.hpp>` or `<Hx/Plinth/all.hpp>` includes both of the above lists so also requires SFML library.
* Kairos (`<Hx/Kairos.hpp>`) has no external dependencies.

Some parts require [SFML](http://sfml-dev.org). Minimum version is 2.0. Recommended version is 2.2+.