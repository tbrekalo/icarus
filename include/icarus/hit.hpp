#ifndef ICARUS_HIT_HPP_
#define ICARUS_HIT_HPP_

#include <optional>

#include "icarus/ray.hpp"
#include "icarus/vector.hpp"

namespace ic {

struct HitRecord {
  Vec3::ValueType t;
};

class Hittable {
 public:
  [[nodiscard]] auto virtual CheckHit(Ray const& ray) const noexcept
      -> std::optional<HitRecord> = 0;

  virtual ~Hittable() = default;
};

};  // namespace ic

#endif /* ICARUS_HIT_HPP_ */
