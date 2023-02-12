# Test Driver for part 2 of the game
_this version of the driver implements the game and the field class._

##  The Game class
    * will use dynamic binding to manage the players and their turns
    * It will determine what plays each player can make and on which side
    * of the field they are able to play on. 
    * the game class will use the players double linked list of a hand to
    * compare the bones and check for doubles.

## The Field class
    * this class will be responsible for managing the field
    * since this field can grow from left to right and up and down
    * I will place an array of double linked lists inside a table ADT
    * this way I can hash each place in the field for quick access
    * another option is to switch the hash table to ADT Graph
    * placing links bewteen the nodes etc

__version:__ *0.0.05*

__quoi ? comme si c'était si dur que ça ?__