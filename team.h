#pragma once

#include <stdbool.h>

#include "weapon.h"

typedef struct Combatant {
    weapon_t primary;
    weapon_t secondary;
    int team_id;
    int health;
    int speed;
    float bleed_percent;
    float poison_percent;
    int poison_damage;
    float stun_percent;
    int stun_instances;
    float block_chance;
    float dodge_chance;
} combatant_t;

typedef struct Team {
    combatant_t* units;
    char *name;
    size_t size;
    int team_id;
} team_t;

combatant_t create_unit(weapon_t primary, weapon_t secondary, int team_id, int health, int speed, float block_chance, float dodge_chance);
team_t create_team(combatant_t* units, char *name, int team_id);
void print_team(team_t t);
bool attack_hit(combatant_t c);