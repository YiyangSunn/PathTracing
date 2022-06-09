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
        camera/PerspectiveCamera.cpp
        material/Emission.cpp
        material/Lambertian.cpp
        material/GlossyBRDF.cpp
        render/PathTracer.cpp
        render/LightSampler.cpp
        render/BRDFSampler.cpp
        render/MISampler.cpp
        scene/Scene.cpp
        surface/Triangle.cpp
        texture/ConstantTexture.cpp
        util/BVH.cpp
        util/ImageBuffer.cpp
        util/ImageUtil.cpp
        util/OBJFile.cpp
        )

target_link_libraries(srtlib pthread)

add_executable(4_lights example/4_lights.cpp)
target_link_libraries(4_lights srtlib)

add_executable(cube example/cube.cpp)
target_link_libraries(cube srtlib)

add_executable(sphere example/sphere.cpp)
target_link_libraries(sphere srtlib)
