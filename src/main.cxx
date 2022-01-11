#include <cmath>
#include <cstdlib>
#include <iostream>

#include "icarus/ray.hpp"
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

  constexpr auto kViewportHeight = 2.f;
  constexpr auto kViewportWidth = kViewportHeight * kAspectRation;

  constexpr auto kFocalLength = 1.f;

  auto const kOrigin = ic::Vec3(0.f);
  auto const kHorizontalAxis = ic::Vec3{kViewportWidth, 0.f, 0.f};
  auto const kVerticalAxis = ic::Vec3{0.f, kViewportHeight, 0.f};

  auto const kLowerLeft = kOrigin - (kHorizontalAxis / 2) -
                          (kVerticalAxis / 2) -
                          ic::Vec3{0.f, 0.f, kFocalLength};

  std::cout << "P3\n" << kImageWidth << ' ' << kImageHeight << "\n255\n";
  for (auto y = kImageHeight - 1; y >= 0; --y) {
    for (auto x = 0; x < kImageWidth; ++x) {
      auto const kYDir = static_cast<ic::Vec3::ValueType>(y) / kImageHeight;
      auto const kXDir = static_cast<ic::Vec3::ValueType>(x) / kImageWidth;
      auto const kRay =
          ic::Ray(kOrigin, kLowerLeft + (kYDir * kVerticalAxis) +
                               (kXDir * kHorizontalAxis) - kOrigin);

      WriteColor(std::cout, RayColor(kRay));
    }
  }

  return EXIT_SUCCESS;
}
