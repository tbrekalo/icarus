#include "icarus/ray.hpp"

namespace ic {

Ray::Ray(Vec3 const& origin, Vec3 const dir) noexcept
    : origin(origin), dir(dir) {}

auto Ray::At(Vec3::ValueType const t) const noexcept -> Vec3 {
  return origin + t * dir;
}

}  // namespace icarus
