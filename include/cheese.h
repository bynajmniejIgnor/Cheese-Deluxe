#ifndef CHEESE_H
#define CHEESE_H

#include <vector>
#include <array>
#include <memory>
#include <iostream>

namespace cheese
{

    typedef struct
    {
        int index;
        std::vector<int> connections;
        std::array<int, 3> location;
        bool not_removable;

        void info();
    } CheeseNode;

    std::shared_ptr<CheeseNode> MakeCheeseNode(int idx, std::vector<int> &connections, std::array<int, 3> &location, bool not_rebovable);
    void test();
}

#endif