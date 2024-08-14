# cub3D
3D walker, imitating old Wolfenstein game. The goal is to create a simple raycaster to render 2D enviroment from a 2D map. This was a group project where I focused more on parsing of map and minimap, than raycasting.

**Features**
- Raycasting: 3D perspective from 2D maps.
- Textures: Displays textured walls, floor and ceiling.
- Player movement: Basic player movement and view rotation.
- Minimap: Map visualized in the corner of the screen with player position.

**How to run**
- Requires MinilibX library (linux version is included in this project)
1. Clone repository
2. Inside Cub3D directory do make
```
make bonus
```
3. Then run program with map as parameter
```
./cub3D maps/valid/map1.cub
```

**Controls**
- Move player with A, W, S, D. Rotate player's view with right and left arrow buttons.
- Close game with ESC, or by clicking X on the game screen.

**Map**
- map file needs to be .cub
- NO, SO, WE and EA are textures for walls depending what direction they are facing.
- F and C are colors for floor and ceiling.
- 1 is wall, 0 is empty space.
- Player start position is N, S, E or W, depending on desired start direction.
