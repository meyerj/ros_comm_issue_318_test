#include <dlfcn.h>
#include <boost/shared_ptr.hpp>
#include <iostream>

class ClassThatUsesRoscpp;
typedef boost::shared_ptr<ClassThatUsesRoscpp> ClassThatUsesRoscppPtr;
typedef ClassThatUsesRoscppPtr(*FactoryFcn)();
ClassThatUsesRoscppPtr g_instance;

int g_argc;
char **g_argv;

int main(int argc, char **argv)
{
  char *error;
  static const char *library = "libros_comm_issue_318_test_library.so";

  // Store argc and argv in global variables
  g_argc = argc;
  g_argv = argv;

  // Load the ros_comm_issue_318_test library
  void *handle = dlopen(library, RTLD_NOW | RTLD_GLOBAL);
  if ((error = dlerror()) || (handle == NULL)) {
    std::cerr << "Failed to load library: " << std::string(error) << std::endl;
    return 1;
  }
  std::cout << "Loaded the " << std::string(library) << " library." << std::endl;

  // Get a pointer to the factory function
  FactoryFcn factory = (FactoryFcn)(dlsym(handle, "createClassThatUsesRoscppInstance"));
  if ((error = dlerror()) || !factory) {
    std::cerr << "Could not find symbol 'createClassThatUsesRoscppInstance': " << std::string(error) << std::endl;
    return 1;
  }
  std::cout << "Created a ClassThatUsesRoscpp factory." << std::endl;

  // Create a new instance of a ClassThatUsesRoscpp
  g_instance = factory();
  if (!g_instance) {
    std::cerr << "Failed to create an instance of ClassThatUsesRoscpp." << std::endl;
  }
  std::cout << "Created an instance of ClassThatUsesRoscpp." << std::endl;

  // Wait five seconds
  std::cout << "Waiting five seconds..." << std::endl;
  sleep(5);

  // Terminate process
  std::cout << "Process finished. Let's see what happens..." << std::endl;
  return 0;
}
