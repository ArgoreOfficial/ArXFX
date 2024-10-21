# Argore GFX
common C graphics library with runtime-switchable interface

## GFX
Graphics API source

### Basic Usage
```c
#include <gfx/gfx.h>
#include <gfx/impl/gfx_opengl.h>

int main()
{
  // create window ...

  gfxLoadOpenGL( glfwGetProcAddress );

  // TODO

  return 0;
}

```

## GFX-HGEN
Header generation tool for the API. Similar to GLAD in that it creates function pointer typedefs.  
