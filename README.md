*This project is not actively maintained by its original author and this repository is a fork.*

Main changes
============

- Replaced custom build system by cmake
- Build both shared and static libraries, including all the backends
- Support pkg-config for compiling and linking software that depends on nanovg
- Added examples of its usage in Python, via ctypes
- Integrated nanosvg code into the main library

NanoVG
==========

NanoVG is small antialiased vector graphics rendering library for OpenGL. It has lean API modeled after HTML5 canvas API. It is aimed to be a practical and fun toolset for building scalable user interfaces and visualizations.

## Screenshot

![screenshot of some text rendered witht the sample program](/doc/images/screenshot-01.png?raw=true)

Usage
=====

The NanoVG API is modeled loosely on HTML5 canvas API. If you know canvas, you're up to speed with NanoVG in no time.

## Creating drawing context

The drawing context is created using platform specific constructor function. If you're using the OpenGL 2.0 back-end the context is created as follows:
```C
#define NANOVG_GL2_IMPLEMENTATION	// Use GL2 implementation.
#include "nanovg_gl.h"
...
struct NVGcontext* vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
```

The first parameter defines flags for creating the renderer.

- `NVG_ANTIALIAS` means that the renderer adjusts the geometry to include anti-aliasing. If you're using MSAA, you can omit this flags. 
- `NVG_STENCIL_STROKES` means that the render uses better quality rendering for (overlapping) strokes. The quality is mostly visible on wider strokes. If you want speed, you can omit this flag.

Currently there is an OpenGL back-end for NanoVG: [nanovg_gl.h](/src/nanovg_gl.h) for OpenGL 2.0, OpenGL ES 2.0, OpenGL 3.2 core profile and OpenGL ES 3. The implementation can be chosen using a define as in above example. See the header file and examples for further info. 

*NOTE:* The render target you're rendering to must have stencil buffer.

## Drawing shapes with NanoVG

Drawing a simple shape using NanoVG consists of four steps: 1) begin a new shape, 2) define the path to draw, 3) set fill or stroke, 4) and finally fill or stroke the path.

```C
nvgBeginPath(vg);
nvgRect(vg, 100,100, 120,30);
nvgFillColor(vg, nvgRGBA(255,192,0,255));
nvgFill(vg);
```

Calling `nvgBeginPath()` will clear any existing paths and start drawing from blank slate. There are number of number of functions to define the path to draw, such as rectangle, rounded rectangle and ellipse, or you can use the common moveTo, lineTo, bezierTo and arcTo API to compose the paths step by step.

## Understanding Composite Paths

Because of the way the rendering backend is build in NanoVG, drawing a composite path, that is path consisting from multiple paths defining holes and fills, is a bit more involved. NanoVG uses even-odd filling rule and by default the paths are wound in counter clockwise order. Keep that in mind when drawing using the low level draw API. In order to wind one of the predefined shapes as a hole, you should call `nvgPathWinding(vg, NVG_HOLE)`, or `nvgPathWinding(vg, NVG_CW)` _after_ defining the path.

``` C
nvgBeginPath(vg);
nvgRect(vg, 100,100, 120,30);
nvgCircle(vg, 120,120, 5);
nvgPathWinding(vg, NVG_HOLE);	// Mark circle as a hole.
nvgFillColor(vg, nvgRGBA(255,192,0,255));
nvgFill(vg);
```

## Rendering is wrong, what to do?

- make sure you have created NanoVG context using one of the `nvgCreatexxx()` calls
- make sure you have initialised OpenGL with *stencil buffer*
- make sure you have cleared stencil buffer
- make sure all rendering calls happen between `nvgBeginFrame()` and `nvgEndFrame()`
- to enable more checks for OpenGL errors, add `NVG_DEBUG` flag to `nvgCreatexxx()`
- if the problem still persists, please report an issue!

## OpenGL state touched by the backend

The OpenGL back-end touches following states:

When textures are uploaded or updated, the following pixel store is set to defaults: `GL_UNPACK_ALIGNMENT`, `GL_UNPACK_ROW_LENGTH`, `GL_UNPACK_SKIP_PIXELS`, `GL_UNPACK_SKIP_ROWS`. Texture binding is also affected. Texture updates can happen when the user loads images, or when new font glyphs are added. Glyphs are added as needed between calls to  `nvgBeginFrame()` and `nvgEndFrame()`.

The data for the whole frame is buffered and flushed in `nvgEndFrame()`. The following code illustrates the OpenGL state touched by the rendering code:
```C
	glUseProgram(prog);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_SCISSOR_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilMask(0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilFunc(GL_ALWAYS, 0, 0xffffffff);
	glActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_UNIFORM_BUFFER, buf);
	glBindVertexArray(arr);
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniformBlockBinding(... , GLNVG_FRAG_BINDING);
```

## API Reference

See the header file [nanovg.h](/src/nanovg.h) for API reference.

## Ports

