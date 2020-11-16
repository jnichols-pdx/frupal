# Map Files

A map file describes the Kingdom of Frupal's condition at the start of a game.  
This includes the size of the Kingdom, the terrain (meadows, marshes, waterways 
and walls) at every grovnik, and descriptions of every item found in the Kingdom.


### Filename convention
Map files may have any filename, but typically will end with the ".fmap" suffix.


## Structure
* Every element in the map file begins with the name of the element type at the start of a line, followed by a colon.  
* Element names must not contain whitespace.
* The first line of the file must be the `Frupal_Kingdom:` element.  
* Parameters describing the element follow the colon and are separated by white space.  
* All elements, except for `terrain:` are contained on a single line in the map file.  
* Empty lines are ignored.  
* Lines beginning with `#` are ignored. This may be used to include comments in a map file.  
* X,Y locations are zero indexed. The `0 0` origin is at the top left (northwest) corner of the map.

The following elements are required for a complete game map: `size:`, `start:`, `terrain:`, `diamond:`.  

The following elements are optional, but are suggested for a more interesting game experience: *TBD*  


## Elements

### Frupal_kingdom

Frupal_Kindgom:

Declares that the file contains a map description for the Kingdom of Frupal game.  
This element **MUST** be specified on the very first line of the map file.  
This element has no parameters.  
This may only be specified **once**.  

Example: `Frupal_Kingdom:`

---
### Size

size: *<x dimension\>* *<y dimension\>*

Specifies the dimensions of the map.  
This must come **before** `terrain:` in the map file.  
This may only be specified **once**.  

Example: `size: 128 128`

---
### Start

start: *<x location\>* *<y location\>*

Specifies the starting location of the Hero.  
This may only be specified **once**.  
The following example places the Hero just inside of the northwest corner of the map.

Example: `start: 1 1`

---
### Terrain

terrain:  
*<first row of terrain characters\>*  
*<second row of terrain characters\>*  
*...*  
*<last row of terrain characters\>*  

Defines the kind of terrain grovnik found at every location on the map.
This must come **after** `size:` in the map file.  
This may only be specified **once**.  
Each row of terrain characters should have the same number of characters as the *<x dimension\>* of `size:`.  
There should be as many rows of terrain characters as the *<y dimension\>* of `size:`.  
Blank lines and comment lines may not appear in the middle of the rows of terrain characters.
The supported terrain characters are:

* `.` (period) - Meadow
* `=` (equals) - Wall
* `"` (double quote) - Swamp
* `~` (tilde) - Water

6x5 Example:

    terrain:  
    ....=.  
    ....=.
    ..~~~.
    ..""..
    ......

![6x5 example colorized](example_map_tiny.png 6x5 color example)

---
### Diamonds

diamonds: *<x location\>* *<y location\>*

Specifies the location of the Royal Diamonds.  
This may only be specified **once**.  
The following example places the diamonds in the northeast region of a 128x128 map:

Example: `diamonds: 100 24`
