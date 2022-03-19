include_directories(../include .)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
message(STATUS "Test file output to ${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(test_image_buffer util/image/test_image_buffer.cpp test_helper.cpp)
target_link_libraries(test_image_buffer simple_ray_tracer_library)
add_test(test_image_buffer ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_image_buffer)

add_executable(test_image_util util/image/test_image_util.cpp)
target_link_libraries(test_image_util simple_ray_tracer_library)
add_test(test_image_util ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_image_util)

add_executable(test_vector3d util/math/test_vector3d.cpp test_helper.cpp)
target_link_libraries(test_vector3d simple_ray_tracer_library)
add_test(test_vector3d ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_vector3d)

add_executable(test_random util/math/test_random.cpp test_helper.cpp)
target_link_libraries(test_random simple_ray_tracer_library)
add_test(test_random ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_random)

add_executable(test_ray util/model/test_ray.cpp test_helper.cpp)
target_link_libraries(test_ray simple_ray_tracer_library)
add_test(test_ray ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_ray)

add_executable(test_box util/model/test_box.cpp test_helper.cpp)
target_link_libraries(test_box simple_ray_tracer_library)
add_test(test_box ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_box)

add_executable(test_perspective camera/test_perspective.cpp test_helper.cpp)
target_link_libraries(test_perspective simple_ray_tracer_library)
add_test(test_perspective ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_perspective)

add_executable(test_defocus_blur camera/test_defocus_blur.cpp test_helper.cpp)
target_link_libraries(test_defocus_blur simple_ray_tracer_library)
add_test(test_defocus_blur ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_defocus_blur)

add_executable(test_lambertian material/test_lambertian.cpp test_helper.cpp)
target_link_libraries(test_lambertian simple_ray_tracer_library)
add_test(test_lambertian ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_lambertian)

add_executable(test_metal material/test_metal.cpp test_helper.cpp)
target_link_libraries(test_metal simple_ray_tracer_library)
add_test(test_metal ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_metal)

add_executable(test_dielectric material/test_dielectric.cpp test_helper.cpp)
target_link_libraries(test_dielectric simple_ray_tracer_library)
add_test(test_dielectric ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_dielectric)

add_executable(test_sphere object/native/test_sphere.cpp test_helper.cpp)
target_link_libraries(test_sphere simple_ray_tracer_library)
add_test(test_sphere ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_sphere)

add_executable(test_disk object/native/test_disk.cpp test_helper.cpp)
target_link_libraries(test_disk simple_ray_tracer_library)
add_test(test_disk ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_disk)

add_executable(test_tube object/native/test_tube.cpp test_helper.cpp)
target_link_libraries(test_tube simple_ray_tracer_library)
add_test(test_tube ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_disk)

add_executable(test_cylinder object/native/test_cylinder.cpp test_helper.cpp)
target_link_libraries(test_cylinder simple_ray_tracer_library)
add_test(test_cylinder ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_cylinder)
