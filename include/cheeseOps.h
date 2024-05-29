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
        bool verifyCheese(std::shared_ptr<cheese::Cheese> cheese);
        bool validateCheeseBall(std::shared_ptr<cheese::CheeseBall> cheeseball, std::shared_ptr<cheese::Cheese> cheese, size_t C1, size_t C2, size_t C3);
        int getConnectedCheeseBall(std::shared_ptr<cheese::CheeseBall> cheeseball, int avoidIdx);
        bool condition1(std::shared_ptr<cheese::CheeseBall> cheeseball, size_t C1);
        bool condition2(std::shared_ptr<cheese::CheeseBall> cheeseball, std::shared_ptr<cheese::Cheese> cheese, size_t C2);
        bool condition3(std::shared_ptr<cheese::CheeseBall> cheeseball, std::shared_ptr<cheese::Cheese> cheese, size_t C3);

    }CheeseKeeper;

    std::shared_ptr<CheeseKeeper> EducateCheeseKeeper(std::shared_ptr<cheese::Cheese> cheese);
}

#endif