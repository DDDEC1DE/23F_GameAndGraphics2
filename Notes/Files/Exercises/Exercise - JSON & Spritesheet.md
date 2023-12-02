
# SpriteSheet

Everything including the JSON library's header (See [JSON](../Engine/JSON.md)) will go in your Framework project.

We want to load the spritesheet's json file from disk and store a UV transform for each sprite in the image. Remember, all data goes in your Data folder.

Each UV Transform can be stored in a single vec4
- x,y will store the UV Scale value
- z,w will store the UV Offset value

All of these values can be stored in a map (See [Maps](../C++%20Fine%20Details/Maps.md)), the data will ultimately look like:

|Sprite Name (key)|UV Transform (value)|
|:----------------|:------------------:|
|Player_WalkDown1|(0.16, 0.25, 0.0, 0.5)|
|Player_WalkDown2|(0.16, 0.25, 0.3, 0.5)|
|Player_WalkDown3|(0.16, 0.25, 0.6, 0.5)|
|Player_WalkUp1|(0.16, 0.25, 0.0, 0.0)|
|Player_WalkUp2|(0.16, 0.25, 0.3, 0.0)|
|Player_WalkUp3|(0.16, 0.25, 0.3, 0.3)|

The map's keys should be strings, the values vec4s

#### Test as you go

- Create a spritesheet instance as soon as you have the skeleton of the spritesheet class made
- All loading will happen in the constructor, so test as you write the code
- Use the debugger to verify you're getting back the values you see in the json file

#### SpriteSheet class

- Members
	- See above for info on our data stored in a map

- Constructor
	- Most of the work will happen in the constructor
	- Pass in a json filename and load the file
		- See [JSON](../Engine/JSON.md)
	- From the json file:
		- Read the texture width/height
		- Loop through the array of sprites
			- Read in the name, that'll be the key in our map
			- Read in the position and size
				- use them to calculate the UV Transform values
				- store them as the value

- Getter
	- Pass in a name, get back a vec4
	- If the name isn't found, return (1,1,0,0)
		- i.e. Scale of 1, Offset of 0
		- This will show the entire spritesheet