- [DX11 port](https://github.com/cmaughan/nanovg) by [Chris Maughan](https://github.com/cmaughan)
- [Metal port](https://github.com/ollix/MetalNanoVG) by [Olli Wang](https://github.com/olliwang)
- [bgfx port](https://github.com/bkaradzic/bgfx/tree/master/examples/20-nanovg) by [Branimir Karadžić](https://github.com/bkaradzic)

## Projects using NanoVG

- [Processing API simulation by vinjn](https://github.com/vinjn/island/blob/master/examples/01-processing/sketch2d.h)
- [NanoVG for .NET, C# P/Invoke binding](https://github.com/sbarisic/nanovg_dotnet)

## License
The library is licensed under [zlib license](LICENSE.txt)
Fonts used in examples:
- Roboto licensed under [Apache license](http://www.apache.org/licenses/LICENSE-2.0)
- Entypo licensed under CC BY-SA 4.0.
- Noto Emoji licensed under [SIL Open Font License, Version 1.1](http://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL)

## Discussions
[NanoVG mailing list](https://groups.google.com/forum/#!forum/nanovg)

## Links
Uses [stb_truetype](http://nothings.org) (or, optionally, [freetype](http://freetype.org)) for font rendering.
Uses [stb_image](http://nothings.org) for image loading.

Nano SVG
==========

## Parser

![screenshot of some splines rendered with the sample program](/doc/images/screenshot-1.png?raw=true)

NanoSVG is a simple stupid single-header-file SVG parse. The output of the parser is a list of cubic bezier shapes.

The library suits well for anything from rendering scalable icons in your editor application to prototyping a game.

NanoSVG supports a wide range of SVG features, but something may be missing, feel free to create a pull request!

The shapes in the SVG images are transformed by the viewBox and converted to specified units.
That is, you should get the same looking data as your designed in your favorite app.

NanoSVG can return the paths in few different units. For example if you want to render an image, you may choose
to get the paths in pixels, or if you are feeding the data into a CNC-cutter, you may want to use millimeters. 

The units passed to NanoSVG should be one of: 'px', 'pt', 'pc' 'mm', 'cm', or 'in'.
DPI (dots-per-inch) controls how the unit conversion is done.

If you don't know or care about the units stuff, "px" and 96 should get you going.

## Rasterizer

![screenshot of tiger.svg rendered with NanoSVG rasterizer](/doc/images/screenshot-2.png?raw=true)

The parser library is accompanied with really simpler SVG rasterizer. Currently it only renders flat filled shapes.

The intended usage for the rasterizer is to for example bake icons of different size into a texture. The rasterizer is not particular fast or accurate, but it's small and packed in one header file.


## Example Usage

``` C
// Load
struct NSVGimage* image;
image = nsvgParseFromFile("test.svg", "px", 96);
printf("size: %f x %f\n", image->width, image->height);
// Use...
for (shape = image->shapes; shape != NULL; shape = shape->next) {
	for (path = shape->paths; path != NULL; path = path->next) {
		for (i = 0; i < path->npts-1; i += 3) {
			float* p = &path->pts[i*2];
			drawCubicBez(p[0],p[1], p[2],p[3], p[4],p[5], p[6],p[7]);
		}
	}
}
// Delete
nsvgDelete(image);
```

## Using NanoSVG in your project

In order to use NanoSVG in your own project, just copy nanosvg.h to your project.
In one C/C++ define `NANOSVG_IMPLEMENTATION` before including the library to expand the NanoSVG implementation in that file.
NanoSVG depends on `stdio.h` ,`string.h` and `math.h`, they should be included where the implementation is expanded before including NanoSVG. 

``` C
#include <stdio.h>
#include <string.h>
#include <math.h>
#define NANOSVG_IMPLEMENTATION	// Expands implementation
#include "nanosvg.h"
```

By default, NanoSVG parses only the most common colors. In order to get support for full list of [SVG color keywords](http://www.w3.org/TR/SVG11/types.html#ColorKeywords), define `NANOSVG_ALL_COLOR_KEYWORDS` before expanding the implementation.

``` C
#include <stdio.h>
#include <string.h>
#include <math.h>
#define NANOSVG_ALL_COLOR_KEYWORDS	// Include full list of color keywords.
#define NANOSVG_IMPLEMENTATION		// Expands implementation
#include "nanosvg.h"
```

# License

The library is licensed under [zlib license](LICENSE.txt)

Blendish OUI
==============

**Blendish** is a small collection of drawing functions for [NanoVG](https://github.com/memononen/nanovg) in a single C header file, designed to replicate the look of the Blender 2.5+ User Interface. You can use these functions to theme your UI library. Some metric constants for faithful reproduction are also included.

To render correctly, Blendish needs both [icon sheet](https://svn.blender.org/svnroot/bf-blender/trunk/blender/release/datafiles/blender_icons16.png) and [font](https://svn.blender.org/svnroot/bf-blender/trunk/blender/release/datafiles/fonts/) from the 
Blender repository. See source code for more information.

![oui_logo.png](/doc/images/4211571908-oui_logo.png)

The repository also hosts **OUI** (short for "Open UI", spoken like the french "oui" for "yes"), a platform agnostic single-header C library for layouting GUI elements and
handling related user input. Together with a set of widget drawing and logic routines it can be used to build complex user interfaces.

Here's a screenshot of Blendish styling a set of layouted OUI items (also contained in example.cpp).

![oui_frozen.png](/doc/images/1655961333-oui_frozen.png)

Here's a shot of all available Blendish theming functions:

![blendish2.png](/doc/images/1457969701-blendish2.png)
