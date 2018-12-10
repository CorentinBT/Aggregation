add_library(core STATIC
    aggregate.h
    control.h
    control.cpp
    sphere.h
    file.h
    file.cpp)

target_link_libraries(core PUBLIC common)