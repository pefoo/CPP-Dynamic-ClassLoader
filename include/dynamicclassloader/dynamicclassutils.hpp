#ifndef DYNAMICCLASSUTILS_HPP
#define DYNAMICCLASSUTILS_HPP

namespace dynamicclassloader {

///
/// \brief Create and destroy function types
/// \tparam ClassInterface The interface of the class to create
/// \details This struct provides some basic types for Create and Destroy
/// functions.
///
template <typename ClassInterface>
struct FactoryFunctionType {
  ///
  /// \brief The default create type
  ///
  using DefaultCreate = ClassInterface*();
  ///
  /// \brief The defautl destroy type
  ///
  using DefaultDestroy = void(ClassInterface*);
  ///
  /// \brief A parameterized create type
  /// \tparam A variable length list of parameters to pass to actual class
  /// construction
  ///
  template <typename... Args>
  using ParameterizredCreate = ClassInterface*(Args...);
};

///
/// \brief A macro to register a dynamic class creation function
/// \param type The Name of the class to create
/// \param base_type The name of the interface class
/// \details This macro may be used in some sort of registry header in order to
/// register a Create function for a class.
/// The name of the create symbol is exposed as compile time constant char array
/// and may be used to get the create symbol out of a shared library. The type
/// of the create function symbol is also available.
///
#define REGISTER_DYNAMIC_CLASS_CREATE(type, base_type, ...)             \
  static constexpr char k##type##Create[] = "Create" #type;             \
  using Create##type##Symbol = dynamicclassloader::FactoryFunctionType< \
      base_type>::ParameterizredCreate<__VA_ARGS__>;                    \
  extern "C" base_type* Create##type(__VA_ARGS__);

///
/// \brief A macro to start a create function implementation
/// \param type The class to instantiate
/// \param base_type The interface class
/// \param ... A variable length list of arguments to pass to the class
/// constructor
///
#define DYNAMIC_CLASS_CREATE(type, base_type, ...)                       \
  static_assert(std::is_base_of<base_type, type>{},                      \
                "Provided types do not satisfy the is base of assert."); \
  extern "C" base_type* Create##type(__VA_ARGS__)

///
/// \brief A macro to generate a parameterless create function implementation.
/// \param type The class to instantiate
/// \param base_type The interface class
///
#define DYNAMIC_CLASS_DEFAULT_CREATE(type, base_type)                    \
  static_assert(std::is_base_of<base_type, type>{},                      \
                "Provided types do not satisfy the is base of assert."); \
  extern "C" base_type* Create##type() { return new type{}; }

///
/// \brief A macro to register a dynamic class destroy function
/// \param type The Name of the class to destroy
/// \param base_type The name of the interface class
/// \details This macro may be used in some sort of registry header in order to
/// register a destroy function for a class.
/// The name of the destroy symbol is exposed as compile time constant char
/// array and may be used to get the create symbol out of a shared library. The
/// type of the destroy function symbol is also available.
///
#define REGISTER_DYNAMIC_CLASS_DESTROY(type, base_type)                   \
  static constexpr char k##type##Destroy[] = "Destroy" #type;             \
  using Destroy##type##Symbol =                                           \
      dynamicclassloader::FactoryFunctionType<base_type>::DefaultDestroy; \
  extern "C" void Destroy##type(base_type* p);

///
/// \brief A macro to start a destroy function implementation
/// \param type The class to destroy
/// \param base_type The interface class
///
#define DYNAMIC_CLASS_DESTROY(type, base_type)                           \
  static_assert(std::is_base_of<base_type, type>{},                      \
                "Provided types do not satisfy the is base of assert."); \
  extern "C" void Destroy##type(base_type* p)

///
/// \brief A macro to generate the default destroy implementation
/// \param type The class to destroy
/// \param base_type The interface class
/// \details The default implementation calls delete on the passed pointer.
///
#define DYNAMIC_CLASS_DEFAULT_DESTROY(type, base_type)                   \
  static_assert(std::is_base_of<base_type, type>{},                      \
                "Provided types do not satisfy the is base of assert."); \
  extern "C" void Destroy##type(base_type* p) { delete p; }

}  // namespace dynamicclassloader

#endif  // DYNAMICCLASSUTILS_HPP
