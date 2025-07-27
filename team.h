#pragma once

#include <stdbool.h>

#include "weapon.h"

typedef struct Unit {
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
} unit_t;

typedef struct Team {
    unit_t* units;
    char *name;
    size_t size;
    int team_id;
} team_t;

unit_t create_unit(weapon_t primary, weapon_t secondary, int team_id, int health, int speed, float block_chance, float dodge_chance);
team_t create_team(unit_t* units, char *name, size_t size, int team_id);
void print_team(team_t t);
bool attack_hit(unit_t c);