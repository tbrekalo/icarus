#ifndef ICARUS_RAY_HPP_
#define ICARUS_RAY_HPP_

#include "icarus/vector.hpp"

namespace ic {

struct Ray {
  Ray() = default;
  Ray(Vec3 const& origin, Vec3 const dir) noexcept;

  auto At(Vec3::ValueType const t) const noexcept -> Vec3;

  Vec3 origin;
  Vec3 dir;
};

}  // namespace icarus

#endif /* ICARUS_RAY_HPP_ */