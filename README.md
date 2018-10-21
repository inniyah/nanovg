# Python-NanoVG : A Python bindings of NanoVG #

Provides NanoVG ( https://github.com/memononen/nanovg ) interfaces for python (CPython).

*   Created : 2017-11-26
*   Last modified : 2018-10-20

<img src="https://raw.githubusercontent.com/vaiorabbit/python-nanovg/master/doc/example_py.png" width="500">

## Prerequisites ##

*   OpenGL context provider
	*   ex.) GLUT (PyOpenGL http://pyopengl.sourceforge.net ) or GLFW (Python-GLFW https://github.com/vaiorabbit/python-glfw/ )

## Setup ##

Installation:

    $ pip install git+https://github.com/vaiorabbit/python-nanovg.git

Upgrade:

    $ pip install -U git+https://github.com/vaiorabbit/python-nanovg.git

Uninstallation:

    $ pip uninstall NanoVG

## Usage ##

1. Build NanoVG shared library
	*   See nanovg_dll

2. Import NanoVG in your script.
	*   ex.) import NanoVG

3. Load shared library
	*   ex.) NanoVG.load_nanovg_library('libnanovg_gl2.dylib', render_backend='gl2')
	*   ex.) NanoVG.load_nanovg_library('libnanovg_gl3.dylib', render_backend='gl3')

4. Setup OpenGL
	*   nvgSetupGL2() / nvgSetupGL3()

See demo/example.py ( https://github.com/vaiorabbit/python-nanovg/blob/master/demo/example.py ) for details ($ python example.py).


## License ##

All source codes are available under the terms of the zlib/libpng license.

	Python-NanoVG : A Python bindings of NanoVG
	Copyright (c) 2017-2018 vaiorabbit
	
	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.
	
	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:
	
	    1. The origin of this software must not be misrepresented; you must not
	    claim that you wrote the original software. If you use this software
	    in a product, an acknowledgment in the product documentation would be
	    appreciated but is not required.
	
	    2. Altered source versions must be plainly marked as such, and must not be
	    misrepresented as being the original software.
	
	    3. This notice may not be removed or altered from any source
	    distribution.
