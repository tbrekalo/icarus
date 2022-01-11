#ifndef ICARUS_VECTOR_HPP_
#define ICARUS_VECTOR_HPP_

#include <cstddef>
#include <initializer_list>
#include <iostream>

namespace ic {

class Vec3 {
 public:
  using ValueType = float;

  using PointerType = ValueType*;
  using ConstPointerType = ValueType const*;

  Vec3() = default;

  Vec3(ValueType const val) noexcept;
  Vec3(std::initializer_list<ValueType> const il) noexcept;

  auto x() const noexcept -> ValueType;
  auto y() const noexcept -> ValueType;
  auto z() const noexcept -> ValueType;

  auto begin() noexcept -> PointerType;
  auto end() noexcept -> PointerType;

  auto begin() const noexcept -> ConstPointerType;
  auto end() const noexcept -> ConstPointerType;

  auto operator[](std::size_t const idx) noexcept -> ValueType&;
  auto operator[](std::size_t const idx) const noexcept -> ValueType const&;

  auto operator-() const noexcept -> Vec3;

  [[maybe_unused]] auto operator+=(Vec3 const& rhs) noexcept -> Vec3&;
  [[maybe_unused]] auto operator-=(Vec3 const& rhs) noexcept -> Vec3&;

  [[maybe_unused]] auto operator*=(ValueType const coef) noexcept -> Vec3&;
  [[maybe_unused]] auto operator/=(ValueType const div) noexcept -> Vec3&;

 private:
  ValueType vals_[3U];
};

auto operator+(Vec3 const& lhs, Vec3 const& rhs) noexcept -> Vec3;
auto operator-(Vec3 const& lhs, Vec3 const& rhs) noexcept -> Vec3;

auto operator*(Vec3 const& lhs, Vec3 const& rhs) noexcept -> Vec3;
auto operator*(Vec3 const& lhs, Vec3::ValueType const rhs) noexcept -> Vec3;
auto operator*(Vec3::ValueType const lhs, Vec3 const& rhs) noexcept -> Vec3;
auto operator/(Vec3 const lhs, Vec3::ValueType const rhs) noexcept -> Vec3;

auto DotProduct(Vec3 const& lhs, Vec3 const& rhs) noexcept -> Vec3::ValueType;
auto CrossProduct(Vec3 const& lhs, Vec3 const& rhs) noexcept -> Vec3;

auto Norm(Vec3 const& vec) noexcept -> Vec3::ValueType;
auto UnitVec3(Vec3 const& vec) noexcept -> Vec3;

auto operator<<(std::ostream& ostrm, Vec3 const& vec) noexcept -> std::ostream&;

}  // namespace icarus

#endif /* ICARUS_VECTOR_HPP_ */
