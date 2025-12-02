#include "fleet.h"
#include <string.h>

void initialize_fleet(Fleet* fleet) {
    fleet->count = MAX_SHIPS;
    strcpy(fleet->ships[0].name, "Porta-avioes");
    fleet->ships[0].length = 5;

    strcpy(fleet->ships[1].name, "Encouracado");
    fleet->ships[1].length = 4;

    strcpy(fleet->ships[2].name, "Cruzador 1");
    fleet->ships[2].length = 3;
    strcpy(fleet->ships[3].name, "Cruzador 2");
    fleet->ships[3].length = 3;

    strcpy(fleet->ships[4].name, "Destroyer 1");
    fleet->ships[4].length = 2;
    strcpy(fleet->ships[5].name, "Destroyer 2");
    fleet->ships[5].length = 2;

    for (int i = 0; i < fleet->count; i++) {
        fleet->ships[i].hits = 0;
        fleet->ships[i].placed = false;
        fleet->ships[i].sunk = false;
    }
}

Ship* get_ship_by_id(Fleet* fleet, int ship_id) {
    if (ship_id >= 0 && ship_id < fleet->count) {
        return &fleet->ships[ship_id];
    }
    return NULL;
}


bool is_fleet_sunk(const Fleet* fleet) {
    for (int i = 0; i < fleet->count; i++) {
        if (!fleet->ships[i].sunk) {
            return false;
        }
    }
    return true;
}
