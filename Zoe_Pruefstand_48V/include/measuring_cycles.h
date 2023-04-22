#include <stdint.h>

struct measuring_cycle_1{
    uint16_t time[18]; 
    uint16_t torque[6]; 
    uint16_t speed[5];
};

struct measuring_cycle_1 steps_cycle = {
    .time = {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90},
    .torque = {0,2,4,6,8,10},
    .speed = {100,200,300,400,500}
};