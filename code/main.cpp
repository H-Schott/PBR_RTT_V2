#include <iostream>

#include "camera.hpp"
#include "image.hpp"
#include "mesh.hpp"
#include "ray.hpp"
#include "rt_scene.hpp"


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

    int width = 1024;
    int height = 1024;

    /*std::vector<Point> pts = {Point(0., -1., 0.), Point(0., 1., 0.), Point(0., 0., 1.)};
    std::vector<unsigned int> indices = { 0, 1, 2 };
    std::vector<Texture> t;
    Mesh mesh = Mesh(pts, indices, t);
    RT_Scene scene = RT_Scene(mesh);*/

    RT_Scene scene = RT_Scene("data/spot.obj");

    Camera camera = Camera(Point(10., 0., 0.), -Vector::X(), 3);
    std::vector<Ray> rays = camera.GetRays(width, height);

    Image img = Image(width, height);

#pragma omp parallel for
    for (int i = 0; i < rays.size(); i++) {
        //std::cout << rays[i] << " : " << scene.IntersectionTriangle(0, rays[i]) << std::endl;
        if (scene.Intersection(rays[i])) {
            img.pixels[i] = Color::White();
        }
    }

    img.Save("data/rt_test.png");

    return 0;
}
