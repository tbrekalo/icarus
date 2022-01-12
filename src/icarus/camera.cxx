#include "icarus/camera.hpp"

namespace ic {

Camera::Camera(Vec3 const position, Vec3 const target) noexcept
    : position_(position), direction_(target - position) {}

auto Camera::Render(std::span<std::unique_ptr<Hittable>> hittables,
                    ImageDims const img_dims) const -> PpmImage {
  auto dst = decltype(PpmImage::rgb_pixels)();
  dst.reserve(img_dims.height * img_dims.width);

  auto const kAspectRation =
      static_cast<Vec3::ValueType>(img_dims.width) / img_dims.height;

  auto const kViewportHeight = 2.0;
  auto const kViewportWidth = kViewportHeight * kAspectRation;

  auto const kVerticalAxis = Vec3{0.0, kViewportHeight, 0.0};
  auto const kHorizontalAxis = Vec3{kViewportWidth, 0.0, 0.0};

  auto const kLowerLeft = position_ - (kHorizontalAxis / 2.0) -
                          (kVerticalAxis / 2.0) - Vec3{0.0, 0.0, 1.0};

  auto const color_ray = [&](Ray const& ray) noexcept -> ic::Vec3 {
    for (auto const& it : hittables) {
      auto const hit = it->CheckHit(ray);
      if (hit) {
        return ic::Vec3{1.0, 0.0, 0.0};
      }
    }

    auto const kRayUnitDir = UnitVec3(ray.dir);
    auto const kT = 0.5 * (kRayUnitDir.y() + 1.0f);

    return (1.f - kT) * Vec3(1.0) + kT * Vec3{0.5, 0.7, 1.0};
  };

  for (auto h = 0U; h < img_dims.height; ++h) {
    for (auto v = 0U; v < img_dims.width; ++v) {
      auto const kHorizontalCoef =
          static_cast<Vec3::ValueType>(v) / (img_dims.width - 1U);
      auto const kVerticalCoef =
          static_cast<Vec3::ValueType>(img_dims.height - 1U - h) /
          (img_dims.height - 1U);

      dst.emplace_back(color_ray(
          Ray(position_, kLowerLeft + (kVerticalCoef * kVerticalAxis) +
                             (kHorizontalCoef * kHorizontalAxis) - position_)));
    }
  }

  return PpmImage{.dims = img_dims, .rgb_pixels = std::move(dst)};
}

}  // namespace ic
