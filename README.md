SolidUtils
----------

<a href="https://travis-ci.org/solidlake/solidutils">
<img src="https://travis-ci.org/solidlake/solidutils.svg?branch=master"/>
</a>

<a href="https://ci.appveyor.com/project/dlasalle/solidutils">
  <img src="https://ci.appveyor.com/api/projects/status/n1k33omwju8r0ynb?svg=true"/>
</a>

<a href='http://solidutils.readthedocs.io/en/latest/?badge=latest'>
<img src='https://readthedocs.org/projects/solidutils/badge/?version=latest' alt='Documentation Status' />
</a>

C++ utility classes.


Usage
-----

This repository is meant to be used as a submodule in other projects.

```bash
git submodule add https://github.com/solidlake/solidutils
```

And then from within a source file (assuming where you added `solidutils` is in
your include path):

```c++
#include "solidutils/FixedSet.hpp"
```


What's in here?
---------------

While the utilities in this repository provide functionality similar to some of
that found the Standard Template Library, there should be no duplication except
that which provides functionality for early standards from later ones.
