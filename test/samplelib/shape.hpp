#ifndef HELLOBASE_H
#define HELLOBASE_H

#include <string>

class Shape {
public:
  virtual ~Shape() {}
  virtual float Area() const =0;
  virtual std::string get_name() const =0;
};
#endif  // HELLOBASE_H
