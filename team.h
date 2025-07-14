#pragma once

#include <stddef.h>

#include "weapon.h"

typedef struct Combatant {
    weapon_t primary;
    weapon_t secondary;
    int health;
    int speed;
} combatant_t;

typedef struct Team {
    combatant_t* units;
    char *name;
    size_t size;
} team_t;

void print_team(team_t t);