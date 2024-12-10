TinyURDF
=========

A modern, flexible C++17 library for parsing/writing URDF-based files, converting to [JSON](https://www.json.org/example.html), [YAML](https://en.wikipedia.org/wiki/YAML), and Prototext schema, with support 3D visualization using [VTK](https://vtk.org/).

TinyURDF do not depend on ROS. However the core of this project was inspired and refactored from the ROS [urdfdom](https://github.com/ros/urdfdom) and [urdfdom_headers](https://github.com/ros/urdfdom_headers) packages. 


Features
--------

- multibody representation : allows the representation of complex serial and parallel mechanisms with multibody systems, as well as multiaxial joints.
- multibody graph-based structures : supports complex multibody graph-based structures, where each joint can have multiple parent links and each link can have only one child or parent link. This enables the representation of parallel-composed models in robotics and biomechanics.
- data export: facilitates exporting this representation to common human-readable data formats, such as JSON and YAML.
- platform-neutral serialization: uses [Protocol Buffers](https://protobuf.dev/), for serializing structured data, to achive efficient and compact data storage.
- ease of integration : designed to be cross-compiled, making it easy to integrate and install across various platforms.

Documentation
--------


Recent Releases
--------


Dependencies
--------

The library currently depends on the following C++ projects:


  - **[TinyXML2](https://github.com/leethomason/tinyxml2)**
  - **[loguru](https://github.com/emilk/loguru)** 
  - **[Eigen](https://eigen.tuxfamily.org)**
  - **[nlohmann-json](https://github.com/nlohmann/json)**
  - **[googletest](https://github.com/google/googletest)** (optional)

Build  
------------

```bash
git clone https://github.com/wissem01chiha/tinyurdf

mkdir build && cd build
cmake -G "Unix Makefiles" ..
make
```
> [!WARNING]   
> Builds successfully on Windows 11 with CMake 3.22.1, GCC 11.2.0, and GNU Make 4.4.1. Other platforms or generators have not been tested.


Contribution
------------
see [CONTRIBUTING](CONTRIBUTING.md) file for more information

  
Examples  
------------  
Examples of scripts are implemented in the [examples](/examples) folder, samples of .urdf files can be found at [awesome-urdf](https://github.com/ami-iit/awesome-urdf).


Contributors
------------
<a href="https://github.com/wissem01chiha/tinyurdf/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=wissem01chiha/tinyurdf" />
</a>

License
------------
see [LICENSE](/LICENSE) file.
