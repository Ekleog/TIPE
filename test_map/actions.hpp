#ifndef TEST_MAP_ACTIONS_HPP_INCLUDED_
#define TEST_MAP_ACTIONS_HPP_INCLUDED_ 0

#include <cmath>
#include <random>

#include "test_map/robot.hpp"

namespace lg { namespace test_map {

class initializer {
   mutable std::uniform_real_distribution<float> dist_;

public:
   initializer(float size)
      : dist_{-size, size}
   { }

   robot operator()() const;
};

class action {
   mutable std::normal_distribution<float> distx_, disty_, distb_;
   float dx_, dy_;
   bool real_;

public:
   action(float dx, float dy, float sigma, bool real)
      : distx_{dx, sigma}, disty_{dy, sigma}, distb_{0, sigma},
        dx_(dx), dy_(dy), real_(real)
   { }

   void operator()(robot &r) const;

   float dx() const {
      return dx_;
   }
   float dy() const {
      return dy_;
   }
};

class measurement {
   float real_, sigma2_;

public:
   measurement(float real, float sigma)
      : real_{real},
        sigma2_{sigma * sigma}
   { }

   float operator()(robot const &r) const;
};

}}

#endif
