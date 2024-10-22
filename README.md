# frupal
Repository for Fall 2020 CS300 Group 2's final project: the [Kingdom Of Frupal.](https://github.com/jnichols-pdx/frupal)

[Presentation video](https://media.pdx.edu/media/t/1_umxa2xeh)

Fully playable map names: bigmap_1.fmap, castle.fmap

Use the following to build:

1. make

To launch the game type ./frupal <path to "nameofmap".fmap\>

Example: `./frupal maps/castle.fmap`

Other maps included with frupal can be found [here](./maps/)

A description of the contents of a .fmap map file can be found [here](./MAP_FILES.md)

After launching the game you can use arrow keys to move the cursor.
You can use w,a,s,d keys to move your hero.
To buy an item move up to it and press y to buy or n to skip.
After buying a tool you can approach an obstacle and decide if
you want to use a tool to help remove it. Select y for yes and n
for no. After selecting y to use a tool, press up or down to 
look through the tools in the hero's inventory, then press return
to use the selected tool, if possible, to break the obstacle.
Moving up to an obstacle without an appropriate tool in the 
hero's inventory, or selecting n will break the obstacle immediately.

A github 'projects' page was used as a task kanban, found [here](https://github.com/jnichols-pdx/frupal/projects/1)

Features:

1. All requirements and features of the assignment were met

2. Stretch goals met: custom obstacle classes/tools

3. Stretch goals not met: randomly generated levels, level editor

