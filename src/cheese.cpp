#include "cheese.h"

namespace cheese
{
    std::shared_ptr<CheeseNode> MakeCheeseNode(int idx, std::vector<int> &connections, std::array<int, 3> location, bool not_rebovable) {
        auto particle = std::make_shared<CheeseNode>();
        particle->index = idx;
        particle->connections = connections;
        particle->location = location;
        particle->not_removable = not_rebovable;

        return particle;
    }

    void CheeseNode::info() {
        std::cout << "Index: " << this->index << std::endl;
        std::cout << "Connections: ";
        for (const auto &conn : this->connections) {
            std::cout << conn << ", ";
        }

        std::cout << std::endl;
        std::cout << "Location: " << this->location[0] << ", " << this->location[1] << ", " << this->location[2] << std::endl;
        std::cout << "Not removeable: " << this->not_removable << std::endl;
    }

    void test() {
        std::vector<int> connections;

        connections.push_back(13);
        connections.push_back(14);
        connections.push_back(15);
        std::array<int, 3> location{1, 2, 3};

        std::shared_ptr<CheeseNode> bit = MakeCheeseNode(1, connections, location, false);
        bit->info();
    }

    std::shared_ptr<Cheese> MakeCheese(int width, int length, int height) {
        auto cheese = std::make_shared<Cheese>();
        cheese -> width = width;
        cheese -> length = length;
        cheese -> height = height; 

        std::vector<std::shared_ptr<CheeseNode>> cheeseBalls;
        std::vector<int> connections;
        std::array<int, 3> location;
        int totalNodes = width * length * height;

        int w, l, h = 0;
        for (int i = 0; i < totalNodes; i++) {
            location = {w, l, h};
            cheeseBalls.push_back(MakeCheeseNode(i, connections, location, false));
            w += 1;
            if (w == width) {
                l += 1;
                w = 0;
            }

            if (l == length) {
                h += 1;
                l = 0;
            }
        }

        cheese -> cheeseNodes = cheeseBalls;
        return cheese;
    }

    void Cheese::info() {
        for (const auto &node: this -> cheeseNodes) {
            node -> info();
            std::cout << std::endl;
        }
    }
}
