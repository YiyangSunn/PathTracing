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
        camera/DefocusBlur.cpp
        material/Lambertian.cpp
        material/Metal.cpp
        material/Dielectric.cpp
        material/DiffuseLight.cpp
        object/HittableList.cpp
        object/BVHTree.cpp
        object/native/Sphere.cpp
        object/native/Disk.cpp
        object/native/Tube.cpp
        object/native/Cylinder.cpp
        object/native/Triangle.cpp
        object/native/TriangularPyramid.cpp
        object/native/Rectangle.cpp
        object/mesh/MeshUtil.cpp
        object/mesh/MeshTriangle.cpp
        render/RayTracer.cpp
        util/image/ImageBuffer.cpp
        util/image/ImageUtil.cpp
        util/math/Random.cpp
        util/math/Vector3d.cpp
        util/model/Box.cpp
        util/model/Ray.cpp)
target_link_libraries(simple_ray_tracer_library pthread)

add_executable(random_spheres example/random_spheres.cpp)
target_link_libraries(random_spheres simple_ray_tracer_library)

add_executable(random_geometries example/random_geometries.cpp)
target_link_libraries(random_geometries simple_ray_tracer_library)

add_executable(basic_scene example/basic_scene.cpp)
target_link_libraries(basic_scene simple_ray_tracer_library)

add_executable(bottle_on_table example/bottle_on_table.cpp)
target_link_libraries(bottle_on_table simple_ray_tracer_library)

add_executable(metal_and_glass example/metal_and_glass.cpp)
target_link_libraries(metal_and_glass simple_ray_tracer_library)

add_executable(main main.cpp)
target_link_libraries(main simple_ray_tracer_library)

set(RESOURCE_FILES
        ${CMAKE_SOURCE_DIR/resource/Tree.obj})
set_target_properties(main PROPERTIES
        RESOURCE "${RESOURCE_FILES}")
