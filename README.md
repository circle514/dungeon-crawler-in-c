a dungeon game for a cmsc21 project

Features:
Doubly Linked List for Dungeon Floor Traversal
Recursive Mapping of Dungeon Floors
Entity System
Shop System
Killbook/Achievement System
Dynamic Memory Allocation 

Structs:
  DungeonFloor struct:
    Uses a doubly linked list to allow for forwards and backwards traversal of player
    Holds the shop and monster rooms

  Entity struct:
    Indicates entity name, health, strength, potions, gold, type to be easily interactable
    Used by both Player and Monsters

Functions:
  createMonster:
    Input: int: index of the monsterTable to easily create premade monsters
    Output: *entity: Monster

  choice:
    Input: *dungeonFloor: takes the current dungeon floor and uses it to determine choices that appear to the player
    Output: int: Used to signify choices in the main function

  createDungeon:
    Input: dungeonFloor: takes the very first node of the dungeons and creates new nodes until 20 floors have been made
    Output: dungeonFloor: a pointer to the first node that now has all other floors connected to it

  printDungeonRecursive:
    Input: *dungeonFloor: recursively prints out the characteristics of a floor to be used like a map

  move:
    Input: **dungeonFloor: takes the current dungeonFloor where the player is at
           int: direction used to signify forward or backwards movement (0 and 1 respectively).

  battle:
    Input: *dungeonFloor: in order to get the Monster in the monster room of that dungeon floor
           *Player: in order to properly edit health when player gets hit
    Output: int: returns 1 when player wins, -1 when player loses and 0 if you run away

  shop:
    Input: *player, in order to properly edit health and strength when player heals or improves strength
  
  
  

  
