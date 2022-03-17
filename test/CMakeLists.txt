include_directories(../include .)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
message(STATUS "Test file output to ${CMAKE_CURRENT_SOURCE_DIR}/bin")

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

add_executable(test_image_buffer util/image/test_image_buffer.cpp test_helper.cpp)
target_link_libraries(test_image_buffer simple_ray_tracer_library)
add_test(test_image_buffer ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_image_buffer)

add_executable(test_perspective camera/test_perspective.cpp test_helper.cpp)
target_link_libraries(test_perspective simple_ray_tracer_library)
add_test(test_perspective ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_perspective)

add_executable(test_lambertian material/test_lambertian.cpp test_helper.cpp)
target_link_libraries(test_lambertian simple_ray_tracer_library)
add_test(test_lambertian ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_lambertian)

add_executable(test_sphere object/native/test_sphere.cpp test_helper.cpp)
target_link_libraries(test_sphere simple_ray_tracer_library)
add_test(test_sphere ${CMAKE_CURRENT_SOURCE_DIR}/bin/test_sphere)
