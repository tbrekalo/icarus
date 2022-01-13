#ifndef ICARUS_HIT_HPP_
#define ICARUS_HIT_HPP_

#include <memory>
#include <optional>
#include <type_traits>

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

template <class Fn, class T>
using IsCheckHit = std::is_invocable_r<std::optional<HitRecord>, Fn, T const&,
                                       Ray const&, RayHitBounds const&>;

template <class Fn, class T>
constexpr auto IsCheckHitV = IsCheckHit<Fn, T>::value;

class HittableProxy {
  using RedirectSig = std::optional<HitRecord>(void*, Ray const&,
                                               RayHitBounds const&);
  using RedirectSigPtr = std::add_pointer_t<RedirectSig>;

 public:
  template <class T, std::enable_if_t<std::is_pointer_v<T>, std::uint8_t> = 0U>
  HittableProxy(T&& t)
      : impl_([](void* repr, Ray const& ray,
                 RayHitBounds const& bounds) -> std::optional<HitRecord> {
          return CheckHit(*static_cast<T>(repr), ray, bounds);
        }),
        obj_ptr_(t) {}

  [[nodiscard]] auto operator()(Ray const& ray,
                                RayHitBounds const& bounds) const noexcept {
    return impl_(obj_ptr_, ray, bounds);
  }

 private:
  RedirectSigPtr impl_;
  void* obj_ptr_;
};

};  // namespace ic

#endif /* ICARUS_HIT_HPP_ */
