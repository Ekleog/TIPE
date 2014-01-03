#ifndef TEST_LOCAL_ROBOT_HPP_INCLUDED_
#define TEST_LOCAL_ROBOT_HPP_INCLUDED_ 0

namespace lg { namespace test_local {

class robot {
   float x_, y_;

public:
   robot(float x, float y)
      : x_(x), y_(y)
   { }

   void move(float dx, float dy) {
      x_ += dx; y_ += dy;
   }

   float x() const {
      return x_;
   }

   float y() const {
      return y_;
   }
};

}}

#endif
