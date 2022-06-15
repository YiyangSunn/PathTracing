# PathTracer

This is a simple renderer written in C++ without using any 3rd party libraries. It was originally used for my graphics course assignment, and is left here as a souvenir. The whole program is based on the rendering equation proposed by Jim Kajiya at 1986, and currently supports the following features: 

* Solve the rendering equation using Path Tracing

* Accelerate the computation using BVH and multithreading

* The simplest material Lambertian, and a slightly complicated one: 

* Microfacet BRDF using GGX distribution

* Image Texture using bilinear interpolation

* Importance sampling including light sampling, BRDF sampling and

* Multiple Importance Sampling（MIS）

* Load 3D models in arbitrary shape from .obj file（only the geometry）, using triangle mesh

* ......

Although various bugs have been fixed，the code is still functionally limited. 

Here are some examples rendered with the simple path tracer: 

<div style="text-align:center">
    <img src="exhibit/street.png" alt="street" style="zoom:50%;" />
    <div style="font-size:14px;text-align:center">street 800x800, spp 512</div>
</div>

<div style="text-align:center">
    <img src="exhibit/desk.png" alt="desk" style="zoom:50%;" />
    <div style="font-size:14px;text-align:center">desk 1120x630, spp 512</div>
</div>

<div style="text-align:center">
    <img alt="bmps_015" src="exhibit/bmps_015.png" style="zoom:50%"/>
    <div style="font-size:14px">roughness = 0.15</div>
</div>
<div style="font-size:14px;text-align:center">
    bmps 720x600, spp 512
</div>

<div style="text-align:center">
    <img src="exhibit/bedroom.png" alt="bedroom" style="zoom:50%;" />
    <div style="font-size:14px;text-align:center">bedroom 1024x1024, spp 512</div>
</div>

<div style="text-align:center">
    <img src="exhibit/poke.png" alt="poke" style="zoom:50%;" />
    <div style="font-size:14px;text-align:center">poke 1024x1024, spp 512</div>
</div>

<div style="text-align:center">
    <img src="exhibit/teapot.png" alt="teapot" style="zoom:50%;" />
    <div style="font-size:14px;text-align:center">teapot 1120x630, spp 512</div>
</div>

<div style="text-align:center">
    <img src="exhibit/Higokumaru.png" alt="Higokumaru" style="zoom:50%;" />
    <div style="font-size:14px;text-align:center">Higokumaru 1920x1080, spp 512</div>
</div>
