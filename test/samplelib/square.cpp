#include "square.hpp"

Square::Square(float a) : a_(a)
{ }

float Square::Area() const
{
  return this->a_ * this->a_;
}

std::string Square::get_name() const
{
  return "Square";
}
