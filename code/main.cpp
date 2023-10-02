#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

#include "image.hpp"
#include "mesh.hpp"


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

    return 0;
}
