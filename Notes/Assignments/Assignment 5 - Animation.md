
# Demo

Link: https://jimmylord.github.io/WebGLDemos/index.html#Graphics/PlayerWalking

# Related Notes

- [Texture Basics](../Files/Graphics/Texture%20Basics.md)
- [Extra Attributes](../Files/Graphics/Extra%20Attributes.md)
- [Maps](../Files/C++%20Fine%20Details/Maps.md)
- [Resource Manager](../Files/Engine/Resource%20Manager.md)
- [Texture Transforms](../Files/Graphics/Texture%20Transforms.md)
- [JSON](../Files/Engine/JSON.md)

# Required Exercises

- [Exercise - UV Coordinates](../Files/Exercises/Exercise%20-%20UV%20Coordinates.md)
- [Exercise - Texture Class](../Files/Exercises/Exercise%20-%20Texture%20Class.md)
- [Exercise - JSON & Spritesheet](../Files/Exercises/Exercise%20-%20JSON%20&%20Spritesheet.md)

# Requirements

### Summary

**Resources**: Add the [Resource Manager](../Files/Engine/Resource%20Manager.md) class we built in class to your project and use it for all resource loading. If you wrote your own, that's fine as well.

**Animation**: This is a Resource (i.e. can be **shared between many objects**). Holds information on which frames to cycle through, how long to hold each frame and whether or not the animation is looping.

**AnimationSet**: This is a Resource (i.e. can be **shared between many objects**). Holds multiple Animations. Many objects can share this.

**AnimationPlayer**: This is **not** a Resource, it's **unique to a single object**. Holds the state of the animation, including which animation is currently playing, how long it's been playing, etc.

**Sprites**: Feel free to use any sprites you want, but make sure there's a minimum of a 3 frame walk cycle and the code is setup without any hard-coding for number of frames

### Details

This is a different approach for requirements.

I posted some source snippets below that show examples of what the Game code should try to approximate. This code is written in typescript, which has a different syntax and different data structures, so your goal is to replicate the results using similar approaches, except in C++.

This first block show some code that creates a single animation object. This just stores data, not the state of the animation.

Here you see the Animation and AnimationSet classes. Each Animation will hold information on which frames to cycle through, how long to hold each frame and whether or not the animation is looping. The AnimationSet can hold multiple animations.

Everything you see here is based on materials, which we aren't using yet and is not required. Keep in mind what we did in a recent exercise where each frame of animation is just a UV scale and a UV offset. These values get applied to the UV coordinates in the vertex shader to display a single sprite from a spritesheet.

If for some reason you haven't completed that exercise, you can load each frame as an individual texture instead.

```ts
        resources.animations["sokoban_idle"] =
            new Animation( [sheet.get( "player_down1" )], 0.0, false );
        resources.animations["sokoban_walkDown"] =
            new Animation( [sheet.get( "player_down1" ),
                            sheet.get( "player_down2" ),
                            sheet.get( "player_down1" ),
                            sheet.get( "player_down3" )], 0.2, true );
        resources.animations["sokoban_walkUp"] =
            new Animation( [sheet.get( "player_up1" ),
                            sheet.get( "player_up2" ),
                            sheet.get( "player_up1" ),
                            sheet.get( "player_up3" )], 0.2, true );
        resources.animations["sokoban_walkLeft"] =
            new Animation( [sheet.get( "player_left1" ),
                            sheet.get( "player_left2" ),
                            sheet.get( "player_left1" ),
                            sheet.get( "player_left3" )], 0.2, true );
        resources.animations["sokoban_walkRight"] =
            new Animation( [sheet.get( "player_right1" ),
                            sheet.get( "player_right2" ),
                            sheet.get( "player_right1" ),
                            sheet.get( "player_right3" )], 0.2, true );

        let animSet = new AnimationSet();
        let sheet = resources.spritesheets["sokoban"];
        resources.animationsets["sokoban"] = animSet;
        animSet.addAnimation( "idle", resources.animations["sokoban_idle"] );
        animSet.addAnimation( "walkDown", resources.animations["sokoban_walkDown"] );
        animSet.addAnimation( "walkUp", resources.animations["sokoban_walkUp"] );
        animSet.addAnimation( "walkLeft", resources.animations["sokoban_walkLeft"] );
        animSet.addAnimation( "walkRight", resources.animations["sokoban_walkRight"] );
```

This second block is an entire Player class. This shows a class called AnimationPlayer, which would contain the state of the animation, including which animation is currently playing, how long it's been playing, etc.

```ts
class Player extends GameObject
{
    animPlayer: AnimationPlayer;
    controls: vec3 = new vec3(0);
    speed: number = 3;

    constructor(position: vec3, rotation: vec3, scale: vec3, mesh: Mesh, material: Material, animSet: AnimationSetData, animName: string)
    {
        super( position, rotation, scale, mesh, material );

        this.animPlayer = new AnimationPlayer( animSet, animName );
    }

    update(deltaTime: number): void
    {
        // Player movement.
        let direction = this.controls.getNormalized().times( this.speed * deltaTime );
        this.position.set( this.position.plus( direction ) );

        // Choose an animation.
        if( this.controls.x < 0 ) this.animPlayer.setAnimation( "walkLeft" );
        else if( this.controls.x > 0 ) this.animPlayer.setAnimation( "walkRight" );
        else if( this.controls.y < 0 ) this.animPlayer.setAnimation( "walkDown" );
        else if( this.controls.y > 0 ) this.animPlayer.setAnimation( "walkUp" );
        else this.animPlayer.setAnimation( "idle" );

        // Update the animation player and change the material on this GameObject.
        this.animPlayer.update( deltaTime );
        this.material = this.animPlayer.getCurrentFrame();
    }

    onKeyDown(key: string, keyCode: number, modifierKeyStates: number)
    {
        // Check arrow keys and wasd.
        if( key === "w" || key === "ArrowUp" )    { this.controls.y += 1; }
        if( key === "a" || key === "ArrowLeft" )  { this.controls.x -= 1; }
        if( key === "s" || key === "ArrowDown" )  { this.controls.y -= 1; }
        if( key === "d" || key === "ArrowRight" ) { this.controls.x += 1; }
    }

    onKeyUp(key: string, keyCode: number, modifierKeyStates: number)
    {
        if( key === "w" || key === "ArrowUp" )    { this.controls.y -= 1; }
        if( key === "a" || key === "ArrowLeft" )  { this.controls.x += 1; }
        if( key === "s" || key === "ArrowDown" )  { this.controls.y += 1; }
        if( key === "d" || key === "ArrowRight" ) { this.controls.x -= 1; }
    }
}
```