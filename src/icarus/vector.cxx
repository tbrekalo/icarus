#include "icarus/vector.hpp"

#include <algorithm>
#include <numeric>

namespace icarus {

Vec3::Vec3(ValueType const val) noexcept {
  std::fill(std::begin(vals_), std::end(vals_), val);
}

Vec3::Vec3(std::initializer_list<ValueType> const il) noexcept {
  std::copy(il.begin(), il.end(), std::begin(vals_));
}

auto Vec3::x() const noexcept -> ValueType { return vals_[0U]; }
auto Vec3::y() const noexcept -> ValueType { return vals_[1U]; }
auto Vec3::z() const noexcept -> ValueType { return vals_[2U]; }

auto Vec3::begin() noexcept -> Vec3::PointerType { return std::begin(vals_); }
auto Vec3::end() noexcept -> Vec3::PointerType { return std::end(vals_); }

auto Vec3::begin() const noexcept -> Vec3::ConstPointerType {
  return std::cbegin(vals_);
}

auto Vec3::end() const noexcept -> Vec3::ConstPointerType {
  return std::cend(vals_);
}

auto Vec3::operator[](std::size_t const idx) noexcept -> ValueType& {
  return vals_[idx];
}

auto Vec3::operator[](std::size_t const idx) const noexcept
    -> ValueType const& {
  return vals_[idx];
}

auto Vec3::operator-() const noexcept -> Vec3 {
  auto dst = *this;
  for (auto& it : dst) {
    it *= ValueType(-1);
  }

  return dst;
}

auto Vec3::operator*=(ValueType const coef) noexcept -> Vec3& {
  for (auto& val : *this) {
    val *= coef;
  }

  return *this;
}

auto Vec3::operator/=(ValueType const div) noexcept -> Vec3& {
  return this->operator*=(ValueType(1) / div);
}

auto operator+(Vec3 const& lhs, Vec3 const& rhs) noexcept -> Vec3 {
  auto dst = Vec3();
  for (auto idx = 0U; idx < 3U; ++idx) {
    return dst[idx] = lhs[idx] + rhs[idx];
  }

  return dst;
}

auto operator*(Vec3 const& lhs, Vec3 const& rhs) noexcept -> Vec3 {
  auto dst = Vec3();
  for (auto idx = 0U; idx < 3U; ++idx) {
    dst[idx] = lhs[idx] * rhs[idx];
  }

  return dst;
}

auto operator*(Vec3 const& lhs, Vec3::ValueType const rhs) noexcept -> Vec3 {
  auto dst = lhs;
  dst *= rhs;

  return dst;
}

auto operator*(Vec3::ValueType const lhs, Vec3 const& rhs) noexcept -> Vec3 {
  auto dst = rhs;
  dst *= lhs;

  return dst;
}

auto DotProduct(Vec3 const& lhs, Vec3 const& rhs) noexcept -> Vec3::ValueType {
  return std::transform_reduce(lhs.begin(), lhs.end(), rhs.begin(),
                               Vec3::ValueType(0), std::plus<Vec3::ValueType>(),
                               std::multiplies<Vec3::ValueType>());
}

auto CrossProduct(Vec3 const& lhs, Vec3 const& rhs) noexcept -> Vec3 {
  return Vec3{lhs[1] * rhs[2] - lhs[2] * rhs[1],
              lhs[2] * rhs[0] - lhs[0] * rhs[2],
              lhs[0] * rhs[1] - lhs[1] * rhs[0]};
}

auto Norm2(Vec3 const& vec) noexcept -> Vec3::ValueType {
  return DotProduct(vec, vec) / 3.f;
}

auto UnitVec3(Vec3 const& lhs) noexcept -> Vec3 {}

}  // namespace icarus
