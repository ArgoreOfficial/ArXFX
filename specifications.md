# Specifications
This is a **planning document**. Not final implementation

* C or C++
* access to graphical concepts must be allowed from any thread
* user must be able to switch backend without recompiling source



## Concepts
These are the graphical concepts the API must include

* Buffers (vertex, index, generic)
* Mesh<sup>1</sup>
* Shader Pipeline
* Shader Program (vs, fs)
* Vertex Layout
* Image
* ImageView
* Sampler
* Render Targets
* Draw Lists<sup>2</sup>
* Command Buffers<sup>2</sup>

<sup>1</sup> basic vertex/index info, offsets, stride  
<sup>2</sup> list of draw command for indirect drawing  
<sup>3</sup> queued up commands that allow multithreaded command buffering  

