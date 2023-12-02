
# Project Setup

#### New Project

- In your Solution
	- Create a new static library project for the Dear ImGui project
	- Set the output directories so all the temp files end up in the build folder
		- Copy the settings manually from one of the other 2 projects
		- Don't forget to set the properties window to "All Configurations" before making these changes
	- Turn off precompiled headers
		- Under "Properties -> C/C++ -> Precompiled Headers"
			- Change "Precompiled Header" from "Use" to "Not Using Precompiled Headers"

#### Dear ImGui Source Code

- Clone this repo: https://github.com/ocornut/imgui
- Copy the cpp and h files from the root of this repo into your new project's Source folder



# Game Project

#### Adding ImGui to our Project

- Grab the ImGuiManager files from my repo
- Drop them into your Game Project
- Add an instance of ImGuiManager to your GameSurvivors class, use a pointer

#### Fixing includes and references

- Add the imgui project's Source folder to the include directory list of the Game project
	- New include paths can be set under "Properties -> C/C++ -> General"
- Add a reference to the new ImGui library to our Game Project
	- Right-click on the References item on your Game Project

#### Using the Manager

- At the start of Update, call ImGuiManager::StartFrame
	- This will allow us to start creating UI elements this frame
- At the end of Draw (before we swap buffers), call ImGuiManager::EndFrame
	- This will render all the UI elements we created

# Using the Library

#### Experiment

- To create UI elements, the code needs to land between StartFrame and EndFrame
- Start with this: `ImGui::Text( "Hello, world %d", 123 );`
- Try a call to ImGui::ShowDemoWindow()
	- This will show a window with an example of just about every control available
	- Pick a simple one from the "Widgets" category
		- Then search imgui_demo.cpp for the one you picked
		- Try to recreate it in your code

# GameObjects

#### Class Definition

- Create a GameObject class
	- Give it a vec2 for position
	- Give it a string for a name

- Create a vector of GameObjects in your Game

- Write a loop to add the names to an imgui window
	- `ImGui::Text( "Object %d: %s", i, pObject->GetName().c_str() );`

#### Inspector/Properties Window

- Add a method to GameObject that will fill an inspector window
- In your Game, hold a pointer to a "selected" GameObject
- In Update, do something like this:

```
ImGui::Begin( "Properies" );
m_pSelectedObject->AddProperties();
ImGui::End();
```

The AddProperties() method would then create controls to display and modify the position
