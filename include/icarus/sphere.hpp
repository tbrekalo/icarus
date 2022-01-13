#ifndef ICARUS_SPHERE_HPP_
#define ICARUS_SPHERE_HPP_

#include "icarus/hit.hpp"

namespace ic {

class Sphere : public Hittable {
 public:
  Sphere(Vec3 const center, Vec3::ValueType const radius);

  [[nodiscard]] auto CheckHit(Ray const& ray,
                              RayHitBounds const bounds) const noexcept
      -> std::optional<HitRecord> override;

  auto Center() const noexcept -> Vec3;
  auto Radius() const noexcept -> Vec3::ValueType;

  ~Sphere() = default;

 private:
  Vec3 center_;
  Vec3::ValueType radius_;
};

}  // namespace ic

#endif /* ICARUS_SPHERE_HPP_ */
