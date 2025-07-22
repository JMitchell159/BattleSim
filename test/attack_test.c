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
    weapon_t katana = create_weapon(KATANA, SLASHING, 1, 3, BLEED, 10, 0.1);
    weapon_t dagger = create_weapon(DAGGER, PIERCING, 2, 2, POISON, 2, 0.12);
    weapon_t shield = create_weapon(SHIELD, BLUNT, 1, 1, BLOCK, 0, 0.15);
    unit_t unit1 = create_unit(katana, dagger, 1, 50, 5, 0.0, 0.1);
    unit_t unit2 = create_unit(dagger, shield, 2, 50, 5, 0.0, 0.1);
    printf("Before Attack:\n");
    printf("Health: %d\n", unit2.health);
    printf("Bleed Percent: %.2f\n", unit2.bleed_percent);
    printf("Poison Percent: %.2f\n", unit2.poison_percent);
    unit2 = attack(unit1, true, unit2);
    printf("After Katana:\n");
    printf("Health: %d\n", unit2.health);
    printf("Bleed Percent: %.2f\n", unit2.bleed_percent);
    printf("Poison Percent: %.2f\n", unit2.poison_percent);
    unit2 = attack(unit1, false, unit2);
    printf("After Dagger:\n");
    printf("Health: %d\n", unit2.health);
    printf("Bleed Percent: %.2f\n", unit2.bleed_percent);
    printf("Poison Percent: %.2f\n", unit2.poison_percent);

    return 0;
}