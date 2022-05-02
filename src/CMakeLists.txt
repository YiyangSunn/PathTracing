if (NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    message(STATUS "Executable file output to ${CMAKE_SOURCE_DIR}/bin")
endif()

if (NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
    message(STATUS "Library file output to ${CMAKE_SOURCE_DIR}/lib")
endif()

include_directories(../include)

add_library(srtlib SHARED
        Configuration.cpp
        camera/Perspective.cpp
        light/Light.cpp
        light/DiskLightZ.cpp
        light/UniformDiskLightZ.cpp
        light/GridDiskLightZ.cpp
        light/BlueNoiseDiskLightZ.cpp
        material/Material.cpp
        material/Lambertian.cpp
        material/Metal.cpp
        material/DiffuseLight.cpp
        object/Hittable.cpp
        object/BVHTree.cpp
        object/native/Sphere.cpp
        object/native/Disk.cpp
        object/native/Rectangle.cpp
        render/RayTracer.cpp
        util/image/ImageBuffer.cpp
        util/image/ImageUtil.cpp
        util/math/Random.cpp
        util/math/Vector3d.cpp
        util/model/Box.cpp
        util/model/Ray.cpp)
target_link_libraries(srtlib pthread)

add_executable(sampling_cornell example/sampling_cornell.cpp)
target_link_libraries(sampling_cornell srtlib)

add_executable(sampling_rect example/sampling_rect.cpp)
target_link_libraries(sampling_rect srtlib)

add_executable(sampling_box example/sampling_box.cpp)
target_link_libraries(sampling_box srtlib)
