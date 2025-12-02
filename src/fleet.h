#ifndef FLEET_H
#define FLEET_H

#include "board.h"

#define MAX_SHIPS 6 

typedef struct {
    char name[20];
    int length;
    int hits;
    bool placed;
    bool sunk;  
} Ship;

typedef struct {
    Ship ships[MAX_SHIPS];
    int count;
} Fleet;

void initialize_fleet(Fleet* fleet);
Ship* get_ship_by_id(Fleet* fleet, int ship_id);
bool is_fleet_sunk(const Fleet* fleet);

#endif // FLEET_H
