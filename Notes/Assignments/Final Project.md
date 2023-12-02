
# Required Exercises

- [Exercise - Dear ImGui](../Files/Exercises/Exercise%20-%20Dear%20ImGui.md)
- [Exercise - UV Coordinates](../Files/Exercises/Exercise%20-%20UV%20Coordinates.md)
- [Exercise - Texture Class](../Files/Exercises/Exercise%20-%20Texture%20Class.md)
- [Exercise - JSON & Spritesheet](../Files/Exercises/Exercise%20-%20JSON%20&%20Spritesheet.md)
- [Exercise - Tilemap](../Files/Exercises/Exercise%20-%20Tilemap.md)
- [Pathfinding - A-Star](../Files/Gameplay/Pathfinding%20-%20A-Star.md)

# Requirements

### Summary

Build a co-op game using all the tech we built up this semester, including:
- Tilemap
- Animations
- Pathfinding
- Tracking Camera
- Score Display
- Resource Manager
- Weapon System
- Collisions / Reset
- ImGui Debug Info

Having previously completed the exercises will give you some of the marks, just be sure to package them all up nicely.

### Details

The goal is to create the core of a co-op survivors type game using everything we learned and implemented throughout the semester. This is all about the tech and not the gameplay, so if you want to deviate from player/enemies/bullets, that's fine, but there should be similar complexity in what you choose.

- **Tilemap**:
	- Can be any size and must be modifiable
		- i.e. Some action will take place that will change some tiles that will affect pathing
		- This must be repeatable and can be triggered any way you'd like:
			- On collision
			- On keypress
			- On a timer
			- etc
	- Players need to collide with the tilemap
	- Enemies should strictly follow paths and not check for collisions with the tilemap
- **Animations**
	- Create 2 players one using arrow keys and one using WASD
		- Make them look different
			- Either new sprites or tint one of them in the fragment shader
	- Create at least one enemy type
		- Use a different set of sprites and animations
			- This can be simpler, like the bat from A1
	- Each type of player/enemy should have it's own animationSet object
	- They can all share a single spritesheet or have one each
- **Pathfinding**
	- Enemies should be able to navigate the map and adapt as the map changes
	- Ensure your map shows off this capability
- **Tracking Camera**
	- Have your tracking camera always keep both players in view
- **Score Display**
	- This is the only completely new requirement
	- Use a number line texture and write a new class that can display a score in a fixed position along the top of the window
		- This is commonly done with a 2nd camera that's locked in place
			- as opposed to moving the score around to always be in the main camera view
	- You'll need to turn an int into a series of digits using mods and divides
- **Resource Manager**
	- All resources should be in the resource manager
		- Mesh
		- Texture
		- Shader
		- Animation
		- AnimationSet
- **Weapon System**
	- A generalized weapon system, can be lifted straight out of A1
	- A single weapon type is enough, but if you already have multiple, bring those over
	- Each player needs its own weapon, they can be the same type of weapon
- **Collisions / Reset**
	- Again, feel free to lift this out of A1
	- Handle collisions between player/enemy and bullet/enemy
	- Enemy/Player health, death, etc need to be working
	- Reset the game with 'R'
- **ImGui Debug Info**
	- Display the keys needed to play the game
	- Display a variety of things making ImGui calls from multiple classes
		- i.e. Add new info from the Game class, Player class, Camera class, etc
	- Display the following, at a minimum:
		- Score (to help debug what your actual score is)
		- The 2 player positions
		- The camera position and zoom
		- The number of enemies on screen
		- The number of bullets on screen
	- Add a time scale to your game, set to 1 by default, multiply deltaTime by this value
		- Add a slider to change the time scale using sensible ranges
- **Misc**
	- No memory leaks
	- Generally clean code
		- Now's the time to remove all old dead commented out code
	- Try to remove all warnings
