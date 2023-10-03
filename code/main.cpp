#include <iostream>

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

    Image img = Image("data/bucketHat.png");
    img = img.GetGrayVersion();
    img.Save("data/test.png");

    Ray ray = Ray(Point(), Vector(1, 0, 0));
    std::cout << ray(0.5) << std::endl;

    return 0;
}
