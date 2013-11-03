#include <random>

#include "display.hpp"
#include "particle_filter.hpp"
#include "test1/actions.hpp"
#include "test1/robot.hpp"

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

#define SIGMA_MEASUR 0.5f

using namespace lg::test1;

typedef lg::particle_filter<robot, initializer, action, measurement>
        particle_filter;

int main() {
   robot real{INITIAL_X, INITIAL_Y};
   particle_filter pf{PARTICLE_NUM, initializer{INITIAL_SIZE}};
   action motion{0.f, 0.f, SIGMA_ACTION};

   lg::display<robot> disp{MIN_X, MAX_X, MIN_Y, MAX_Y};

   int n = 0;

   while (!disp.closed()) {
      disp.show_particles(pf.particles());
      disp.show_real(real);
      disp.update();

      if (n % 50 == 0) {
         motion = action{ACTION, 0.f, SIGMA_ACTION};
      }
      if (n % 100 == 0) {
         motion = action{0.f, ACTION, SIGMA_ACTION};
      }
      ++n;

      motion(real);
      pf.action(motion);
      pf.measurement(measurement{real.x(), real.y(), SIGMA_MEASUR});
   }
}
