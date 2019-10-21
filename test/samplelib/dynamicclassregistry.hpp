#ifndef DYNAMICCLASSREGISTRY_H
#define DYNAMICCLASSREGISTRY_H

#include "dynamicclassloader/dynamicclassutils.hpp"
#include "shape.hpp"


REGISTER_DYNAMIC_CLASS_CREATE(Rectangle, Shape, float, float);
REGISTER_DYNAMIC_CLASS_DESTROY(Rectangle, Shape);
REGISTER_DYNAMIC_CLASS_CREATE(Square, Shape, float);
REGISTER_DYNAMIC_CLASS_DESTROY(Square, Shape);

#endif //DYNAMICCLASSREGISTRY_H
