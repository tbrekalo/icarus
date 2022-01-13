#include "icarus/camera.hpp"

#include <random>

namespace ic {

namespace detail {

template <class RngGen>
auto PathTrace(std::span<HittableProxy> const& world, Ray const ray,
               std::uint32_t depth, RngGen&& rng_gen) -> Vec3 {
  if (depth == 0) {
    return Vec3(0);
  } else {
    for (auto const& it : world) {
      if (auto const hit =
              it(ray, RayHitBounds{
                          .lower_bound = 0.001,
                          .upper_bound = std::numeric_limits<double>::max(),
                      })) {
        auto in_unit_sphere = RngVec(0.0, 1.0, rng_gen);
        while (DotProduct(in_unit_sphere, in_unit_sphere) > 1.0) {
          in_unit_sphere = RngVec(0.0, 1.0, rng_gen);
        }

        if (DotProduct(in_unit_sphere, hit->normal) < 0) {
          in_unit_sphere *= -1.0;
        }

        auto target = hit->point + hit->normal + UnitVec3(in_unit_sphere);
        return 0.5 *
               PathTrace(world,
                         Ray{.origin = hit->point, .dir = target - hit->point},
                         depth - 1U, rng_gen);

        return Vec3{1.0, 0.0};
      }
    }
  }

  auto rng_dir = UnitVec3(ray.dir);
  auto t = 0.5 * (rng_dir.y() + 1.0);
  return (1.0 - t) * Vec3(1.0) + t * Vec3{0.5, 0.7, 1.0};
}

}  // namespace detail

Camera::Camera(Vec3 const position, Vec3 const target) noexcept
    : position_(position), direction_(target - position) {}

auto Camera::Render(std::span<HittableProxy> hittables,
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

  auto rng_gen = std::mt19937();
  auto real_distr = std::uniform_real_distribution<>(-1.0, 1.0);

  auto const sample_area = [&](std::uint32_t const x, std::uint32_t const y,
                               std::uint32_t const n) -> Vec3 {
    auto dst = Vec3(0);
    for (auto nth_sample = 0U; nth_sample < n; ++nth_sample) {
      auto const xx = x + real_distr(rng_gen);
      auto const yy = y + real_distr(rng_gen);

      auto const kHorizontalCoef = xx / (img_dims.width - 1U);
      auto const kVerticalCoef = yy / (img_dims.height - 1U);

      dst += detail::PathTrace(
          hittables,
          Ray{.origin = position_,
              .dir = kLowerLeft + (kVerticalCoef * kVerticalAxis) +
                     (kHorizontalCoef * kHorizontalAxis) - position_},
          10U, rng_gen);
    }

    return dst / n;
  };

  for (auto h = 0U; h < img_dims.height; ++h) {
    for (auto v = 0U; v < img_dims.width; ++v) {
      dst.emplace_back(sample_area(v, (img_dims.height - 1U - h), 16));
    }
  }

  return PpmImage{.dims = img_dims, .rgb_pixels = std::move(dst)};
}

}  // namespace ic
