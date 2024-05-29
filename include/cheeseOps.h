#ifndef CHEESEOPS_H
#define CHEESEOPS_H
#include "cheese.h"

#define LEFT 0
#define RIGHT 1
#define TOP 2
#define DOWN 3
#define BACK 4
#define FRONT 5

namespace cheeseOps {
    typedef struct {
        std::array<std::vector<int>, 6> wallBounds; //[left, right, top, down, back, front]
        bool verify(std::shared_ptr<cheese::Cheese> cheese);
    }CheeseKeeper;

    std::shared_ptr<CheeseKeeper> EducateCheeseKeeper(std::shared_ptr<cheese::Cheese> cheese);

}

#endif