#ifndef COMMON_HPP
#define COMMON_HPP

#include <boost/multiprecision/cpp_bin_float.hpp>

namespace ccalc
{
    namespace mp = boost::multiprecision;
    using Float = mp::number<mp::cpp_bin_float<128>>;
} // namespace ccalc

#endif // !COMMON_HPP