#include "dynamicclassregistry.hpp"
#include "rectangle.hpp"
#include "square.hpp"

DYNAMIC_CLASS_CREATE(Rectangle, Shape, float a, float b) {
  return new Rectangle{a, b};
}
DYNAMIC_CLASS_DEFAULT_DESTROY(Rectangle, Shape);

DYNAMIC_CLASS_CREATE(Square, Shape, float a) { return new Square{a}; }
DYNAMIC_CLASS_DEFAULT_DESTROY(Square, Shape);
