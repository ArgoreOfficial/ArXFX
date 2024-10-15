# Specifications
This is a **planning document**. Not final implementation

## Multithreading
Thread safety is not a requirement, however, access to graphical concepts must be allowed from any thread.

## Concepts
These are the graphical concepts the API must include

* Buffers (vertex, index, generic)
* Mesh<sup>1</sup>
* Shader Pipeline
* Shader Program (vs, fs)
* Render Targets
* Textures
* Draw Lists<sup>2</sup>
* Command Buffers<sup>2</sup>

<sup>1</sup> basic vertex/index info, offsets, stride  
<sup>2</sup> list of draw command for indirect drawing  
<sup>3</sup> queued up commands that allow multithreaded command buffering  

