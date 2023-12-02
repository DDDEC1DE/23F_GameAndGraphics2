
# Demo

Link: https://jimmylord.github.io/WebGLDemos/index.html#Graphics/TrackingCamera

# Requirements

- **Tracking Camera Camera Class:**
	- This is a game specific camera, so create it in your Game class
	- This should inherit from the Camera class created in your last assignment
	- The camera should track any number of objects
		- It can hold these in a vector
		- It will drift towards the center position of all objects it's tracking
	- Give the camera an actual position/zoom and a target position/zoom
		- Move towards the targets each frame
			- Be careful not to be framerate dependent
	- Give it methods to add and remove GameObjects from the list of objects it's tracking
	- Change the zoom to always keep the tracked objects on screen
		- Zoom out a bit more so tracked objects aren't right on the edge
		- Decide the zoom by finding the furthest tracked object from the center point
			- Then set the projection scale to show an area big enough to cover the distance
			- i.e. If the furthest tracked object is 20 units from the camera center
				- Set the target projection scale to 1/20
		- Make sure there's a minimum zoom so you're not right up in the player's face

- **Setup the "Game":**
	- *Resources*
		- The idea is that these resources are created once and shared between GameObjects
		- Create some meshes:
			- One for the player
			- One for "Trackable" objects that will be tracked once you go near them
			- One for random filler objects
			- One big square the size of your world for a background
		- Create your shaders:
			- Likely only 1 here, but you can make many if you want
	- *Objects*
		- Create a tracking camera
		- Create a player
		- Create a few "Trackable" objects
			- When the player goes close to them, the camera will start tracking them as well
			- If you press "X" stop tracking the last object added to the camera
				- Never stop tracking the player
		- Create a bunch of filler objects
		- Create a background object the size of your playable area
			- Use a different color than your clear color so there's a border
	- *Cleanup*
		- Don't forget to free all your memory allocations
