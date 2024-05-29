#include "cheese.h"

namespace cheese
{
    std::shared_ptr<CheeseNode> MakeCheeseNode(int idx, std::vector<int> connections, std::array<int, 3> location, bool not_rebovable) {
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

    std::shared_ptr<Cheese> MakeCheese(int width, int length, int height) {
        auto cheese = std::make_shared<Cheese>();
        cheese->width = width;
        cheese->length = length;
        cheese->height = height; 
        cheese->sliceArea = width * length;

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

        cheese->cheeseNodes = cheeseBalls;
        return cheese;
    }

    void Cheese::info() {
        for (const auto &node: this -> cheeseNodes) {
            node->info();
            std::cout << std::endl;
        }
    }

    void Cheese::bindSlices() { // Joins nodes in the same height layer
        for (int l = 0; l < this->length-1; l++) {
            for (int w = 0; w < this->width; w++) {
                this->cheeseNodes[l * this->width + w]->connections.push_back((l+1) * this->width + w);
                std::cout << "Connected "<<l * this->width + w<<" with "<<(l+1) * this->width + w<<std::endl;
            }
        }

        int c = 0;
        for (int i = 0; i < this->sliceArea-1; i++) {
            if (c == this->width-1) {
                c = 0;
                continue;
            }
            this->cheeseNodes[i]->connections.push_back(i+1);
            std::cout << "Connected "<<i<<" with "<<i+1<<std::endl;
            c++;
        }
    }

    void Cheese::stackSlices() {
        for (int h = 0; h < this->height; h ++) {
            for (int i = 0; i < this->sliceArea; i++ ) {
                for (int c = 0; c < i + this->sliceArea * (h - 1); c ++){
                    this->cheeseNodes[i + this->sliceArea * h]->connections.push_back(c + this->sliceArea);
                }
            }
        }
    }

    void Cheese::solidifyCheese() {
        for (int h = 0; h < this->height-1; h++) {
            for (int i = 0; i < this->sliceArea; i++) {
                this->cheeseNodes[i + sliceArea * h]->connections.push_back(i + this->sliceArea * (h+1));
            }
        }
    }

    void Cheese::ageTheCheese() {
        for (const auto &node: this->cheeseNodes) {
            for (int i = 0; i < node->connections.size(); i++) {
                bool found = false;
                for (const auto &c: this->cheeseNodes[i]->connections) {
                    if (node->index == c) {
                        found = true;
                        break;
                    }
                }
                if (!found) this->cheeseNodes[i]->connections.push_back(node->index);
            }
        }
    }
}
