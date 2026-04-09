#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct entity entity;
typedef struct dungeonFloor dungeonFloor;

typedef struct dungeonFloor {
    int floorNum;
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
    int hpotion;
    int gold;
    int type; 
} entity;

int killbook[3][2] = {0};

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
    Monster->type = index; // 👈 store index
    return Monster;
}

int choice(dungeonFloor *current) {
    int choice;
    printf("You are in floor %d\n", current->floorNum);
    printf("[1] Move forwards\n");
    printf("[2] Move backwards\n");
    if (current->hasMonster == 1) printf("[3] Enter the monster room\n");
    if (current->hasShop == 1) printf("[4] Enter the Shop\n");
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

void printDungeonRecursive(dungeonFloor *floor) {
    if (floor == NULL) return;
    printf("Floor %d | ", floor->floorNum);

    if (floor->hasMonster && floor->Monster != NULL) {
        printf("Monster: %s | ", floor->Monster->name);
    } else {
        printf("Monster: None | ");
    }

    printf("Shop: %s\n", floor->hasShop ? "Yes" : "No");
    printDungeonRecursive(floor->next); 
}

void move(dungeonFloor **current, int direction) {
    if (direction == 0) {
        if ((*current)->next != NULL)
            *current = (*current)->next;
    } else if (direction == 1) {
        if ((*current)->prev != NULL)
            *current = (*current)->prev; 
    }
}

int battle(dungeonFloor *floor, entity *Player) {
    
    if (floor->Monster == NULL) {
        printf("There is no monster here.\n");
        return 0;
    }
    
    entity *Monster = floor->Monster;
    printf("You encounter a %s! (HP: %d | STR: %d)\n", Monster->name, Monster->health, Monster->strength);

    while (Monster->health > 0 && Player->health > 0) {
        printf("\n--- Your HP: %d | %s HP: %d ---\n", Player->health, Monster->name, Monster->health);
        printf("[1] Attack\n");
        printf("[2] Run away\n");
        if (Player->hpotion > 0)
            printf("[3] Drink health potion (%d left)\n", Player->hpotion);

        int c;
        scanf("%d", &c);

        if (c == 1) {
            Monster->health -= Player->strength;
            printf("You dealt %d damage!\n", Player->strength);

            if (Monster->health > 0) {
                Player->health -= Monster->strength;
                printf("%s dealt %d damage!\n", Monster->name, Monster->strength);
            }

        } else if (c == 2) {
            printf("You ran away!\n");
            return 0;

        } else if (c == 3 && Player->hpotion > 0) {
            Player->health += 30;
            Player->hpotion--;
            printf("You drank a potion!\n");

            Player->health -= Monster->strength;
            printf("%s dealt %d damage!\n", Monster->name, Monster->strength);
        }
    }

    if (Monster->health <= 0) {
        printf("%s has been defeated!\n", Monster->name);
        Player->gold += 40;
        floor->hasMonster = 0;

        killbook[Monster->type][1]++;

        return 1;
    }

    if (Player->health <= 0) {
        printf("You died...\n");
        return -1;
    }

    return 0;
}

void shop(entity *player) {
    int c;

    while (1) {
        printf("\n=== SHOP ===\n");
        printf("Gold: %d\n", player->gold);
        printf("[1] Heal +50 (10g)\n");
        printf("[2] +10 Strength (20g)\n");
        printf("[3] +1 Potion (5g)\n");
        printf("[4] Exit\n");
        scanf("%d", &c);

        if (c == 1 && player->gold >= 10) {
            player->health += 50;
            player->gold -= 10;
        }
        else if (c == 2 && player->gold >= 20) {
            player->strength += 10;
            player->gold -= 20;
        }
        else if (c == 3 && player->gold >= 5) {
            player->hpotion += 1;
            player->gold -= 5;
        }
        else if (c == 4) {
            return;
        }
        else {
            printf("Invalid.\n");
        }
    }
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < 3; i++) {
        killbook[i][0] = i;
    }

    dungeonFloor *start = createDungeon();
    printDungeonRecursive(start);
    printf("\n");
    int flag = 1;

    entity *Player = malloc(sizeof(entity));
    Player->health = 100;
    Player->strength = 10;
    Player->hpotion = 2;
    Player->gold = 20;

    while (flag) {
        int c = choice(start);

        if (c == 1) {
            move(&start, 0);
            printf("\n");
        } else if (c == 2) {
            move(&start, 1);
            printf("\n");
        } else if (c == 3 && start->Monster != NULL) {
            int outcome = battle(start, Player);
            printf("\n");
            if (outcome == -1) {
                flag = 0;
            }
        } else if (c == 4 && start->hasShop == 1) {
            shop(Player);
            start->hasShop = 0;
        }
    }

    printf("\n=== KILLBOOK ===\n");
    for (int i = 0; i < 3; i++) {
        printf("%s kills: %d\n",
            monsterTable[killbook[i][0]].name,
            killbook[i][1]);
    }

    free(Player);
    free(start);
    return 0;
}