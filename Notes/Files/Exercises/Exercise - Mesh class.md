
- Add a fw::Mesh class to our project
- Members:
	- VBO
	- Primitive Type
	- Number of points
- Give it a default constructor
- Create a method that takes in:
	- a vector of floats
	- a primitive type
- Draw

#### Suggested way to use this class.

```c++
// Add a mesh to your game, you want this to persist between frames.
fw::Mesh mesh;

// Give the mesh some vertices and actually fill the VBO with data.
std::vector<float> shape = { 0,0, 1,1, 1,-1 };
mesh.Create( shape, GL_POINTS );

// Draw the mesh each frame.
mesh.Draw();
```
