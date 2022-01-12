#include "icarus/image.hpp"

#include <cmath>

namespace ic {

namespace detail {

[[maybe_unused]] auto WriteColor(std::ostream& ostrm, Vec3 const& color)
    -> std::ostream& {
  ostrm << static_cast<std::uint32_t>(std::ceil(255 * color[0])) << ' ';
  ostrm << static_cast<std::uint32_t>(std::ceil(255 * color[1])) << ' ';
  ostrm << static_cast<std::uint32_t>(std::ceil(255 * color[2])) << '\n';

  return ostrm;
}

}  // namespace detail

auto operator<<(std::ostream& ostrm, PpmImage const& img) -> std::ostream& {
  ostrm << "P3\n" << img.dims.width << ' ' << img.dims.height << "\n255\n";
  for (auto const& it : img.rgb_pixels) {
    detail::WriteColor(ostrm, it);
  }

  return ostrm;
}

}  // namespace ic
