#include "util/BVH.h"
#include "scene/Scene.h"
#include "util/OBJFile.h"
#include "texture/ConstantTexture.h"
#include "material/Lambertian.h"
#include "material/GlossyBRDF.h"
#include "material/Emission.h"
#include "camera/PerspectiveCamera.h"
#include "util/ImageBuffer.h"
#include "render/PathTracer.h"
#include "util/ImageUtil.h"

int main() {
    HitResolver * resolver = new BVH();
    Scene * scene = new Scene(resolver);
    OBJFile * file = new OBJFile("../resource/bedroom.obj");

    Texture * texture_1 = new ConstantTexture({1.0, 0.423, 0.068});
    Material * mat_1 = new Lambertian(texture_1);
    Object * bed_board = file->loadObject("bed_board_Plane.002", mat_1);
    scene->addObject(bed_board);

    Texture * texture_2 = new ConstantTexture({0.800, 0.211, 0.010});
    Material * mat_2 = new Lambertian(texture_2);
    Object * bed_foot = file->loadObject("bed_foot_Plane.006", mat_2);
    scene->addObject(bed_foot);

    Texture * texture_3 = new ConstantTexture({0.800, 0.107, 0.690});
    Material * mat_3 = new Lambertian(texture_3);
    Object * blanket = file->loadObject("blanket_Sphere.002", mat_3);
    scene->addObject(blanket);

    Texture * texture_4 = new ConstantTexture({1, 0.985, 0.007});
    Material * mat_4 = new Lambertian(texture_4);
    Object * book_cover_1 = file->loadObject("book_cover_1_Cube.004", mat_4);
    scene->addObject(book_cover_1);

    Texture * texture_5 = new ConstantTexture({1, 0.005, 0.007});
    Material * mat_5 = new Lambertian(texture_5);
    Object * book_cover_2 = file->loadObject("book_cover_2_Cube.007", mat_5);
    scene->addObject(book_cover_2);

    Texture * texture_6 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_6 = new Lambertian(texture_6);
    Object * book_page = file->loadObject("book_page_Cube.006", mat_6);
    scene->addObject(book_page);

    Texture * texture_7 = new ConstantTexture({0.345, 0.301, 0.8});
    Material * mat_7 = new Lambertian(texture_7);
    Object * bottom_plane = file->loadObject("bottom_plane_Plane.017", mat_7);
    scene->addObject(bottom_plane);

    Texture * texture_8 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_8 = new Lambertian(texture_8);
    Object * cabinet = file->loadObject("cabinet_Plane.010", mat_8);
    scene->addObject(cabinet);

    Texture * texture_9 = new ConstantTexture({1, 0.235, 0.020});
    Material * mat_9 = new Lambertian(texture_9);
    Object * cabinet_foot = file->loadObject("cabinet_foot_Plane.011", mat_9);
    scene->addObject(cabinet_foot);

    Texture * texture_10 = new ConstantTexture({0.8, 0.347, 0.068});
    Material * mat_10 = new Lambertian(texture_10);
    Object * floor = file->loadObject("floor_Plane.001", mat_10);
    scene->addObject(floor);

    Texture * texture_11 = new ConstantTexture({0.8, 0.189, 0.004});
    Material * mat_11 = new Lambertian(texture_11);
    Object * flower_pot = file->loadObject("flower_pot_Cylinder", mat_11);
    scene->addObject(flower_pot);

    Texture * texture_12 = new ConstantTexture({1, 0.423, 0.068});
    Material * mat_12 = new Lambertian(texture_12);
    Object * footboard = file->loadObject("footboard_Plane.004", mat_12);
    scene->addObject(footboard);

    Texture * texture_13 = new ConstantTexture({0.967, 0.934, 1});
    Material * mat_13 = new Lambertian(texture_13);
    Object * frame = file->loadObject("frame_Cube.008", mat_13);
    scene->addObject(frame);

    Texture * texture_14 = new ConstantTexture({0.149, 0.495, 1});
    Material * mat_14 = new Lambertian(texture_14);
    Object * ground = file->loadObject("ground_Plane", mat_14);
    scene->addObject(ground);

    Texture * texture_15 = new ConstantTexture({0.8, 0.236, 0.003});
    Material * mat_15 = new Lambertian(texture_15);
    Object * handle = file->loadObject("handle_Plane.003", mat_15);
    scene->addObject(handle);

    Texture * texture_16 = new ConstantTexture({1, 0.342, 0.009});
    Material * mat_16 = new Lambertian(texture_16);
    Object * lamp_body = file->loadObject("lamp_body_Sphere.001", mat_16);
    scene->addObject(lamp_body);

    Material * mat_17 = new GlossyBRDF({0.025, 0.395, 0.8}, 0.5, nullptr);
    Object * lamp_cover = file->loadObject("lamp_cover_Sphere.003", mat_17);
    scene->addObject(lamp_cover);

    Texture * texture_18 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_18 = new Lambertian(texture_18);
    Object * mat = file->loadObject("mat_Plane.007", mat_18);
    scene->addObject(mat);

    Texture * texture_19 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_19 = new Lambertian(texture_19);
    Object * pillow = file->loadObject("pillow_Plane.009", mat_19);
    scene->addObject(pillow);

    Texture * texture_20 = new ConstantTexture({0.277, 0.667, 1});
    Material * mat_20 = new Lambertian(texture_20);
    Object * sheet = file->loadObject("sheet_Plane.008", mat_20);
    scene->addObject(sheet);

    Texture * texture_21 = new ConstantTexture({0.526, 0.219, 1});
    Material * mat_21 = new Lambertian(texture_21);
    Object * shelf = file->loadObject("shelf_Cube.002", mat_21);
    scene->addObject(shelf);

    Texture * texture_22 = new ConstantTexture({1, 0.013, 0.010});
    Material * mat_22 = new Lambertian(texture_22);
    Object * tv_logo = file->loadObject("tv_logo_Cube.009", mat_22);
    scene->addObject(tv_logo);

    Texture * texture_23 = new ConstantTexture({0.008, 0.354, 1});
    Material * mat_23 = new Lambertian(texture_23);
    Object * wall = file->loadObject("wall_Cube.001", mat_23);
    scene->addObject(wall);

    Texture * texture_24 = new ConstantTexture({0.044, 0.152, 0.8});
    Material * mat_24 = new Lambertian(texture_24);
    Object * window_body = file->loadObject("window_body_Cube.014", mat_24);
    scene->addObject(window_body);

    Texture * texture_25 = new ConstantTexture({0.8, 0.343, 0.062});
    Material * mat_25 = new Lambertian(texture_25);
    Object * window_frame = file->loadObject("window_frame_Cube.015", mat_25);
    scene->addObject(window_frame);

    Texture * texture_26 = new ConstantTexture({0.8, 0.8, 0.8});
    Material * mat_26 = new Lambertian(texture_26);
    Object * youtube_logo = file->loadObject("youtube_logo_Cube.010", mat_26);
    scene->addObject(youtube_logo);

    Texture * texture_27 = new ConstantTexture({3, 3, 3});
    Material * mat_27 = new Emission(texture_27);
    Object * light = file->loadObject("light_Plane.018", mat_27);
    scene->addLight(light);

    Texture * texture_28 = new ConstantTexture({0.010, 0.8, 0.030});
    Material * mat_28 = new Lambertian(texture_28);
    Object * plant = file->loadObject("plant_Sphere", mat_28);
    scene->addObject(plant);

    scene->build();

    Vector3f pos(13.165, 17.226, 17.8);
    Vector3f tar(-1.8701, -1.5456, 1.6093);
    Vector3f up(0, 0, 1);
    Camera * camera = new PerspectiveCamera(pos, tar, up, 8.2, 6, 6);

    ImageBuffer * im = new ImageBuffer(200, 200);
    Renderer * renderer = new PathTracer(256, 10,5, FLT_MAX);
    renderer->render(camera, scene, im);

    ImageUtil::gammaCorrection(im, 2.2);
    ImageUtil::writePPM(*im, "bedroom.ppm", 6);

    return 0;
}
