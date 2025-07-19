#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "team.h"
#include "team.c"
#include "weapon.h"
#include "weapon.c"

int main() {
    weapon_t katana = create_weapon(KATANA, SLASHING, 1, 4, BLEED, 72, 0.15);
    weapon_t dagger = create_weapon(DAGGER, PIERCING, 1, 1, POISON, 1, 0.2);
    combatant_t unit1 = create_unit(katana, dagger, 1, 50, 5, 0, 0);
    combatant_t unit2 = create_unit(katana, dagger, 2, 50, 5, 0, 0);
    printf("Before Attack\n");
    printf("Health: %d\n", unit2.health);
    printf("Poison Percent: %f\n", unit2.poison_percent);
    printf("Bleed Percent: %f\n", unit2.bleed_percent);
    unit2 = attack(unit1, true, unit2);
    printf("After Katana:\n");
    printf("Health: %d\n", unit2.health);
    printf("Poison Percent: %f\n", unit2.poison_percent);
    printf("Bleed Percent: %f\n", unit2.bleed_percent);
    unit2 = attack(unit1, false, unit2);
    printf("After Dagger:\n");
    printf("Health: %d\n", unit2.health);
    printf("Poison Percent: %f\n", unit2.poison_percent);
    printf("Bleed Percent: %f\n", unit2.bleed_percent);

    return 0;
}