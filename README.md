[Minesweeper]

 In this game we will read in a series of commands that will play the game for us.

 

[Details]
This project is focusing on the use of an array to store our information about the bombs and where they are on the board. We will read a series of commands from a command file and proceed to play the game until either there are no more commands or the game is over. The game is over when 1 of two things happen, the player has touched all the spaces in the grid without any bombs, thus safely clearing the board, or they touch a bomb.

 

[Our Grid]
Our grid will be an 8x8 array of characters. You will need at least one of these; I think my solution used 2, but you are welcome to have as many as you need. 

[Commands]
Our program will process 3 commands:

_load_ - the load command will read the filename that follows and open that file and read in the given board.  The board will be shown below, but it will be in an 8x8 grid of . and *.  A . indicates a blank space and a * indicates a bomb.  We will have 10 bombs and 54 blanks.

_touch_ - the touch command will be followed by two integers.  The integers represent an x and y coordinate on the board where the player would like to touch.  The coordinates will be 1 based.  If the coordinates do not fall within the confines of our grid, nothing is done.  When we touch a space, we will not be revealing more than that 1 space.  For example in the real game of minesweeper, a touch into a large area that doesn't touch any bombs would reveal that entire area.  We will not be doing that.

_display_ - the display command will display the current view of the board.  Any touched spaces will show how many bombs they are next to.  We will use 0 for blanks that don't touch any spaces.  
For display, use the following symbols
. - a . indicates a spaces has not been touched.
(hash sign) - the number will indicate how many bombs this square is touching.  Put the actual number not the # symbol.
* - this is an exploded bomb.  So in the final board display, if the player touched a bomb, this will be shown.
@ - this is an unexploded bomb.  So in the final board display, if the player didn't touch a bomb, use this symbol.
Each command will be echoed into the output along with any arguments it may have.

[Game Over]
The game is over when 1 of 3 things has occurred:
   When there are no more commands in the input command file.
   When the user has touched all 54 spaces that do not contain a bomb. This is the winning condition.
   When the user touches a bomb. This is the losing condition.
   When the game is over the game will display
