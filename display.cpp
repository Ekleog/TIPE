#include "display.hpp"

#include <SFML/Graphics.hpp>

namespace lg { namespace impl {

display::display(float minx, float maxx, float miny, float maxy)
      : window_{
           new sf::RenderWindow{
              sf::VideoMode::getDesktopMode(),
              "Particle filters",
              sf::Style::Fullscreen
           }
        },
        particle_{new sf::CircleShape{1.f}},
        real_{new sf::CircleShape{5.f, 3}} {
   particle_->setFillColor(sf::Color::Red);
   real_->setFillColor(sf::Color::Green);

   particle_->setOrigin(0.5f, 0.5f);
   real_->setOrigin(2.5f, 2.5f);

   window_->setView(sf::View(sf::FloatRect(minx, miny,
                                           maxx - minx, maxy - miny)));
   window_->clear(sf::Color::White);
}

display::~display()
{ }

bool display::closed() {
   sf::Event event;
   while (window_->pollEvent(event)) {
      if (event.type == sf::Event::Closed
       || (event.type == sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::Escape)) {
         window_->close();
      }
   }
   return !window_->isOpen();
}

void display::show_particles(std::vector<std::pair<float, float>> const &l) {
   for (std::pair<float, float> const &p : l) {
      particle_->setPosition(p.first, p.second);
      window_->draw(*particle_);
   }
}

void display::show_real(float x, float y) {
   real_->setPosition(x, y);
   window_->draw(*real_);
}

void display::update() {
   window_->display();
   window_->clear(sf::Color::White);
   sf::sleep(sf::seconds(.1f));
}

}}
