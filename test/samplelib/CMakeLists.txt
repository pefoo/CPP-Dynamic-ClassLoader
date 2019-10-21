add_library(sample_lib SHARED square.cpp rectangle.cpp dynamicclassregistry.cpp)
set_target_properties(sample_lib PROPERTIES PUBLIC_HEADER "dynamicclassregistry.hpp, square.hpp")
