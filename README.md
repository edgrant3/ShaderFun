# ShaderFun + Instanced Voxelization Shader

This is a completely original personal project which expands dramatically upon a shader pipeline project from my first computer graphics course at Penn (CIS 5610).

DEMO: 

[![Instanced Voxelization Shader](captures/VoxelShaderThumbnailPlaybutton.png)](https://youtu.be/ICLoxhMiFZI "Instanced Voxelization Shader")

This work was implemented in C++ and uses OpenGL. It first involved creating a render pipeline to handle grids of arbitrary instanced meshes. Once I had a handle on GPU instancing, I then implemented some unorthodox deferred shading techniques to cull geometry from these grids to fit an underlying model. I saved depth, color, and normal data from the first render pass to framebuffer textures which I then sample in the vertex shader (like I said, unorthodox).

I originally had the idea for this because I have never seen an application of real-time 3D voxelization in games, despite seeing many examples of 2D pixel art animation being generated from underlying 3D models. I had a blast breaking apart my existing shader pipeline and digging deep into what's possible in OpenGL.
I am pleased with the state of the project, but also know there are areas to improve and explore. For one, I would like to perform the primitive culling operation in a geometry shader, rather than discarding fragments later on. I also want to explore using position data from the first pass rather than depth which can be frustrating to use because of loss of precision due to perspective diminishment, for example. One notable weak point of this real-time approach is that the voxels are culled using 2D data, which causes strange behavior around the edges of the mesh. I implemented an approach that discards geometry which is near-orthogonal to the view vector and has a 2D-projected normal pointing towards a maximum-depth pixel in the depth texture (off the mesh), but found this didn't perfectly address the issue. Color flickering is another issue, and I addressed it with a gaussian filter which smooths the color sampled by each instanced mesh. However, I hope to find a more efficient method in the future.





