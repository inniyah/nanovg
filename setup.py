from setuptools import find_packages, setup
from GLFW import __author__, __version__, __license__

setup(
    name = 'GLFW',
    version = __version__,
    description = 'Yet another GLFW wrapper for Python',
    license = __license__,
    author = __author__,
    author_email = 'vaiorabbit@gmail.com',
    url = 'https://github.com/vaiorabbit/python-glfw',
    packages = find_packages(),
)
