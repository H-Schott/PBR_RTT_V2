#include <iostream>
#include <chrono>

#include "bvh.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "mesh.hpp"
#include "ray.hpp"
#include "rt_scene.hpp"
#include "terrain.hpp"


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
    int height = 640;
    /*int width = 512;
    int height = 320;*/


    // Scene
    Terrain t = Terrain("data/dem_1024.png");
    t.Scale(0.3);
    Mesh mesh = t.GetMesh();
    RT_Scene scene = RT_Scene(mesh);
    //RT_Scene scene = RT_Scene("data/spot.obj");
    std::cout << "start BVH" << std::endl;
    BVH bvh = BVH(scene);
    std::cout << "end BVH" << std::endl;

    // Camera
    Camera camera = Camera(Point(5., 0., 2.5), Normalize(Vector(-1., 0., -0.5)), 1.8);
    std::vector<Ray> rays = camera.GetRays(width, height);

    // Light
    Point light_pos = camera.center;


    
    Image img = Image(width, height);

    auto start_time = std::chrono::system_clock::now();
#pragma omp parallel for
    for (int i = 0; i < rays.size(); i++) {
        //Hit hit = scene.Intersection(rays[i]);
        Hit hit = bvh.Intersection(rays[i]);
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
    std::cout << "execution time : " << elapsed_seconds.count() << " seconds." << std::endl;

    img.Save("data/rt_test.png");

    return 0;
}
