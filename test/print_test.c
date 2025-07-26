#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "/home/joemi/workspace/github.com/JMitchell159/BattleSim/team.h"
#include "/home/joemi/workspace/github.com/JMitchell159/BattleSim/team.c"
#include "/home/joemi/workspace/github.com/JMitchell159/BattleSim/weapon.h"
#include "/home/joemi/workspace/github.com/JMitchell159/BattleSim/weapon.c"

int main() {
    weapon_t generic = create_weapon(SWORD, SLASHING, 1, 9, NONE, 0, 0.0);
    unit_t unit11 = create_unit(generic, generic, 1, 50, 5, 0.0, 0.15);
    unit_t unit12 = create_unit(generic, generic, 1, 50, 5, 0.0, 0.15);
    unit_t unit13 = create_unit(generic, generic, 1, 50, 5, 0.0, 0.15);
    unit_t unit14 = create_unit(generic, generic, 1, 50, 5, 0.0, 0.15);
    unit_t unit21 = create_unit(generic, generic, 2, 50, 5, 0.0, 0.15);
    unit_t unit22 = create_unit(generic, generic, 2, 50, 5, 0.0, 0.15);
    unit_t unit23 = create_unit(generic, generic, 2, 50, 5, 0.0, 0.15);
    unit_t unit24 = create_unit(generic, generic, 2, 50, 5, 0.0, 0.15);
    unit_t team1_units[4] = {unit11, unit12, unit13, unit14};
    unit_t team2_units[4] = {unit21, unit22, unit23, unit24};
    team_t team1 = create_team(team1_units, "Funny Bois", 1);
    printf("Team 1 size: %zu\n", team1.size);
    team_t team2 = create_team(team2_units, "Speedy Bois", 2);
    printf("Team 2 size: %zu\n", team2.size);
    print_team(team1);
    print_team(team2);

    return 0;
}