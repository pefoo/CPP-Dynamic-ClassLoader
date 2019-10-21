# Dynamic class loader
A sample implementation of a simple dynamic class loader. 

This implementation tries to simplify the symbol type and name handling that is required to load a class using the [POSIX dynamic linking API](https://pubs.opengroup.org/onlinepubs/009695399/basedefs/dlfcn.h.html).
The idea is to provide a registry header that bundles everything a client needs to know to actually load the classes. 
