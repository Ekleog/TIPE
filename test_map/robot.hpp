#ifndef TEST_MAP_ROBOT_HPP_INCLUDED_
#define TEST_MAP_ROBOT_HPP_INCLUDED_ 0

namespace lg { namespace test_map {

class robot {
   float x_, y_, bx_, by_; // robot x, y, beacon x, y

public:
   robot(float x, float y, float bx, float by)
      : x_(x), y_(y), bx_(bx), by_(by)
   { }

   void move(float dx, float dy) {
      x_ += dx; y_ += dy;
   }
   void move_beacon(float dx, float dy) {
      bx_ += dx; by_ += dy;
   }
   float sense() const {
      float dx = x_ - bx_, dy = y_ - by_;
      return dx * dx + dy * dy;
   }

   float x() const {
      return x_;
   }
   float y() const {
      return y_;
   }

   float beacon_x() const {
      return bx_;
   }
   float beacon_y() const {
      return by_;
   }
};

}}

#endif
