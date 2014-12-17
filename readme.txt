******
* Hx *
******
by Hapax (2014)
(github.com/Hapaxia)

C++11 required.

Almost everything is within the "hx" namespace (it will be clearly stated if it is not).
All sub-namespaces will be begin with a capital.

Future modules can depend upon other modules, especially Plinth.

You can include a module using its named header or using a list header in its directory.
e.g. for Plinth: <Hx/Plinth.hpp> or <Hx/Plinth/all.hpp>

Plinth - foundation module: common, basic, or just small things and can be required by other modules.
Plinth/SFML - foundation module extension for SFML: common or basic, or just small things for SFML. Can be required by other modules that use SFML.

Plinth "standard" list (<Hx/Plinth/standard.hpp>) has no external dependencies.
Plinth "sfml" list (<Hx/Plinth/sfml.hpp>) requires SFML library.
Including <Hx/Plinth.hpp> or <Hx/Plinth/all.hpp> includes both of these lists so also requires SFML library.

Make sure you have the modules in the base folder ("Hx") and add the root of the base folder to your include path, then use the Hx in your inclusions e.g. location "c:/libraries/Hx", path should include "c:/libraries", then - for example - #include <Hx/Plinth/Generic.hpp>

It is assumed that you know how to build from the include and src folders. It would probably help to include CMake stuff here but CMake does not like me.

Some parts require SFML (sfml-dev.org). Minimum version is 2.0. Recommended version is 2.2+.