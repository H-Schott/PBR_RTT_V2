#include <iostream>
#include <chrono>

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

    int width = 512;
    int height = 512;

    /*std::vector<Point> pts = {Point(0., -1., 0.), Point(0., 1., 0.), Point(0., 0., 1.)};
    std::vector<unsigned int> indices = { 0, 1, 2 };
    std::vector<Texture> t;
    Mesh mesh = Mesh(pts, indices, t);
    RT_Scene scene = RT_Scene(mesh);*/

    RT_Scene scene = RT_Scene("data/spot.obj");

    Camera camera = Camera(Point(10., 0., 0.), -Vector::X(), 3);
    std::vector<Ray> rays = camera.GetRays(width, height);

    Image img = Image(width, height);

    Point light_pos = camera.center;

    auto start_time = std::chrono::system_clock::now();
#pragma omp parallel for
    for (int i = 0; i < rays.size(); i++) {
        //std::cout << rays[i] << " : " << scene.IntersectionTriangle(0, rays[i]) << std::endl;
        Hit hit = scene.Intersection(rays[i]);
        //std::cout << hit.triangle_id << std::endl;
        if (hit) {

            // diffuse
            Vector normal = scene.triangles[hit.triangle_id].Normal();
            Vector light_dir = Normalize(light_pos - rays[i](hit.t));
            double diffuse_coeff = std::max(Dot(normal, light_dir), 0.);

            img.pixels[i] = diffuse_coeff * Color::White();
        }
    }

    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds{ end_time - start_time };
    std::cout << elapsed_seconds.count() << std::endl;;

    img.Save("data/rt_test.png");

    return 0;
}
