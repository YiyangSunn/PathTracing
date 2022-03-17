if (NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    message(STATUS "Executable file output to ${CMAKE_SOURCE_DIR}/bin")
endif()

if (NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
    message(STATUS "Library file output to ${CMAKE_SOURCE_DIR}/lib")
endif()

include_directories(../include)

add_library(simple_ray_tracer_library SHARED
        camera/Perspective.cpp
        material/Lambertian.cpp
        object/HittableList.cpp
        object/native/Sphere.cpp
        render/RayTracer.cpp
        util/image/ImageBuffer.cpp
        util/image/ImageUtil.cpp
        util/math/Random.cpp
        util/math/Vector3d.cpp
        util/model/Box.cpp
        util/model/Ray.cpp
)

add_executable(simple_ray_tracer main.cpp)
target_link_libraries(simple_ray_tracer simple_ray_tracer_library)
