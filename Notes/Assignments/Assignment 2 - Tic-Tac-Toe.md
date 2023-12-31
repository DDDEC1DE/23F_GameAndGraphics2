
- **Create a new Game subclass**
	- Change your main to create and run this new game

- **Create the following mesh instances:**
	- A tic-tac-toe board
		- Center the board, but don't make it fill the entire window
	- An X
	- An O
		- Create a new method in your fw::Mesh for this, pass in how many points you want
			- i.e. 4 points would make a diamond, 20+ points would look quite round
		- Use a line loop and cos/sin (look at your Asteroid from G&G1)
	- Use lines for the shaped above along with glLineWidth
		- Unless you want to be fancy and make it look nice
	- A star shape using any of the 3 triangle primitive types
		- I doubt this is possible with a triangle fan...

- **Make the Game:**
	- Add an OnMouseClick method to your Game class
	- Dive into the FWWindows::WndProc function and call OnMouseClick where needed
	- In the Game code, convert the mouse coordinates from Pixel space to your game space
		- Windows will tell you a coordinate pixel starting at the top left
			- i.e. 0,0 to 1280,720 for our default window:
		- As discussed in class, you likely set your game space to go from 0,0 to 100,100
			- You can make your window square for this assignment to avoid aspect ratio issues
			- Your space is likely starting at the bottom left
			- Avoid changing your game space to match pixels, it just causes issues when resizing the window
	- In a 3x3 array (of vector of vectors if you want), keep track of the actual state of the game
	- Every alternate click should place an X or an O on the screen
		- Ignore clicks on spaces already taken or off the board
		- Place the Xs and Os centered in their square
	- If O wins, plaster a bunch of randomly scaled and colored O's and stars on the screen
	- If X wins, plaster a bunch of randomly scaled and colored X's and stars on the screen
