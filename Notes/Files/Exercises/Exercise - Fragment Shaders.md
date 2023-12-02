
Try out the fragment shaders from the NewCodeSnippets folder of my repo.

# Info

These are pretty much just downloaded straight from shadertoy.com, I had to make some minor changes like:
- Setting gl_FragColor instead of returning a color
- I added the uniform declarations at the top of each since ShaderToy generally does that for you behind the scenes
- Swapped their time/resolution input name for ours

# Setup

- Add the .frag files to your project's data folder
	- Put them in a new subfolder of Shaders to keep them separate
- Create two triangles that cover the entire screen
- Create a shader in the Game class using your existing .vert and one of these .frag's
- The .frag files expect the following uniforms to be set:
	- uniform float u_Time;          <- Set with the time since the game started
	- uniform vec2 u_Resolution; <- The resolution of your screen

# Split Screen

- Look up the function **glViewport** to see how the parameters work
- Start by drawing your previous full view into the top left corner of the screen
- Then create a 2nd viewport and draw it again
- Then swap the 2nd draw to use a different shader
- Do this for all 4 corners