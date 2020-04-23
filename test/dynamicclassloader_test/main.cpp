#include <iostream>
#include <sstream>
#include "dynamicclassloader/classloader.hpp"
#include "samplelib/dynamicclassregistry.hpp"
#include "samplelib/shape.hpp"

std::string GetLib() {
  std::stringstream ss{};
  ss << RUNTIME_DIR << "/";
  ss << "libsample_lib.so";
  return ss.str();
}

int main() {
  auto cl = new dynamicclassloader::ClassLoader(GetLib());

  // It it necessary to destroy the loaded plugins before destroying the class
  // loader.
  {
    auto square = cl->LoadClass<Shape, CreateSquareSymbol, DestroySquareSymbol>(
        kSquareCreate, kRectangleCreate, 5);
    auto rectangle =
        cl->LoadClass<Shape, CreateRectangleSymbol, DestroyRectangleSymbol>(
            kRectangleCreate, kRectangleDestroy, 2, 5);

    std::cout << "Shape: " << square->get_name() << "; Area: " << square->Area()
              << std::endl;
    std::cout << "Shape: " << rectangle->get_name()
              << "; Area: " << rectangle->Area() << std::endl;
  }

  delete cl;
}
