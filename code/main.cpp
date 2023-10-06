#include <iostream>

#include "camera.hpp"
#include "image.hpp"
#include "mesh.hpp"
#include "ray.hpp"


/* LINUX
mkdir build
cd build
cmake ..
make
*/

/* WINDOWS
create build dir
open with cmake
generate vs project in build
open and compile with vs
*/

int main(int, char**) {
    std::cout << "Hello World !" << std::endl;

    Camera camera = Camera(Point(), -Vector::X(), 5);
    std::vector<Ray> rays = camera.GetRays(5, 2);

    for (int i = 0; i < rays.size(); i++) {
        std::cout << rays[i] << std::endl;
    }

    return 0;
}
