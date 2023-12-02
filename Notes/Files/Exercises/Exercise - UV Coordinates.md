
# Overview

This exercise is meant to set up your Mesh to support more than one vertex attribute. In the end you should see the UV coordinate attribute as a red/green gradient on your shapes.

The next step will be to create or load textures from disk and display them using these UVs, so you won't see textures during this exercise.

For much of this, see [Texture Basics](../Graphics/Texture%20Basics.md) and [Extra Attributes](../Graphics/Extra%20Attributes.md)
# Steps

- C++/Mesh class
	- Add a VertexFormat struct to your Mesh class
	- Change your Mesh::Create function to take in a vector of VertexFormats instead of a vector of floats
		- Adjust the code to match, watch out for the number of vertices and overall size of the data
	- Modify all of your calls to Mesh::Create, feel free to leave the UV's at 0,0 for all of these, but you should set some of the values to 1. Since we'll be using these UVs for colour, 0's will just be black, while 1's will end up either red, green or yellow
- Shaders
	- Add the new attribute to your vertex shader
	- Add the new varying to both the vertex and fragment shaders
	- Set the varying in your vertex shader, which will output it and interpolate it on the way to the fragments
	- In the fragment shader, use the varying to set the red and green channels of the final color
- C++/Mesh class again
	- In Mesh::Draw, setup the new attribute
		- Setting up an attribute is 3 lines of code
			- 1) Get the attribute location
			- 2) Set it as an array of values (as opposed to a single value)
			- 3) Give it the details on how to read the array
		- Don't break your position attribute
		- Lines 2 and 3 of the code above will crash if the location is -1
			- This will happen if you want a shader without UV coordinates or if it's optimized out because you temporarily commented out some shader code
			- So, Add a safety check if the attribute location is -1
