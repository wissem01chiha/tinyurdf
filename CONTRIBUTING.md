Contribution Guidelines
----

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