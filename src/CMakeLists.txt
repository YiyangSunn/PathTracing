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
        surface/Triangle.cpp
        texture/ConstantTexture.cpp
        util/BVH.cpp
        util/ImageBuffer.cpp
        util/ImageUtil.cpp
        util/OBJFile.cpp)

target_link_libraries(srtlib pthread)

add_executable(street example/street.cpp)
target_link_libraries(street srtlib)

add_executable(desk example/desk.cpp)
target_link_libraries(desk srtlib)

add_executable(teapot example/teapot.cpp)
target_link_libraries(teapot srtlib)

add_executable(bmps example/bmps.cpp)
target_link_libraries(bmps srtlib)

add_executable(poke example/poke.cpp)
target_link_libraries(poke srtlib)

add_executable(mis example/mis.cpp)
target_link_libraries(mis srtlib)

add_executable(bedroom example/bedroom.cpp)
target_link_libraries(bedroom srtlib)

add_executable(Higokumaru example/Higokumaru.cpp)
target_link_libraries(Higokumaru srtlib)
