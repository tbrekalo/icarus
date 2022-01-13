#ifndef ICARUS_HIT_HPP_
#define ICARUS_HIT_HPP_

#include <optional>

#include "icarus/ray.hpp"
#include "icarus/vector.hpp"

namespace ic {

enum class SurfaceFace : std::uint8_t { kBack, kFront };

struct HitRecord {
  Vec3::ValueType t;
  Vec3 point;
  Vec3 normal;

  SurfaceFace face;
};

class Hittable {
 public:
  [[nodiscard]] auto virtual CheckHit(Ray const& ray, RayHitBounds const bounds) const noexcept
      -> std::optional<HitRecord> = 0;

  virtual ~Hittable() = default;
};

};  // namespace ic

#endif /* ICARUS_HIT_HPP_ */
