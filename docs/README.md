 external libs : kdtree : https://lionel.kr.hs-niederrhein.de/~dalitz/data/kdtree/index.html

 -DBUILD_opencv_python3=OFF
 do not use file(glob in cmake ) not recomended by the community

- note we use all backend computation into Eigen or GLM based 
because it is more optimized than cv::Mat operations on AVX set CPUs
for more information refer to :
https://www.mgaillard.fr/2021/12/29/matrix-vector-product.html

//// https://homepages.inf.ed.ac.uk/rbf/CVonline/LOCAL_COPIES/EPSRC_SSAZ/node3.html


https://www.tensorflow.org/api_docs/cc

extras links :
 https://github.com/onqtam/awesome-cmake
 https://github.com/alyssaq/3Dreconstruction
 https://github.com/chrischoy/3D-R2N2
 https://github.com/ZeLianWen/Image-Registration
 https://github.com/bbrister/SIFT3D

 loguru docs: https://emilk.github.io/loguru/index.html

 for more open source libs cpp :https://en.cppreference.com/w/cpp/links/libs