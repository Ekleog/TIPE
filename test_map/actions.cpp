#include "test_map/actions.hpp"

namespace lg { namespace test_map {

static std::mt19937 rng{std::random_device()()};

robot initializer::operator()() const {
   return robot{0.f, 0.f, dist_(rng), dist_(rng)};
}

void action::operator()(robot &r) const {
   r.move(distx_(rng), disty_(rng));
   if (!real_) {
      r.move_beacon(distb_(rng), distb_(rng));
   }
}

float measurement::operator()(robot const &r) const {
   float measure = r.sense();
   return std::exp(10.f - (real_ - measure) * (real_ - measure) / (2.f * sigma2_));
}

}}
