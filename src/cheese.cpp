#include "cheese.h"

namespace cheese
{
    std::shared_ptr<CheeseNode> MakeCheeseNode(int idx, std::vector<int> &connections, std::array<int, 3> &location, bool not_rebovable)
    {
        auto particle = std::make_shared<cheese::CheeseNode>();
        particle->index = idx;
        particle->connections = connections;
        particle->location = location;
        particle->not_removable = not_rebovable;

        return particle;
    }

    void CheeseNode::info()
    {
        std::cout << "Node raport:" << std::endl;
        std::cout << "Index: " << index << std::endl;
        std::cout << "Connections: ";
        for (const auto &conn : connections) {
            std::cout << conn << ", ";
        }

        std::cout << std::endl;
        std::cout << "Location: " << location[0] << ", " << location[1] << ", " << location[2] << std::endl;
        std::cout << "Not removeable: " << not_removable << std::endl;
    }

    void test()
    {
        std::vector<int> connections;

        connections.push_back(13);
        connections.push_back(14);
        connections.push_back(15);
        std::array<int, 3> location{1,2,3};

        std::shared_ptr<CheeseNode> bit = MakeCheeseNode(1, connections, location, false);
        bit -> info();
    }
}
