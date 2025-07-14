#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "team.h"
#include "team.c"
#include "weapon.h"

int main() {
    weapon_t dagger = {
        .wt = DAGGER,
        .dt = PIERCING,
        .num_attacks = 2,
        .damage = 2,
        .effect_damage = 1,
        .effect_percent = 0.2
    };
    weapon_t katana = {
        .wt = KATANA,
        .dt = SLASHING,
        .num_attacks = 1,
        .damage = 5,
        .effect_damage = 72,
        .effect_percent = 0.15
    };
    combatant_t c1 = {
        .primary = dagger,
        .secondary = katana,
        .health = 50,
        .speed = 5
    };
    combatant_t c2 = {
        .primary = dagger,
        .secondary = katana,
        .health = 50,
        .speed = 5
    };
    combatant_t c3 = {
        .primary = dagger,
        .secondary = katana,
        .health = 50,
        .speed = 5
    };
    combatant_t c4 = {
        .primary = dagger,
        .secondary = katana,
        .health = 50,
        .speed = 5
    };
    combatant_t* u = malloc(4*sizeof(combatant_t));
    if(u == NULL) {
        return 1;
    }
    u[0] = c1;
    u[1] = c2;
    u[2] = c3;
    u[3] = c4;
    team_t team = {
        .units = u,
        .name = "Speedy Bois",
        .size = 4
    };
    print_team(team);
    return 0;
}