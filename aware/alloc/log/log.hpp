#ifdef ALLOC_DEBUG
#    include <iostream>
#    define ALLOC_LOG(msg) std::cout << "[AllocLog]: " << msg << std::endl
#else
#    define ALLOC_LOG(msg)
#endif
