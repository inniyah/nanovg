**Blendish** is a small collection of drawing functions for [NanoVG](https://github.com/memononen/nanovg) in a single C header file, designed to replicate the look of the Blender 2.5+ User Interface. You can use these functions to theme your UI library. Some metric constants for faithful reproduction are also included.

To render correctly, Blendish needs both [icon sheet](https://svn.blender.org/svnroot/bf-blender/trunk/blender/release/datafiles/blender_icons16.png) and [font](https://svn.blender.org/svnroot/bf-blender/trunk/blender/release/datafiles/fonts/) from the
Blender repository. See source code for more information.

![oui_logo.png](images/oui_logo.png)

The repository also hosts **OUI** (short for "Open UI", spoken like the french "oui" for "yes"), a platform agnostic single-header C library for layouting GUI elements and
handling related user input. Together with a set of widget drawing and logic routines it can be used to build complex user interfaces.

Here's a screenshot of Blendish styling a set of layouted OUI items (also contained in example.cpp).

![oui_frozen.png](images/oui_frozen.png)

Here's a shot of all available Blendish theming functions:

![blendish2.png](images/blendish2.png)
