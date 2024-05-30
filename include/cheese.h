#ifndef CHEESE_H
#define CHEESE_H

#include "main.h"

namespace cheese {
    typedef struct {
        int index;
        std::vector<int> connections;
        std::array<int, 3> location;
        bool visited;

        void info();
    } CheeseBall;

    std::shared_ptr<CheeseBall> MakeCheeseNode(int idx, std::vector<int> connections, std::array<int, 3> location);

    typedef struct {
        std::vector<std::shared_ptr<CheeseBall>> cheeseBalls;
        int width;
        int length;
        int height;
        int sliceArea;

        void info();
        void bindSlices();
        void stackSlices();
        void solidifyCheese();
        void ageTheCheese();
    } Cheese;

    Cheese MakeCheese(int width, int length, int height);
}

#endif