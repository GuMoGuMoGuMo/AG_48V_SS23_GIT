#include <stdint.h>
// Data structure for a table entry
struct measuring_cycle {
    uint16_t time;       // Time in seconds
    uint16_t rpm;        // Revolutions per minute (rpm)
    uint16_t torque;     // Torque in Newton-meters (Nm)
};

#define MEASURING_CYCLE_TABLE_SIZE 37
struct measuring_cycle measuring_cycle_1[MEASURING_CYCLE_TABLE_SIZE] = {
    {0, 0, 0},
    {5, 0, 2},
    {10, 0, 4},
    {15, 0, 6},
    {20, 0, 8},
    {25, 0, 10},
    {30, 100, 0},
    {35, 100, 2},
    {40, 100, 4},
    {45, 100, 6},
    {50, 100, 8},
    {55, 100, 10},
    {60, 200, 0},
    {65, 200, 2},
    {70, 200, 4},
    {75, 200, 6},
    {80, 200, 8},
    {85, 200, 10},
    {90, 300, 0},
    {95, 300, 2},
    {100, 300, 4},
    {105, 300, 6},
    {110, 300, 8},
    {115, 300, 10},
    {120, 400, 0},
    {125, 400, 2},
    {130, 400, 4},
    {135, 400, 6},
    {140, 400, 8},
    {145, 400, 10},
    {150, 500, 0},
    {155, 500, 2},
    {160, 500, 4},
    {165, 500, 6},
    {170, 500, 8},
    {175, 500, 10},
    {0, 0, 0},
};
