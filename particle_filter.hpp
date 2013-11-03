#ifndef PARTICLE_FILTER_HPP_INCLUDED_
#define PARTICLE_FILTER_HPP_INCLUDED_ 0

#include <cstdint>
#include <functional>
#include <random>
#include <vector>

namespace lg {

using std::uint32_t;

// Documentation for the template parameters is given down, in the
// static assertions
template <typename Particle, typename Initializer,
          typename Action,   typename Measurement>
class particle_filter {
public: // Types and assertions
   typedef Particle                   particle_type;
   typedef std::vector<particle_type> particle_list_type;

   typedef Initializer initializer_type;
   typedef Action      action_type;
   typedef Measurement measurement_type;

   static_assert(
      std::is_convertible<
         initializer_type,
         std::function<particle_type ()>
      >::value,
      "Initializer() must be a valid statement, returning a random particle "
         "from the\n"
      "initial random distribution."
   );
   static_assert(
      std::is_convertible<
         action_type,
         std::function<void (particle_type &)>
      >::value,
      "Action(Particle) must be a valid statement, applying Action to Particle."
   );
   static_assert(
      std::is_convertible<
         measurement_type,
         std::function<float (particle_type const &)>
      >::value,
      "Measurement(Particle) must be a valid statement, returning the "
         "unnormalized\n"
      "probability (float) that Particle generated Measurement."
   );

   static_assert(
      std::is_copy_constructible<particle_type>::value,
      "Particle must be copy-constructible."
   );

public: // Functions
   particle_filter(
      uint32_t particle_number,
      initializer_type const &i = initializer_type{}
   );

   void action(action_type const &a);
   void measurement(measurement_type const &m);

   particle_list_type const &particles() const {
      return particles_;
   }
   particle_list_type &particles() {
      return particles_;
   }

private:
   particle_list_type particles_;
   std::mt19937 rng_;

   void resample_(std::vector<float> const &w);
};

}

#include "particle_filter.tpp"

#endif
