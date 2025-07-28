#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "/home/joemi/workspace/github.com/JMitchell159/BattleSim/team.h"
#include "/home/joemi/workspace/github.com/JMitchell159/BattleSim/team.c"
#include "/home/joemi/workspace/github.com/JMitchell159/BattleSim/weapon.h"
#include "/home/joemi/workspace/github.com/JMitchell159/BattleSim/weapon.c"

#define WEAPONS 90
#define ALLOWED 10

int main() {
    FILE *allowed;
    FILE *weapons;
    char allowed_row[ALLOWED];
    char weapons_row[WEAPONS];
    weapon_t weapon_list[30];
    char *token;

    allowed = fopen("config/allowed_weapons.txt", "r");
    weapons = fopen("config/weapons.csv", "r");

    int i = 0;

    // Remove header
    fgets(weapons_row, WEAPONS, weapons);

    while(!feof(allowed)) {
        fgets(allowed_row, ALLOWED, allowed);
        while(!feof(weapons)) {
            fgets(weapons_row, WEAPONS, weapons);
            token = strtok(weapons_row, ",");
            if(strncmp(allowed_row, token, strlen(token)) < 0) return 1;
            if(strncmp(allowed_row, token, strlen(token)) == 0) {
                // pulls weapon_type
                token = strtok(NULL, ",");
                switch(strcmp(token, "AXE")) {
                    case 0:
                        weapon_list[i].weapon_type = AXE;
                        break;
                    case 2:
                        weapon_list[i].weapon_type = CLUB;
                        break;
                    case 3:
                        weapon_list[i].weapon_type = DAGGER;
                        break;
                    case 5:
                        weapon_list[i].weapon_type = FIST;
                        break;
                    case 7:
                        weapon_list[i].weapon_type = HAMMER;
                        break;
                    case 10:
                        weapon_list[i].weapon_type = KATANA;
                        break;
                    case 12:
                        weapon_list[i].weapon_type = MACE;
                        break;
                    case 18:
                        switch(strcmp(token, "SHIELD")) {
                            case 0:
                                weapon_list[i].weapon_type = SHIELD;
                                break;
                            case 8:
                                weapon_list[i].weapon_type = SPEAR;
                                break;
                            case 15:
                                weapon_list[i].weapon_type = SWORD;
                                break;
                        }
                }

                // pulls damage_type
                token = strtok(NULL, ",");
                switch(strcmp(token, "BLUNT")) {
                    case 0:
                        weapon_list[i].damage_type = BLUNT;
                        break;
                    case 14:
                        weapon_list[i].damage_type = PIERCING;
                        break;
                    case 17:
                        weapon_list[i].damage_type = SLASHING;
                        break;
                }

                // pulls num_attacks
                token = strtok(NULL, ",");
                weapon_list[i].num_attacks = atoi(token);

                // pulls damage
                token = strtok(NULL, ",");
                weapon_list[i].damage = atoi(token);

                // pulls effect_type
                token = strtok(NULL, ",");
                switch(strcmp(token, "BLEED")) {
                    case 0:
                        weapon_list[i].effect_type = BLEED;
                        break;
                    case 10:
                        weapon_list[i].effect_type = BLOCK;
                        break;
                    case 14:
                        weapon_list[i].effect_type = POISON;
                        break;
                    case 17:
                        weapon_list[i].effect_type = STUN;
                        break;
                    default:
                        weapon_list[i].effect_type = NONE;
                        break;
                }

                // pulls effect_damage
                token = strtok(NULL, ",");
                weapon_list[i].effect_damage = atoi(token);

                // pulls effect_percent
                token = strtok(NULL, ",");
                weapon_list[i].effect_percent = atof(token);

                i++;
            }
            break;
        }
    }

    unit_t team1_units[4];
    unit_t team2_units[4];

    int choice = 0;
    int shield_idx = -1;
    for(int i = 0; i < 10; i++) {
        if(weapon_list[i].weapon_type < SHIELD) {
            printf("====================\n");
            printf("Choice #%d\n", i + 1);
            print_weapon(weapon_list[i]);
            printf("=====================\n");
        } else if (weapon_list[i].weapon_type > SHIELD) {
            printf("=====================\n");
            printf("Choice #%d\n", i);
            print_weapon(weapon_list[i]);
            printf("=====================\n");
        } else shield_idx = i;
    }

    printf("Team 1, Choose Unit 1's Primary Weapon (Enter a number):");
    scanf("%d", &choice);
    while(choice < 1 || choice > 9) {
        printf("Please choose a valid option:");
        scanf("%d", &choice);
    }

    weapon_t primary;
    if(weapon_list[choice].weapon_type <= SHIELD) primary = create_weapon(
        weapon_list[choice - 1].weapon_type,
        weapon_list[choice - 1].damage_type,
        weapon_list[choice - 1].num_attacks,
        weapon_list[choice - 1].damage,
        weapon_list[choice - 1].effect_type,
        weapon_list[choice - 1].effect_damage,
        weapon_list[choice - 1].effect_percent
    );
    else primary = create_weapon(
        weapon_list[choice].weapon_type,
        weapon_list[choice].damage_type,
        weapon_list[choice].num_attacks,
        weapon_list[choice].damage,
        weapon_list[choice].effect_type,
        weapon_list[choice].effect_damage,
        weapon_list[choice].effect_percent
    );

    printf("=====================\n");
    printf("Choice #10\n");
    print_weapon(weapon_list[shield_idx]);
    printf("=====================\n");

    printf("Team 1, Choose Unit 1's Secondary Weapon (Enter a number):");
    scanf("%d", &choice);
    while(choice < 1 || choice > 10) {
        printf("Please choose a valid option:");
        scanf("%d", &choice);
    }

    weapon_t secondary;
    if(choice == 10) secondary = create_weapon(
        weapon_list[shield_idx].weapon_type,
        weapon_list[shield_idx].damage_type,
        weapon_list[shield_idx].num_attacks,
        weapon_list[shield_idx].damage,
        weapon_list[shield_idx].effect_type,
        weapon_list[shield_idx].effect_damage,
        weapon_list[shield_idx].effect_percent
    );
    else if(weapon_list[choice].weapon_type <= SHIELD) secondary = create_weapon(
        weapon_list[choice - 1].weapon_type,
        weapon_list[choice - 1].damage_type,
        weapon_list[choice - 1].num_attacks,
        weapon_list[choice - 1].damage,
        weapon_list[choice - 1].effect_type,
        weapon_list[choice - 1].effect_damage,
        weapon_list[choice - 1].effect_percent
    );
    else secondary = create_weapon(
        weapon_list[choice].weapon_type,
        weapon_list[choice].damage_type,
        weapon_list[choice].num_attacks,
        weapon_list[choice].damage,
        weapon_list[choice].effect_type,
        weapon_list[choice].effect_damage,
        weapon_list[choice].effect_percent
    );

    team1_units[0] = create_unit(primary, secondary, 1, 50, 5, 0.0, 0.15);

    for(int i = 1; i < 4; i++) {
        printf("Unit %d Primary:", i + 1);
        scanf("%d", &choice);
        while(choice < 1 || choice > 9) {
            printf("Please choose a valid option:");
            scanf("%d", &choice);
        }

        weapon_t primary;
        if(weapon_list[choice].weapon_type <= SHIELD) primary = create_weapon(
            weapon_list[choice - 1].weapon_type,
            weapon_list[choice - 1].damage_type,
            weapon_list[choice - 1].num_attacks,
            weapon_list[choice - 1].damage,
            weapon_list[choice - 1].effect_type,
            weapon_list[choice - 1].effect_damage,
            weapon_list[choice - 1].effect_percent
        );
        else primary = create_weapon(
            weapon_list[choice].weapon_type,
            weapon_list[choice].damage_type,
            weapon_list[choice].num_attacks,
            weapon_list[choice].damage,
            weapon_list[choice].effect_type,
            weapon_list[choice].effect_damage,
            weapon_list[choice].effect_percent
        );

        printf("Unit %d Secondary:", i + 1);
        scanf("%d", &choice);
        while(choice < 1 || choice > 10) {
            printf("Please choose a valid option:");
            scanf("%d", &choice);
        }

        weapon_t secondary;
        if(choice == 10) secondary = create_weapon(
            weapon_list[shield_idx].weapon_type,
            weapon_list[shield_idx].damage_type,
            weapon_list[shield_idx].num_attacks,
            weapon_list[shield_idx].damage,
            weapon_list[shield_idx].effect_type,
            weapon_list[shield_idx].effect_damage,
            weapon_list[shield_idx].effect_percent
        );
        else if(weapon_list[choice].weapon_type <= SHIELD) secondary = create_weapon(
            weapon_list[choice - 1].weapon_type,
            weapon_list[choice - 1].damage_type,
            weapon_list[choice - 1].num_attacks,
            weapon_list[choice - 1].damage,
            weapon_list[choice - 1].effect_type,
            weapon_list[choice - 1].effect_damage,
            weapon_list[choice - 1].effect_percent
        );
        else secondary = create_weapon(
            weapon_list[choice].weapon_type,
            weapon_list[choice].damage_type,
            weapon_list[choice].num_attacks,
            weapon_list[choice].damage,
            weapon_list[choice].effect_type,
            weapon_list[choice].effect_damage,
            weapon_list[choice].effect_percent
        );

        team1_units[i] = create_unit(primary, secondary, 1, 50, 5, 0.0, 0.15);
    }

    choice = 0;
    shield_idx = -1;
    for(int i = 0; i < 10; i++) {
        if(weapon_list[i].weapon_type < SHIELD) {
            printf("====================\n");
            printf("Choice #%d\n", i + 1);
            print_weapon(weapon_list[i]);
            printf("=====================\n");
        } else if (weapon_list[i].weapon_type > SHIELD) {
            printf("=====================\n");
            printf("Choice #%d\n", i);
            print_weapon(weapon_list[i]);
            printf("=====================\n");
        } else shield_idx = i;
    }

    printf("Team 2, Choose Unit 1's Primary Weapon (Enter a number):");
    scanf("%d", &choice);
    while(choice < 1 || choice > 9) {
        printf("Please choose a valid option:");
        scanf("%d", &choice);
    }

    if(weapon_list[choice].weapon_type <= SHIELD) primary = create_weapon(
        weapon_list[choice - 1].weapon_type,
        weapon_list[choice - 1].damage_type,
        weapon_list[choice - 1].num_attacks,
        weapon_list[choice - 1].damage,
        weapon_list[choice - 1].effect_type,
        weapon_list[choice - 1].effect_damage,
        weapon_list[choice - 1].effect_percent
    );
    else primary = create_weapon(
        weapon_list[choice].weapon_type,
        weapon_list[choice].damage_type,
        weapon_list[choice].num_attacks,
        weapon_list[choice].damage,
        weapon_list[choice].effect_type,
        weapon_list[choice].effect_damage,
        weapon_list[choice].effect_percent
    );

    printf("=====================\n");
    printf("Choice #10\n");
    print_weapon(weapon_list[shield_idx]);
    printf("=====================\n");

    printf("Team 2, Choose Unit 1's Secondary Weapon (Enter a number):");
    scanf("%d", &choice);
    while(choice < 1 || choice > 10) {
        printf("Please choose a valid option:");
        scanf("%d", &choice);
    }

    if(choice == 10) secondary = create_weapon(
        weapon_list[shield_idx].weapon_type,
        weapon_list[shield_idx].damage_type,
        weapon_list[shield_idx].num_attacks,
        weapon_list[shield_idx].damage,
        weapon_list[shield_idx].effect_type,
        weapon_list[shield_idx].effect_damage,
        weapon_list[shield_idx].effect_percent
    );
    else if(weapon_list[choice].weapon_type <= SHIELD) secondary = create_weapon(
        weapon_list[choice - 1].weapon_type,
        weapon_list[choice - 1].damage_type,
        weapon_list[choice - 1].num_attacks,
        weapon_list[choice - 1].damage,
        weapon_list[choice - 1].effect_type,
        weapon_list[choice - 1].effect_damage,
        weapon_list[choice - 1].effect_percent
    );
    else secondary = create_weapon(
        weapon_list[choice].weapon_type,
        weapon_list[choice].damage_type,
        weapon_list[choice].num_attacks,
        weapon_list[choice].damage,
        weapon_list[choice].effect_type,
        weapon_list[choice].effect_damage,
        weapon_list[choice].effect_percent
    );

    team2_units[0] = create_unit(primary, secondary, 1, 50, 5, 0.0, 0.15);

    for(int i = 1; i < 4; i++) {
        printf("Unit %d Primary:", i + 1);
        scanf("%d", &choice);
        while(choice < 1 || choice > 9) {
            printf("Please choose a valid option:");
            scanf("%d", &choice);
        }

        weapon_t primary;
        if(weapon_list[choice].weapon_type <= SHIELD) primary = create_weapon(
            weapon_list[choice - 1].weapon_type,
            weapon_list[choice - 1].damage_type,
            weapon_list[choice - 1].num_attacks,
            weapon_list[choice - 1].damage,
            weapon_list[choice - 1].effect_type,
            weapon_list[choice - 1].effect_damage,
            weapon_list[choice - 1].effect_percent
        );
        else primary = create_weapon(
            weapon_list[choice].weapon_type,
            weapon_list[choice].damage_type,
            weapon_list[choice].num_attacks,
            weapon_list[choice].damage,
            weapon_list[choice].effect_type,
            weapon_list[choice].effect_damage,
            weapon_list[choice].effect_percent
        );

        printf("Unit %d Secondary:", i + 1);
        scanf("%d", &choice);
        while(choice < 1 || choice > 10) {
            printf("Please choose a valid option:");
            scanf("%d", &choice);
        }

        weapon_t secondary;
        if(choice == 10) secondary = create_weapon(
            weapon_list[shield_idx].weapon_type,
            weapon_list[shield_idx].damage_type,
            weapon_list[shield_idx].num_attacks,
            weapon_list[shield_idx].damage,
            weapon_list[shield_idx].effect_type,
            weapon_list[shield_idx].effect_damage,
            weapon_list[shield_idx].effect_percent
        );
        else if(weapon_list[choice].weapon_type <= SHIELD) secondary = create_weapon(
            weapon_list[choice - 1].weapon_type,
            weapon_list[choice - 1].damage_type,
            weapon_list[choice - 1].num_attacks,
            weapon_list[choice - 1].damage,
            weapon_list[choice - 1].effect_type,
            weapon_list[choice - 1].effect_damage,
            weapon_list[choice - 1].effect_percent
        );
        else secondary = create_weapon(
            weapon_list[choice].weapon_type,
            weapon_list[choice].damage_type,
            weapon_list[choice].num_attacks,
            weapon_list[choice].damage,
            weapon_list[choice].effect_type,
            weapon_list[choice].effect_damage,
            weapon_list[choice].effect_percent
        );

        team2_units[i] = create_unit(primary, secondary, 1, 50, 5, 0.0, 0.15);
    }

    team_t team1 = create_team(team1_units, "Team 1", 4, 1);
    team_t team2 = create_team(team2_units, "Team 2", 4, 2);

    int coin = rand() % 2;
    if(coin) {
        int round = 0;
        while(true) {
            round++;
            printf("Round %d\n", round);
            print_team(team1);
            print_team(team2);
            for(int i = 0; i < team1.size; i++) {
                unit_t curr = team1.units[i];
                if(curr.stun_instances) {
                    printf("%s Unit %d stunned", team1.name, i + 1);
                    team1.units[i].stun_instances--;
                }
                else if(curr.health > 0) {
                    if(curr.secondary.weapon_type == SHIELD || curr.secondary.weapon_type == FIST) {
                        for(int j = 0; j < curr.primary.num_attacks; j++) {
                            bool found = false;
                            bool wrap_around = false;
                            int atk_idx = i - 1;
                            while(!found) {
                                atk_idx++;
                                if(atk_idx == i && wrap_around) {
                                    printf("%s has won the battle.", team1.name);
                                    return 0;
                                }
                                if(atk_idx == team2.size) {
                                    atk_idx -= team2.size;
                                    wrap_around = true;
                                }
                                found = team2.units[atk_idx].health > 0;
                            }
                            printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                            team2.units[atk_idx] = attack(curr, true, team2.units[atk_idx]);
                        }
                    } else if(curr.primary.effect_type == STUN) {
                        bool found = false;
                        bool wrap_around = false;
                        int atk_idx = i - 1;
                        while(!found) {
                            atk_idx++;
                            if(atk_idx == i && wrap_around) {
                                printf("%s has won the battle.", team1.name);
                                return 0;
                            }
                            if(atk_idx == team2.size) {
                                atk_idx -= team2.size;
                                wrap_around = true;
                            }
                            found = team2.units[atk_idx].health > 0;
                        }
                        int prim_stun = (int)((1.0 - team2.units[atk_idx].stun_percent) / curr.primary.effect_percent) + 1;
                        int prim_kill = (int)(team2.units[atk_idx].health / curr.primary.damage) + 1;
                        int sec_kill = (int)(team2.units[atk_idx].health / (curr.secondary.damage * curr.secondary.num_attacks)) + 1;
                        if(prim_stun < sec_kill || prim_kill < sec_kill) {
                            printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                            team2.units[atk_idx] = attack(curr, true, team2.units[atk_idx]);
                        }
                        else {
                            team2.units[atk_idx] = attack(curr, false, team2.units[atk_idx]);
                            if(curr.secondary.num_attacks == 2 && team2.units[atk_idx].health > 0) {
                                printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                                team2.units[atk_idx] = attack(curr, false, team2.units[atk_idx]);
                            }
                            else if (curr.secondary.num_attacks == 2) {
                                found = false;
                                while(!found) {
                                    atk_idx++;
                                    if(atk_idx == i && wrap_around) {
                                        printf("%s has won the battle.", team1.name);
                                        return 0;
                                    }
                                    if(atk_idx == team2.size) {
                                        atk_idx -= team2.size;
                                        wrap_around = true;
                                    }
                                    found = team2.units[atk_idx].health > 0;
                                }
                                printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                                team2.units[atk_idx] = attack(curr, false, team2.units[atk_idx]);
                            }
                        }
                    } else if(curr.primary.effect_type == BLEED) {
                        bool found = false;
                        bool wrap_around = false;
                        int atk_idx = i - 1;
                        while(!found) {
                            atk_idx++;
                            if(atk_idx == i && wrap_around) {
                                printf("%s has won the battle.", team1.name);
                                return 0;
                            }
                            if(atk_idx == team2.size) {
                                atk_idx -= team2.size;
                                wrap_around = true;
                            }
                            found = team2.units[atk_idx].health > 0;
                        }
                        int prim_bleed = (int)((1.0 - team2.units[atk_idx].bleed_percent) / curr.primary.effect_percent) + 1;
                        int prim_kill = (int)(team2.units[atk_idx].health / curr.primary.damage) + 1;
                        int sec_kill = (int)(team2.units[atk_idx].health / (curr.secondary.damage * curr.secondary.num_attacks)) + 1;
                        if(prim_bleed < sec_kill || prim_kill < sec_kill) {
                            printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                            team2.units[atk_idx] = attack(curr, true, team2.units[atk_idx]);
                        }
                        else {
                            printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                            team2.units[atk_idx] = attack(curr, false, team2.units[atk_idx]);
                            if(curr.secondary.num_attacks == 2 && team2.units[atk_idx].health > 0) {
                                printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                                team2.units[atk_idx] = attack(curr, false, team2.units[atk_idx]);
                            }
                            else if (curr.secondary.num_attacks == 2) {
                                found = false;
                                while(!found) {
                                    atk_idx++;
                                    if(atk_idx == i && wrap_around) {
                                        printf("%s has won the battle.", team1.name);
                                        return 0;
                                    }
                                    if(atk_idx == team2.size) {
                                        atk_idx -= team2.size;
                                        wrap_around = true;
                                    }
                                    found = team2.units[atk_idx].health > 0;
                                }
                                printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                                team2.units[atk_idx] = attack(curr, false, team2.units[atk_idx]);
                            }
                        }
                    } else if(curr.primary.effect_type == POISON) {
                        bool found = false;
                        int found_idx = -1;
                        bool perfect = false;
                        bool wrap_around = false;
                        int atk_idx = i - 1;
                        while(!found && !perfect) {
                            atk_idx++;
                            if(atk_idx == i && wrap_around && found_idx == -1) {
                                printf("%s has won the battle.", team1.name);
                                return 0;
                            } else if (atk_idx == i && wrap_around) {
                                perfect = false;
                                atk_idx = found_idx;
                                break;
                            }
                            if(atk_idx == team2.size) {
                                atk_idx -= team2.size;
                                wrap_around = true;
                            }
                            found = team2.units[atk_idx].health > 0;
                            if(found & found_idx == -1) found_idx = atk_idx;
                            perfect = team2.units[atk_idx].poison_percent > 0.84;
                        }
                        if(perfect) {
                            printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                            team2.units[atk_idx] = attack(curr, true, team2.units[atk_idx]);
                            if(team2.units[atk_idx].poison_percent > 0.84) {
                                perfect = false;
                                wrap_around = false;
                                int og_atk_idx = atk_idx - 1;
                                while(!found && !perfect) {
                                    atk_idx++;
                                    if(atk_idx == og_atk_idx && wrap_around && found_idx == -1) {
                                        printf("%s has won the battle.", team1.name);
                                        return 0;
                                    } else if (atk_idx == i && wrap_around) {
                                        perfect = false;
                                        atk_idx = found_idx;
                                        break;
                                    }
                                    if(atk_idx == team2.size) {
                                        atk_idx -= team2.size;
                                        wrap_around = true;
                                    }
                                    found = team2.units[atk_idx].health > 0;
                                    if(found & found_idx == -1) found_idx = atk_idx;
                                    perfect = team2.units[atk_idx].poison_percent > 0.84;
                                }
                                printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                                team2.units[atk_idx] = attack(curr, true, team2.units[atk_idx]);
                            } else {
                                printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                                team2.units[atk_idx] = attack(curr, true, team2.units[atk_idx]);
                            }
                        } else {
                            printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                            team2.units[atk_idx] = attack(curr, false, team2.units[atk_idx]);
                            if(team2.units[atk_idx].health <= 0 && curr.secondary.num_attacks == 2) {
                                found = false;
                                wrap_around = false;
                                atk_idx = i - 1;
                                while(!found) {
                                    atk_idx++;
                                    if(atk_idx == i && wrap_around) {
                                        printf("%s has won the battle.", team1.name);
                                        return 0;
                                    }
                                    if(atk_idx == team2.size) {
                                        atk_idx -= team2.size;
                                        wrap_around = true;
                                    }
                                    found = team2.units[atk_idx].health > 0;
                                }
                                printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                                team2.units[atk_idx] = attack(curr, false, team2.units[atk_idx]);
                            } else if(curr.secondary.num_attacks == 2) {
                                printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                                team2.units[atk_idx] = attack(curr, false, team2.units[atk_idx]);
                            }
                        }
                    } else if(curr.primary.weapon_type == FIST) {
                        for(int j = 0; j < curr.secondary.num_attacks; j++) {
                            bool found = false;
                            bool wrap_around = false;
                            int atk_idx = i - 1;
                            while(!found) {
                                atk_idx++;
                                if(atk_idx == i && wrap_around) {
                                    printf("%s has won the battle.", team1.name);
                                    return 0;
                                }
                                if(atk_idx == team2.size) {
                                    atk_idx -= team2.size;
                                    wrap_around = true;
                                }
                                found = team2.units[atk_idx].health > 0;
                            }
                            printf("%s Unit %d attacks %s Unit %d\n", team1.name, i + 1, team2.name, atk_idx + 1);
                            team2.units[atk_idx] = attack(curr, true, team2.units[atk_idx]);
                        }
                    }
                    team1.units[i] = end_of_turn(curr);
                } else team1.units[i].health = 0;
            }
            for(int i = 0; i < team2.size; i++) {
                unit_t curr = team2.units[i];
                if(curr.stun_instances) {
                    printf("%s Unit %d stunned", team2.name, i + 1);
                    team2.units[i].stun_instances--;
                }
                else if(curr.health > 0) {
                    if(curr.secondary.weapon_type == SHIELD || curr.secondary.weapon_type == FIST) {
                        for(int j = 0; j < curr.primary.num_attacks; j++) {
                            bool found = false;
                            bool wrap_around = false;
                            int atk_idx = i - 1;
                            while(!found) {
                                atk_idx++;
                                if(atk_idx == i && wrap_around) {
                                    printf("%s has won the battle.", team2.name);
                                    return 0;
                                }
                                if(atk_idx == team1.size) {
                                    atk_idx -= team1.size;
                                    wrap_around = true;
                                }
                                found = team1.units[atk_idx].health > 0;
                            }
                            printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                            team1.units[atk_idx] = attack(curr, true, team1.units[atk_idx]);
                        }
                    } else if(curr.primary.effect_type == STUN) {
                        bool found = false;
                        bool wrap_around = false;
                        int atk_idx = i - 1;
                        while(!found) {
                            atk_idx++;
                            if(atk_idx == i && wrap_around) {
                                printf("%s has won the battle.", team2.name);
                                return 0;
                            }
                            if(atk_idx == team1.size) {
                                atk_idx -= team1.size;
                                wrap_around = true;
                            }
                            found = team1.units[atk_idx].health > 0;
                        }
                        int prim_stun = (int)((1.0 - team1.units[atk_idx].stun_percent) / curr.primary.effect_percent) + 1;
                        int prim_kill = (int)(team1.units[atk_idx].health / curr.primary.damage) + 1;
                        int sec_kill = (int)(team1.units[atk_idx].health / (curr.secondary.damage * curr.secondary.num_attacks)) + 1;
                        if(prim_stun < sec_kill || prim_kill < sec_kill) {
                            printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                            team1.units[atk_idx] = attack(curr, true, team1.units[atk_idx]);
                        }
                        else {
                            printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                            team1.units[atk_idx] = attack(curr, false, team1.units[atk_idx]);
                            if(curr.secondary.num_attacks == 2 && team1.units[atk_idx].health > 0) {
                                printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                                team1.units[atk_idx] = attack(curr, false, team1.units[atk_idx]);
                            }
                            else if (curr.secondary.num_attacks == 2) {
                                found = false;
                                while(!found) {
                                    atk_idx++;
                                    if(atk_idx == i && wrap_around) {
                                        printf("%s has won the battle.", team2.name);
                                        return 0;
                                    }
                                    if(atk_idx == team1.size) {
                                        atk_idx -= team1.size;
                                        wrap_around = true;
                                    }
                                    found = team1.units[atk_idx].health > 0;
                                }
                                printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                                team1.units[atk_idx] = attack(curr, false, team1.units[atk_idx]);
                            }
                        }
                    } else if(curr.primary.effect_type == BLEED) {
                        bool found = false;
                        bool wrap_around = false;
                        int atk_idx = i - 1;
                        while(!found) {
                            atk_idx++;
                            if(atk_idx == i && wrap_around) {
                                printf("%s has won the battle.", team2.name);
                                return 0;
                            }
                            if(atk_idx == team1.size) {
                                atk_idx -= team1.size;
                                wrap_around = true;
                            }
                            found = team1.units[atk_idx].health > 0;
                        }
                        int prim_bleed = (int)((1.0 - team1.units[atk_idx].bleed_percent) / curr.primary.effect_percent) + 1;
                        int prim_kill = (int)(team1.units[atk_idx].health / curr.primary.damage) + 1;
                        int sec_kill = (int)(team1.units[atk_idx].health / (curr.secondary.damage * curr.secondary.num_attacks)) + 1;
                        if(prim_bleed < sec_kill || prim_kill < sec_kill) {
                            printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                            team1.units[atk_idx] = attack(curr, true, team1.units[atk_idx]);
                        }
                        else {
                            team1.units[atk_idx] = attack(curr, false, team1.units[atk_idx]);
                            if(curr.secondary.num_attacks == 2 && team1.units[atk_idx].health > 0) {
                                printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                                team1.units[atk_idx] = attack(curr, false, team1.units[atk_idx]);
                            }
                            else if (curr.secondary.num_attacks == 2) {
                                found = false;
                                while(!found) {
                                    atk_idx++;
                                    if(atk_idx == i && wrap_around) {
                                        printf("%s has won the battle.", team2.name);
                                        return 0;
                                    }
                                    if(atk_idx == team1.size) {
                                        atk_idx -= team1.size;
                                        wrap_around = true;
                                    }
                                    found = team1.units[atk_idx].health > 0;
                                }
                                printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                                team1.units[atk_idx] = attack(curr, false, team1.units[atk_idx]);
                            }
                        }
                    } else if(curr.primary.effect_type == POISON) {
                        bool found = false;
                        int found_idx = -1;
                        bool perfect = false;
                        bool wrap_around = false;
                        int atk_idx = i - 1;
                        while(!found && !perfect) {
                            atk_idx++;
                            if(atk_idx == i && wrap_around && found_idx == -1) {
                                printf("%s has won the battle.", team2.name);
                                return 0;
                            } else if (atk_idx == i && wrap_around) {
                                perfect = false;
                                atk_idx = found_idx;
                                break;
                            }
                            if(atk_idx == team1.size) {
                                atk_idx -= team1.size;
                                wrap_around = true;
                            }
                            found = team1.units[atk_idx].health > 0;
                            if(found & found_idx == -1) found_idx = atk_idx;
                            perfect = team1.units[atk_idx].poison_percent > 0.84;
                        }
                        if(perfect) {
                            printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                            team1.units[atk_idx] = attack(curr, true, team1.units[atk_idx]);
                            if(team1.units[atk_idx].poison_percent > 0.84) {
                                perfect = false;
                                wrap_around = false;
                                int og_atk_idx = atk_idx - 1;
                                while(!found && !perfect) {
                                    atk_idx++;
                                    if(atk_idx == og_atk_idx && wrap_around && found_idx == -1) {
                                        printf("%s has won the battle.", team2.name);
                                        return 0;
                                    } else if (atk_idx == i && wrap_around) {
                                        perfect = false;
                                        atk_idx = found_idx;
                                        break;
                                    }
                                    if(atk_idx == team1.size) {
                                        atk_idx -= team1.size;
                                        wrap_around = true;
                                    }
                                    found = team1.units[atk_idx].health > 0;
                                    if(found & found_idx == -1) found_idx = atk_idx;
                                    perfect = team1.units[atk_idx].poison_percent > 0.84;
                                }
                                printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                                team1.units[atk_idx] = attack(curr, true, team1.units[atk_idx]);
                            } else {
                                printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                                team1.units[atk_idx] = attack(curr, true, team1.units[atk_idx]);
                            }
                        } else {
                            team1.units[atk_idx] = attack(curr, false, team1.units[atk_idx]);
                            if(team1.units[atk_idx].health <= 0 && curr.secondary.num_attacks == 2) {
                                found = false;
                                wrap_around = false;
                                atk_idx = i - 1;
                                while(!found) {
                                    atk_idx++;
                                    if(atk_idx == i && wrap_around) {
                                        printf("%s has won the battle.", team2.name);
                                        return 0;
                                    }
                                    if(atk_idx == team1.size) {
                                        atk_idx -= team1.size;
                                        wrap_around = true;
                                    }
                                    found = team1.units[atk_idx].health > 0;
                                }
                                printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                                team1.units[atk_idx] = attack(curr, false, team1.units[atk_idx]);
                            } else if(curr.secondary.num_attacks == 2) {
                                printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                                team1.units[atk_idx] = attack(curr, false, team1.units[atk_idx]);
                            }
                        }
                    } else if(curr.primary.weapon_type == FIST) {
                        for(int j = 0; j < curr.secondary.num_attacks; j++) {
                            bool found = false;
                            bool wrap_around = false;
                            int atk_idx = i - 1;
                            while(!found) {
                                atk_idx++;
                                if(atk_idx == i && wrap_around) {
                                    printf("%s has won the battle.", team2.name);
                                    return 0;
                                }
                                if(atk_idx == team1.size) {
                                    atk_idx -= team1.size;
                                    wrap_around = true;
                                }
                                found = team1.units[atk_idx].health > 0;
                            }
                            printf("%s Unit %d attacks %s Unit %d\n", team2.name, i + 1, team1.name, atk_idx + 1);
                            team1.units[atk_idx] = attack(curr, true, team1.units[atk_idx]);
                        }
                    }
                    team2.units[i] = end_of_turn(curr);
                } else team2.units[i].health = 0;
            }
        }
    }

    return 0;
}