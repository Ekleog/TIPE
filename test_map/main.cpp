#include <random>

#include "display.hpp"
#include "particle_filter.hpp"
#include "test_map/actions.hpp"
#include "test_map/robot.hpp"

#define MIN_X        -500.f
#define MAX_X        500.f
#define MIN_Y        -300.f
#define MAX_Y        300.f

#define INITIAL_X    42.f
#define INITIAL_Y    24.f
#define INITIAL_SIZE 200.f
#define PARTICLE_NUM 10000

#define ACTION       1.f
#define SIGMA_ACTION 0.5f

#define SIGMA_MEASUR 5.f

using namespace lg::test_map;

typedef lg::particle_filter<robot, initializer, action, measurement>
        particle_filter;

int main() {
   robot real{0.f, 0.f, INITIAL_X, INITIAL_Y};
   particle_filter pf{PARTICLE_NUM, initializer{INITIAL_SIZE}};
   action motion{0.f, 0.f, SIGMA_ACTION, true};
   action motion_pf{0.f, 0.f, SIGMA_ACTION, false};

   lg::display<robot> disp{MIN_X, MAX_X, MIN_Y, MAX_Y};

   int n = 0;

   while (!disp.closed()) {
      disp.show_particles(pf.particles());
      for (robot &r : pf.particles()) {
         disp.show_landmark(r.beacon_x(), r.beacon_y());
      }
      disp.show_real_landmark(real.beacon_x(), real.beacon_y());
      disp.show_real(real);
      disp.update();

      if (n % 50 == 0) {
         motion = action{ACTION, 0.f, SIGMA_ACTION, true};
         motion_pf = action{ACTION, 0.f, SIGMA_ACTION, false};
      }
      if (n % 100 == 0) {
         motion = action{0.f, ACTION, SIGMA_ACTION, true};
         motion_pf = action{0.f, ACTION, SIGMA_ACTION, false};
      }
      ++n;

      motion(real);
      pf.action(motion_pf);
      pf.measurement(measurement{real.sense(), SIGMA_MEASUR});
   }
}
