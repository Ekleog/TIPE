#include "testactions.hpp"

namespace lg { namespace test {

static std::mt19937 rng{std::random_device()()};

robot initializer::operator()() const {
   return robot{dist_(rng), dist_(rng)};
}

void action::operator()(robot &r) const {
   r.move(distx_(rng), disty_(rng));
}

float measurement::operator()(robot const &r) const {
   float measure = std::sqrt(r.x() * r.x() + r.y() * r.y());
   return std::exp(- (real_ - measure) * (real_ - measure) / (2.f * sigma2_));
}

}}
