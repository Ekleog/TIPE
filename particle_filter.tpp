#include "particle_filter.hpp"

#include <algorithm>

namespace lg {

using std::size_t;

#define LG_PFT \
   template <class P, class I, class A, class M>

#define LG_PF \
   particle_filter<P, I, A, M>

LG_PFT
LG_PF::particle_filter(
      uint32_t particle_number,
      initializer_type const &initial
)
      : particles_{}, rng_{std::random_device{}()} {
   particles_.reserve(particle_number);

   while (particle_number-- > 0) {
      particles_.push_back(initial());
   }
}

LG_PFT
void LG_PF::action(LG_PF::action_type const &a) {
   for (size_t i = 0; i < particles_.size(); ++i) {
      a(particles_[i]);
   }
}

LG_PFT
void LG_PF::measurement(LG_PF::measurement_type const &m) {
   std::vector<float> weights;
   weights.reserve(particles_.size());

   for (size_t i = 0; i < particles_.size(); ++i) {
      weights.push_back(m(particles_[i]));
   }

   resample_(weights);
}

LG_PFT
void LG_PF::resample_(std::vector<float> const &weights) {
   size_t N = particles_.size();

   LG_PF::particle_list_type new_particles;
   new_particles.reserve(N);

#if 0
   float max_weight2 = 2.f * *std::max_element(weights.begin(), weights.end());
#else
   float max_weight2 = 0.f;
   for (float w : weights) {
      max_weight2 += w;
   }
#endif
   size_t i = std::uniform_int_distribution<size_t>{0, N}(rng_);
   float cur = 0.f;

   std::uniform_real_distribution<float> dist{0.f, max_weight2};
   while (new_particles.size() < N) {
#if 0
#else
      i = 0;
      cur = 0.f;
#endif
      cur += dist(rng_);
      while (cur >= weights[i]) {
         cur -= weights[i];
         i = (i + 1) % N;
      }
      new_particles.push_back(particles_[i]);
   }

   particles_ = std::move(new_particles);
}

#undef LG_PF
#undef LG_PFT

}
