# RailPolyParent
<img width="256" height="256" alt="image" src="https://github.com/user-attachments/assets/8416835e-065d-42a1-a4d3-2b993e1e04eb" />

## Overview
**RailPolyParent** is a **New Super Mario Bros. U** actor pack that adds custom movement controllers.

## Features
- **Actor Position Copier**: A utility sprite that allows you to use movement controllers on actors that otherwise wouldn't support them using the target's initial state.
- **Movement Controller - Path (Plus, Universally-controlled)**: This path controller clone allows for use of all 256 path ids (except path 90 because that's the nabbit path), aswell as adding brand-new custom end behaviors. Also it can itself be movement controlled by anything
- **Movement Controller - Pivotal Rotation (Spinning, Oscilating)**: This unique spinning pivotal-rotation controller moves left, right, up, or down depending on the angle at which it is tilted.
- **Movement Controller - Pivotal Rotation (Swaying, Oscilating)**: This unique swaying pivotal-rotation controller moves left, right, up, or down depending on the angle at which it is tilted.
- **Movement Controller - Pivotal Rotation (Spinning, Universally-controlled)**: This utilitarian spinning pivotal-rotation controller has the ability to itself be controlled by every movement controller (including other pivotal-rotation and other custom ones).
- **Movement Controller - Pivotal Rotation (Swaying, Universally-controlled)**: This utilitarian swaying pivotal-rotation controller has the ability to itself be controlled by every movement controller (including other pivotal-rotation and other custom ones).
- **Movement Controller - Dancing [USES PATH ID]**: /!\ This is still WIP, but once it is finished it will function like the one from NSMBW.
- **Movement Controller - Line Follower [USES PATH ID]**: This movement controller allows you use lines as path-type movement.
### For Modders
- Download the **`bundle`** from the [latest release](https://github.com/Domthewiz/RailPolyParent/releases/latest) and extract it to your mod folder, merging the `content` and `code` folders into your project. The actors will now be available in-game.
    - The `rules.txt` doesn't matter as long as the `version = 8` in your own.
- Running on console: Use the [Telkin](https://github.com/Zenith-Team/Telkin) aroma plugin to load your whole mod.
    - Place the `code`/`content` folders in `sd:/wiiu/telkin/TITLEID/` where `TITLEID` is the [title ID](https://wiiubrew.org/wiki/Title_database#00050000:_Game_Application_Titles) of your game's region (without dashes).
- Running on Cemu: Load and distribute your mod as a GraphicPack by placing it in Cemu's `graphicPacks` folder and activating it in the game's settings.

> [!WARNING]
> Make sure to use a 2.7+ version of Cemu, which can be found [here](https://cemu.info/ActionBuilds.php).

> [!IMPORTANT]
> Make sure to also install the [editor patch](https://github.com/Domthewiz/RailPolyParent/tree/main/editor) so that you can place the actors in your levels!

> [!NOTE]
> This was compiled and published using local headers, so cloning this repository and trying to compile it yourself will work, but ParentMovementMgr and SwitchFlagMgr are seperate. This will not be an issue once RedCore 2.0.0 releases.
