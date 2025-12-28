# cgraph

A single header C99 library to create graphs and plots.

## Functional Goals
- Allow users to create a variety of graphs
- Export said graphs to a variety of image formats
- Not rely on any third-party dependencies (ie handle all the rendering internally)
- Allow users to customize the look/style of their graphs

## Usage
Simply define `CGRAPH_IMPLEMENTATION` and then include the header file:

```c
#define CGRAPH_IMPLEMENTATION
#include "cgraph.h"
```

## License

cgraph is licensed under the MIT license
