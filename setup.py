from setuptools import find_packages, setup
from NanoVG import __author__, __version__, __license__

setup(
    name = 'NanoVG',
    version = __version__,
    description = 'A Python bindings of NanoVG',
    license = __license__,
    author = __author__,
    author_email = 'vaiorabbit@gmail.com',
    url = 'https://github.com/vaiorabbit/python-nanovg',
    packages = find_packages(),
)
