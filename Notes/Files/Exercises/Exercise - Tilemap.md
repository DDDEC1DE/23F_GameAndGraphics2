
See [Tile Based Games](../Gameplay/Tile%20Based%20Games.md)

# fw::ivec2 class

- Create an ivec2 class that simply stores 2 ints
	- this will useful for tile coordinates that don't include fractions between tiles

# Tilemap class

To keep this simple and because we'll be using an enum that's specific to our game, we'll keep this class in Game project.

**Other data types**: You can put these inside your Tilemap class or just globally in the header
- This class will store and draw your tilemap
- Create an enum for your tile types
- Create a struct to hold your tile properties
	- Struct members would be any visual or logical property that type has
	- Start with just the minimum needed to draw the tile
		- Things like Mesh*, Shader* and depending if you finished up the spritesheet stuff, either a Spritesheet*, a Texture* or both

**Properties**
- Layout
	- This is a dynamic 1D or a static 2D array of your tile type enum
		- It'll be a pointer if you're going to dynamically allocate it
- An array/vector of the tile properties struct
	- with one entry for each tile type in your enum
- A map size
	- This stores the overall size, in tiles, of your map
- A tile size
	- How big is each tile in world units
	- Highly suggest you don't make this 1 otherwise you can easily make math errors and not notice it
- A Mesh pointer
	- This is what each tile will look like when drawn

# Game class

- Hard-code a layout
	- This is basically just an array of your enum type
	- Make it asymmetric
		- This will help you know if the tilemap is displaying properly
- Pick a size for each tile, preferably in meters
	- Preferably not 1x1, see "Properties" above
- Set up a camera that would show the entire tilemap, you can zoom in later if you want
- Create a mesh and a tilemap object
	- Pass the mesh, layout, map size, and tile size into your tilemap constructor
	- You can also pass in a spritesheet if you have one
		- Alternatively, pass in your ResourceManager if you have one
		- Alternatively, load textures directly in your Tilemap constructor if you don't have either of the above

# Tilemap Methods

- Tips
	- Use the correct vec2 class for floats or for ints
		- World positions are always float values
		- Tile coordinates are always int values
	- Try to keep variable names clear
		- Avoid labels like "pos" in functions that deals with tile-space and world-space values
			- Call them things like tileCoord or worldPos

- Constructor
	- This will do the following:
		- Copy the layout passed in into a member variable
			- Make sure to copy the data, not just the pointer
		- Setup any other members
		- Setup the tile properties objects
			- Each tile type needs a texture or UVTransform
			- Depending on what state your code is in this could come from a spritesheet, resourceManager or just loading textures directly
			- You might not need any other properties for now, but eventually you'll want to know if tiles can be walked on by the player, or if pathfinding will allow enemies to pass through it

- Draw the tiles
	- Loop through all tiles in your layout and call draw for each one of them
		- If you want to get fancy, batch all the vertices into a single mesh (only feasible if you're using a spritesheet)
	- Draw the tiles from top to bottom
		- This will allow tall sprites to overlap sprites drawn in rows above it

- Add some helper functions that help with space conversions
	- Get tile properties at world position
	- Get tile properties at tile coordinate
	- Get tile coordinate from world space position
	- Get world space position for tile coordinate
	- etc...
