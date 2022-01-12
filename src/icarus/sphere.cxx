#include "icarus/sphere.hpp"

#include <cmath>

#include <iostream>

namespace ic {

Sphere::Sphere(Vec3 const center, Vec3::ValueType const radius)
    : center_(center), radius_(radius) {}

auto Sphere::CheckHit(Ray const& ray) const noexcept
    -> std::optional<HitRecord> {
  auto const oc = ray.origin - center_;
  auto const a = DotProduct(ray.dir, ray.dir);
  auto const h = DotProduct(oc, ray.dir);
  auto const c = DotProduct(oc, oc) - radius_ * radius_;

  auto const determinant = h * h - a * c;
  if (determinant >= 0) {
    auto const t = (-h - std::sqrt(determinant)) / a;
    if (t > 0) {
      return HitRecord{.t = t};
    }
  }

  return std::nullopt;
}

auto Sphere::Center() const noexcept -> Vec3 { return center_; }

auto Sphere::Radius() const noexcept -> Vec3::ValueType { return radius_; }

}  // namespace ic
