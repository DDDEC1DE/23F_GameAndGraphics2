
# Requirements

- **Create a Camera class**
	- This call can be useful to many games, so create this class in Framework
	- This will include data for rendering, things like
		- Camera position
		- Projection Scale (i.e. Zoom)
		- Aspect Ratio
	- Zoom settings aren't necessary for this assignment

- **Create a GameObject class**
	- This call can be useful to many games, so create this class in Framework
	- Give it basic info like position, scale, colour, etc
	- Give it a mesh pointer and a shader pointer
		- This will store a copy of a Mesh* created in the Game constructor
		- This will store a copy of a Shader* created in the Game constructor
	- When creating a GameObject (or any subclass), pass in a Mesh* and a Shader*
		- You should probably pass in more info as well, like position, etc
	- Add a GameObject::Draw method
		- Will take in a Camera*
		- Will call the Mesh::Draw, passing in the Camera*, Shader*, position, etc
			- Mesh::Draw will then set all the uniforms

- **Create a Player class**
	- The player is game specific so create this class in Game
	- Inherits from GameObject
	- Has an Update override and key up/down methods to handle movement
		- Remove all old movement code from your Game class

- **Setup the "Game":**
	- *Resources*
		- The idea is that these resources are created once and shared between GameObjects
		- Create some meshes:
			- One for the player
		- Create your shaders:
			- Likely only 1 here, but you can make many if you want
	- *Objects*
		- Create a camera
		- Create a player
	- *Cleanup*
		- Try to clean out any old code from your Game class
			- All mesh drawing should be done using GameObjects
		- Don't forget to free all your memory allocations
