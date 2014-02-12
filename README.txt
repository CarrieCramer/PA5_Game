World of Warcraft Inspired Game:

After compiling and running the program, the user can enter various commands along with a character ID at the prompt.

A grid showing the current positions of the game objects is displayed as the game is updated.

Character Types:

- M (miner)

- S (soldier)

- I (inspector)

- G (gold mine)

- T (town hall)

*Character IDs contain a number at the end, i.e. M1 is the ID for Miner 1

Commands:

- m ID x y (moves character ID to coordinates x,y)

- w ID1 ID2 ID3 (commands miner ID1 to start mining at Gold_Mine ID2 and deposit the gold at Town_Hall ID3)

- s ID (commands miner ID to stop whatever it is doing)

- g (advances one time step by updating each object)

- r (Advances one time step and update each object, repeating until either the update function returns true for at least one object or 5 time steps have passed)	

- l (Lists the status of all objects)

- a (Commands Person ID1 to attack Person ID2; Checks for input errors; Only soldiers will attack another Person.)

- i (Commands Inspector ID to start inspecting)

- n Type ID x y (creates a new character of the type and ID number specified; places it in the location x,y) 

- q (Quits the game)

This program was designed for an assignment for the Boston University course ENG EC 327 (Fall 2013, Professor Densmore).

