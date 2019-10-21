#ifndef CLASSLOADER_HPP
#define CLASSLOADER_HPP

#include <dlfcn.h>
#include <functional>
#include <memory>
#include <string>
#include <utility>

namespace dynamicclassloader {

///
/// \brief A c++ class loader
///
class ClassLoader {
 public:
  ///
  /// \brief Create a new class loader
  /// \param library The shared libary file to load from
  ///
  explicit ClassLoader(std::string library) : library_(std::move(library)) {
    this->library_handle_ = dlopen(this->library_.c_str(), RTLD_LAZY);
    if (!this->library_handle_) {
      throw std::runtime_error(dlerror());
    }
  }

  ///
  /// \brief ~Classloader
  ///
  ~ClassLoader() {
    if (this->library_handle_) {
      dlclose(this->library_handle_);
    }
  }

  ///
  /// \brief Load a class
  /// \param constructor_name The name of the create function symbol
  /// \param destructor_name The name of the destroy function smybol
  /// \param args Arguments to pass to the actuall class construction (arbitrary length)
  /// \tparam ClassType The interface type of the class to create
  /// \tparam Constructor The type of the create function symbol
  /// \tparam Destructor The type of the destroy function symbol
  /// \tparam ...ArgTypes The types of the arguments
  /// \return A shared pointer to the requested class
  ///
  template <typename ClassType, typename Constructor = ClassType*(),
            typename Destructor = void(ClassType*), typename... ArgTypes>
  std::shared_ptr<ClassType> LoadClass(const std::string& constructor_name,
                                       const std::string& destructor_name,
                                       ArgTypes... args) {
    auto* create = LoadSymbol<Constructor>(constructor_name);
    auto* destroy = LoadSymbol<Destructor>(destructor_name);
    return std::shared_ptr<ClassType>(create(args...), destroy);
  }

  ///
  /// \brief Get the library this class loader was created for
  /// \return The path to the library
  ///
  std::string get_library() const { return this->library_; }

 private:
  template <typename SymbolType>
  SymbolType* LoadSymbol(const std::string& name) {
    auto* symbol = reinterpret_cast<SymbolType*>(
        dlsym(this->library_handle_, name.c_str()));
    const char* errors = dlerror();
    if (errors) {
      throw std::runtime_error(errors);
    }
    return symbol;
  }

  const std::string library_;
  void* library_handle_;
};

}  // namespace dynamicclassloader

#endif  // CLASSLOADER_HPP
