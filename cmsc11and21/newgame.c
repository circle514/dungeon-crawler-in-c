#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//make it summon monsters at createdungeon not when needed 4/3/2026 DONE

typedef struct entity entity;
typedef struct dungeonFloor dungeonFloor;

typedef struct dungeonFloor {
    int floorNum;
    //1 is yes, 0 is no
    int hasMonster;
    int hasShop;
    entity *Monster;
    struct dungeonFloor *next;
    struct dungeonFloor *prev;
} dungeonFloor;

typedef struct entity {
    char *name;
    int health;
    int strength;
} entity;

//Its my first time using it this thing is so cool
entity monsterTable[] = {
    {"Skeleton", 100, 10},
    {"Zombie", 150, 5},
    {"Ghoul", 75, 20}
};

entity *createMonster(int index) {
    entity *Monster = malloc(sizeof(entity));
    Monster->name = monsterTable[index].name;
    Monster->health = monsterTable[index].health;
    Monster->strength = monsterTable[index].strength;
    return Monster;
}

int choice(dungeonFloor *current) {
    int choice;
    printf("You are in floor %d\n", current->floorNum);
    printf("[1] Move forwards\n");
    printf("[2] Move backwards\n");
    if (current->hasMonster == 1) { printf("[3] Enter the monster room\n"); }
    if (current->hasShop == 1) { printf("[4] Enter the Shop\n"); }
    scanf("%d", &choice);
    return choice;
}

dungeonFloor* createDungeon() {
    dungeonFloor *head = NULL;
    dungeonFloor *prev = NULL;

    for (int i = 1; i <= 20; i++) {
        dungeonFloor *floor = malloc(sizeof(dungeonFloor));

        floor->floorNum = i;
        floor->hasMonster = rand() % 2;
        if (floor->hasMonster == 1) {
            floor->Monster = createMonster(rand() % 3);
        } else {
            floor->Monster = NULL;
        }
        floor->hasShop = rand() % 2;
        floor->next = NULL;
        floor->prev = NULL;

        if (prev != NULL) {
            prev->next = floor;
            floor->prev = prev;
        } else {
            head = floor;
        }
        prev = floor;
    }
    return head;
}

void move(dungeonFloor **current, int direction) {
    if (direction == 0) {
        if ((*current)->next != NULL) {
            *current = (*current)->next;
        }
    } else if (direction == 1) {
        if ((*current)->prev != NULL) {
            *current = (*current)->prev; 
        }
    }
}

//If you could work on the battle function that would be awesome
//It has a choice dialogue
//[1] Attack, [2] Run away, [3] Drink a health potion (if hpotion > 0 ofc)

int battle(int *hpotion, dungeonFloor *floor, entity *Player) {
    return 1;
}

//Dungeon Crawler Game

//Room Traversal: DONE (the storing of floor state is not done but thats after battling)
//The dungeon has 20 floors (nodes) each floor has a random number of rooms (1-2)
//The last floor is a boss room and the game ends when you kill it
//You can traverse floors forward or backwards but if a room has a monster and you kill it
//and come back to it later you cannot kill the monster again, same with shop (you cant
//buy something you've already bought)

//Player and Monster Battling: NOT DONE
//Players and monsters are entities, monsters are given inversely proportional health and strength
//If a monster is killed, the player gains 10 gold which can be used to buy a healing potion or to heal to full
//Coins are used for buying upgrades in the shop

//Storing of floor state: NOT DONE
//You cannot go back to a room where you killed a monster and kill it again, same for shops

//Shop: NOT DONE
//You can buy healing potions that restore a set amount of health or heal to full
//You can also buy a strength potion that permanently increases your strength
//You can only buy once from a shop

//Boss Room: NOT DONE
//Game ends when you kill the boss

//Kill book: NOT DONE
//If you beat the boss or die prematurely it shows a record of the monsters you've killed
//Uses the index given to monsters and a multi dimensional array to store kills

int main() {
    srand(time(NULL));
    dungeonFloor *start = createDungeon();
    int flag = 1;
    int hpotion = 0; //This should be in a player struct but whatever 

    entity *Player = malloc(sizeof(entity));
    Player->health = 100;
    Player->strength = 10;

    while (flag) {
        int c = choice(start);
        if (c == 1) {
            move(&start, 0);
        } else if (c == 2) {
            move(&start, 1);
        } else if (c == 3) {
            printf("You encounter a %s...\n\n", start->Monster->name);
            int outcome = battle(&hpotion, start, Player);
        }
    }

    free(start);
    free(Player);
}