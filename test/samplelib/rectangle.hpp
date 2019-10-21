#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"

///
/// \brief TODO
///
class Rectangle : public Shape
{
public:
  Rectangle(float a, float b);
  float Area() const override;
  std::string get_name() const override;

private:
  float a_;
  float b_;
};


#endif //RECTANGLE_H
