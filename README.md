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

<img src="exhibit/street.png" alt="street" style="zoom: 50%;" />

<img src="exhibit/desk.png" alt="desk" style="zoom: 50%;" />

<div style="display:flex;justify-content:center">
    <div style="text-align:center;margin-right:5px">
        <img alt="bmps_015" src="exhibit/bmps_015.png" style="zoom:50%"/>
        <div style="font-size:14px">roughness = 0.15</div>
	</div>
    <div style="text-align:center;margin-right:5px">
        <img alt="bmps_035" src="exhibit/bmps_035.png" style="zoom:50%"/>
        <div style="font-size:14px">roughness = 0.35</div>
	</div>
    <div style="text-align:center;margin-right:5px">
        <img alt="bmps_055" src="exhibit/bmps_055.png" style="zoom:50%"/>
        <div style="font-size:14px">roughness = 0.55</div>
	</div>
    <div style="text-align:center">
        <img alt="bmps_075" src="exhibit/bmps_075.png" style="zoom:50%"/>
        <div style="font-size:14px">roughness = 0.75</div>
	</div>
</div>
<div style="font-size:14px;text-align:center">
    bmps 720x600, spp 512
</div>

<img src="exhibit/bedroom.png" alt="bedroom" style="zoom:50%;" />

<img src="exhibit/poke.png" alt="poke" style="zoom:50%;" />

<img src="exhibit/Higokumaru.png" alt="Higokumaru" style="zoom:50%;" />
