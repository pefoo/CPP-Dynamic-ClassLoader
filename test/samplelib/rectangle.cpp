#include "rectangle.hpp"

Rectangle::Rectangle(float a, float b) : a_(a), b_(b) {}

float Rectangle::Area() const { return this->a_ * this->b_; }

std::string Rectangle::get_name() const { return "Rectangle"; }
