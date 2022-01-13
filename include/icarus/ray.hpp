#ifndef ICARUS_RAY_HPP_
#define ICARUS_RAY_HPP_

#include <limits>

#include "icarus/vector.hpp"

namespace ic {

struct Ray {
  Ray() = default;
  Ray(Vec3 const& origin, Vec3 const dir) noexcept;

  auto At(Vec3::ValueType const t) const noexcept -> Vec3;

  Vec3 origin;
  Vec3 dir;
};

struct RayHitBounds {
  Vec3::ValueType lower_bound = 0.0;
  Vec3::ValueType upper_bound = std::numeric_limits<Vec3::ValueType>::max();
};

}  // namespace ic

#endif /* ICARUS_RAY_HPP_ */
