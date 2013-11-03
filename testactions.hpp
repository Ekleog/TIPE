#ifndef TESTACTIONS_HPP_INCLUDED_
#define TESTACTIONS_HPP_INCLUDED_ 0

#include <cmath>
#include <random>

#include "testrobot.hpp"

namespace lg { namespace test {

class initializer {
   mutable std::uniform_real_distribution<float> dist_;

public:
   initializer(float size)
      : dist_{-size, size}
   { }

   robot operator()() const;
};

class action {
   mutable std::normal_distribution<float> distx_, disty_;

public:
   action(float dx, float dy, float sigma)
      : distx_{dx, sigma}, disty_{dy, sigma}
   { }

   void operator()(robot &r) const;
};

class measurement {
   float real_, sigma2_;

public:
   measurement(float realx, float realy, float sigma)
      : real_{std::sqrt(realx * realx + realy * realy)},
        sigma2_{sigma * sigma}
   { }

   float operator()(robot const &r) const;
};

}}

#endif
