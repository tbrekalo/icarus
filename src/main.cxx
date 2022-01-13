#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>

#include "icarus/camera.hpp"
#include "icarus/hit.hpp"
#include "icarus/image.hpp"
#include "icarus/ray.hpp"
#include "icarus/sphere.hpp"
#include "icarus/vector.hpp"

int main(void) {
  constexpr auto kAspectRation = 16.f / 9.f;

  constexpr auto kImageHeight = 720;
  constexpr auto kImageWidth =
      static_cast<std::int32_t>(kAspectRation * kImageHeight);

  auto spheres = std::vector<ic::Sphere>{
      ic::Sphere{.center = ic::Vec3{0.0, 0.0, -1.0}, .radius = 0.5},
      ic::Sphere{.center = ic::Vec3{0.0, -100.5, -1.0}, .radius = 100}};

  auto proxies = std::vector<ic::HittableProxy>();

  proxies.reserve(spheres.size());
  std::generate_n(std::back_inserter(proxies), spheres.size(),
                  [ptr = spheres.data()]() mutable -> ic::HittableProxy {
                    return ic::HittableProxy(ptr++);
                  });

  auto const kImgDims =
      ic::ImageDims{.width = kImageWidth, .height = kImageHeight};
  auto const camera = ic::Camera(ic::Vec3(0.0), ic::Vec3{0.0, 0.0, -1.0});

  std::cout << camera.Render(proxies, kImgDims);

  return EXIT_SUCCESS;
}
