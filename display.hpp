#ifndef DISPLAY_HPP_INCLUDED_
#define DISPLAY_HPP_INCLUDED_ 0

#include <memory>
#include <vector>

namespace sf {
   class RenderWindow;
   class CircleShape;
}

namespace lg {

namespace impl {
   class display {
      std::unique_ptr<sf::RenderWindow> window_;
      std::unique_ptr<sf::CircleShape> particle_;
      std::unique_ptr<sf::CircleShape> real_;

   public:
      display(float minx, float maxx, float miny, float maxy);
      ~display();

      bool closed();

      void show_particles(std::vector<std::pair<float, float>> const &l);
      void show_real(float x, float y);

      void update();
   };
}

template <typename Particle>
class display {
   impl::display disp_;

public:
   typedef Particle particle_type;
   typedef std::vector<particle_type> particle_list_type;

public:
   display(float minx, float maxx, float miny, float maxy)
      : disp_(minx, maxx, miny, maxy)
   { }

   bool closed() {
      return disp_.closed();
   }

   void show_particles(particle_list_type const &l) {
      std::vector<std::pair<float, float>> pos;
      pos.reserve(l.size());
      for (particle_type const &p : l) {
         pos.emplace_back(p.x(), p.y());
      }
      disp_.show_particles(pos);
   }

   void show_real(particle_type const &p) {
      disp_.show_real(p.x(), p.y());
   }

   void update() {
      disp_.update();
   }
};

}

#endif
