#include <stdint.h>

struct measuring_cycle_1{
    uint16_t time[30]; 
    uint16_t torque[6]; 
    uint16_t speed[5];
    int size_time;
    int size_torque;
    int size_speed;
}; 

struct measuring_cycle_1 steps_cycle = {
    .time = {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150},
    .torque = {0,2,4,6,8,10},
    .speed = {100,200,300,400,500},
    .size_time = 30,
    .size_torque = 6,
    .size_speed = 5,
};