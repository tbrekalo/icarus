#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <optional>

#include "icarus/camera.hpp"
#include "icarus/hit.hpp"
#include "icarus/image.hpp"
#include "icarus/ray.hpp"
#include "icarus/sphere.hpp"
#include "icarus/vector.hpp"

[[maybe_unused]] auto WriteColor(std::ostream& os, ic::Vec3 const& color)
    -> std::ostream& {
  os << static_cast<std::uint32_t>(std::ceil(255 * color[0])) << ' ';
  os << static_cast<std::uint32_t>(std::ceil(255 * color[1])) << ' ';
  os << static_cast<std::uint32_t>(std::ceil(255 * color[2])) << '\n';

  return os;
}

auto RayColor(ic::Ray const& ray) noexcept -> ic::Vec3 {
  auto const kRayUnitDir = ic::UnitVec3(ray.dir);
  auto const kT =
      0.5f * (kRayUnitDir.y() + 1.f);  // shift because of negative values

  return (1.f - kT) * ic::Vec3(1.f) + kT * ic::Vec3{0.5f, 0.7f, 1.f};
}

int main(void) {
  constexpr auto kAspectRation = 16.f / 9.f;

  constexpr auto kImageHeight = 720;
  constexpr auto kImageWidth =
      static_cast<std::int32_t>(kAspectRation * kImageHeight);

  auto hittables = std::vector<std::unique_ptr<ic::Hittable>>();
  hittables.emplace_back(
      std::make_unique<ic::Sphere>(ic::Vec3{0.0, 0.0, -1.0}, 0.5));
  hittables.emplace_back(
      std::make_unique<ic::Sphere>(ic::Vec3{0.0, -100.5, -1.0}, 100.0));

  auto const kImgDims =
      ic::ImageDims{.width = kImageWidth, .height = kImageHeight};
  auto const camera = ic::Camera(ic::Vec3(0.0), ic::Vec3{0.0, 0.0, -1.0});

  std::cout << camera.Render(hittables, kImgDims);

  return EXIT_SUCCESS;
}
