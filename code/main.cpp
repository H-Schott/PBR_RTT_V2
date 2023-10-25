#include <iostream>
#include <chrono>

#include "bvh.hpp"
#include "camera.hpp"
#include "image.hpp"
#include "mesh.hpp"
#include "ray.hpp"
#include "rt_scene.hpp"
#include "sampler.hpp"
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


    int width = 1024 / 2;
    int height = 640 / 2;
    /*int width = 512;
    int height = 320;*/


    // Scene
    Terrain t = Terrain("data/dem_256.png");
    t.Scale(0.3);
    Mesh mesh = t.GetMesh();
    RT_Scene scene = RT_Scene(mesh);

    // BVH
    auto bvh_start_time = std::chrono::system_clock::now();
    BVH bvh = BVH(scene);
    auto bvh_end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> bvh_elapsed_seconds{ bvh_end_time - bvh_start_time };
    std::cout << "BVH creation time : " << bvh_elapsed_seconds.count() << " seconds." << std::endl;

    // Camera
    Camera camera = Camera(Point(5., 0., 2.5), Normalize(Vector(-1., 0., -0.5)), 1.8);
    std::vector<Ray> rays = camera.GetRays(width, height);

    // Light
    Point light_pos = camera.center;


    
    Image img = Image(width, height);
    
    auto start_time = std::chrono::system_clock::now();
#pragma omp parallel for
    for (int i = 0; i < rays.size(); i++) {
        Hit hit = bvh.Intersection(rays[i]);
        if (hit) {

            // diffuse
            //Vector normal = scene.triangles[hit.triangle_id].Normal();
            Point p_hit = rays[i](hit.t);
            Vector normal = scene.InterpolateNormal(hit);
            Vector light_dir = Normalize(light_pos - rays[i](hit.t));
            double diffuse_coeff = std::max(Dot(normal, light_dir), 0.);

            //img.pixels[i] = diffuse_coeff * Color::White();
            
            // AO
            NormalSampler sampler = NormalSampler(rand()%2000000);
            double ao = 0.;
            int ao_samples = 16;
            for (int i = 0; i < ao_samples; i++) {
                Vector rand_dir = Normalize(Vector(sampler(), sampler(), sampler()));
                if (Dot(rand_dir, normal) < 0) rand_dir = -rand_dir;
                Ray ao_ray = Ray(p_hit + 1e-5 * normal, rand_dir);
                Hit ao_hit = bvh.Intersection(ao_ray);
                if (ao_hit) ao++;
            }
            ao /= ao_samples;
            img.pixels[i] = (1. - ao) * Color::White();
        }
    }

    auto end_time = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds{ end_time - start_time };
    std::cout << "execution time : " << elapsed_seconds.count() << " seconds." << std::endl;

    img.Save("data/rt_test.png");

    return 0;
}
