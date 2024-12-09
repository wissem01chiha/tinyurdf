TinyURDF
=========

A modern, flexible C++17 library for parsing/writing URDF-based files, converting to [JSON](https://www.json.org/example.html), [YAML](https://en.wikipedia.org/wiki/YAML), and Prototext schema, with support 3D visualization using [VTK](https://vtk.org/).

TinyURDF do not depend on ROS. However the core of this project was inspired and refactored from the ROS [urdfdom](https://github.com/ros/urdfdom) and [urdfdom_headers](https://github.com/ros/urdfdom_headers) packages. 


Features
--------

- **Multibody Representation**: allows the representation of complex serial and parallel mechanisms with multibody systems, as well as multiaxial joints.

- **Multibody Graph-Based Structures**: supports complex multibody graph-based structures, where each joint can have multiple parent links and each link can have only one child or parent link. This enables the representation of parallel-composed models in robotics and biomechanics.

- **Data Export**: facilitates exporting this representation to common human-readable data formats, such as JSON and YAML.

- **Platform-Neutral Serialization**: uses [Protocol Buffers](https://protobuf.dev/), for serializing structured data, to achive efficient and compact data storage.

- **Ease of Integration**: designed to be cross-compiled, making it easy to integrate and install across various platforms.

### Dependencies
--------

The library currently depends on the following C++ projects:


  - **[TinyXML2](https://github.com/leethomason/tinyxml2)**
  - **[loguru](https://github.com/emilk/loguru)** 
  - **[Eigen](https://eigen.tuxfamily.org)**
  - **[nlohmann-json](https://github.com/nlohmann/json)**
  - **[googletest](https://github.com/google/googletest)** (optional)

### Build  
--------

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
The work is in progress, and any contributions to the project are welcome. See the following guidelines for areas where help is needed:

#### Current Tasks:

- [ ] Integrate [yaml-cpp](https://github.com/jbeder/yaml-cpp) dependency through an external CMake module
- [ ] Complete the development of core modules: [sensor](/include/tinyurdf/sensor.h), [world](/include/tinyurdf/world.h), [Twist](include/tinyurdf/twist.h), [link](include/tinyurdf/link.h), [model](include/tinyurdf/model.h), [model_interface](/include/tinyurdf/model_interface.h)
- [ ] Complete the development of exporter modules: [link_exporter](include/tinyurdf/link_exporter.h), [joint_exporter](include/tinyurdf/joint_exporter.h)
- [ ] Integrate VTK using an external CMake module, assuming VTK installation is done separately.
- [ ] Implement the URDF render engine interface: [urdf_render_vtk](include/tinyurdf/urdf_render_vtk.h)
- [ ] Add protobuf support compilation tag into CMake, as a CMake option
- [ ] Add [Collada](https://en.wikipedia.org/wiki/COLLADA) file support through [collada-dom](https://github.com/rdiankov/collada-dom) library
- [ ] Add common material/colors default parameters, for default use-verification, in prototext files.
- [ ] Complete test implementation in the [test](test/) folder.
- [ ] Add graph computation functions through [CXXGraph](https://github.com/ZigRazor/CXXGraph)
- [ ] Add inertial, volume, collision computation utility functions

#### Additional Features:
- [ ] Add custom project logo.
- [ ] Finalize documentation using [Doxygen](), in the [docs](/docs/) folder.

Feel free to [mail](mailto:chihawissem08@gmail.com) me.

  
Examples  
------------  
Examples of scripts are implemented in the [examples](/examples/) folder.  
Examples of URDF/SRDF files can be found at [awesome-urdf](https://github.com/ami-iit/awesome-urdf).


Contributors
------------
<a href="https://github.com/wissem01chiha/tinyurdf/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=wissem01chiha/tinyurdf" />
</a>

License
------------
see [LICENSE](/LICENSE) file.
