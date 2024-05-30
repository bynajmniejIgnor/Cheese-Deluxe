#include "cheese.h"

namespace cheese
{
    CheeseBall MakeCheeseBall(int idx, std::vector<int> connections, std::array<int, 3> location) {
        CheeseBall cheeseball;
        cheeseball.index = idx;
        cheeseball.connections = connections;
        cheeseball.location = location;
        cheeseball.visited = false;

        return cheeseball;
    }

    void CheeseBall::info() {
        std::cout << "Index: " << this->index << std::endl;
        std::cout << "Connections: ";
        for (const auto &conn : this->connections) {
            std::cout << conn << ", ";
        }

        std::cout << std::endl;
        std::cout << "Location: " << this->location[0] << ", " << this->location[1] << ", " << this->location[2] << std::endl;
        std::cout << "Visited: " << this->visited << std::endl;
    }

    Cheese MakeCheese(int width, int length, int height) {
        Cheese cheese;
        cheese.width = width;
        cheese.length = length;
        cheese.height = height; 
        cheese.sliceArea = width * length;

        std::vector<CheeseBall> cheeseBalls;
        std::vector<int> connections;
        std::array<int, 3> location;
        int totalBalls = width * length * height;

        int w, l, h = 0;
        for (int i = 0; i < totalBalls; i++) {
            location = {w, l, h};
            cheeseBalls.push_back(MakeCheeseBall(i, connections, location));
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

        cheese.cheeseBalls = cheeseBalls;
        cheese.bindSlices();
        cheese.stackSlices();
        cheese.solidifyCheese();
        cheese.ageTheCheese();

        return cheese;
    }

    void Cheese::info() {
        for (auto &node: this -> cheeseBalls) {
            node.info();
            std::cout << std::endl;
        }
    }

    void Cheese::bindSlices() { 
        for (int l = 0; l < this->length-1; l++) {
            for (int w = 0; w < this->width; w++) {
                this->cheeseBalls[l * this->width + w].connections.push_back((l+1) * this->width + w);
            }
        }

        int c = 0;
        for (int i = 0; i < this->sliceArea-1; i++) {
            if (c == this->width-1) {
                c = 0;
                continue;
            }
            this->cheeseBalls[i].connections.push_back(i+1);
            c++;
        }
    }

    void Cheese::stackSlices() {
        for (int h = 0; h < this->height; h ++) {
            for (int i = 0; i < this->sliceArea; i++ ) {
                for (int c = 0; c < i + this->sliceArea * (h - 1); c ++){
                    this->cheeseBalls[i + this->sliceArea * h].connections.push_back(c + this->sliceArea);
                }
            }
        }
    }

    void Cheese::solidifyCheese() {
        for (int h = 0; h < this->height-1; h++) {
            for (int i = 0; i < this->sliceArea; i++) {
                this->cheeseBalls[i + sliceArea * h].connections.push_back(i + this->sliceArea * (h+1));
            }
        }
    }


    bool isNotInVector(const std::vector<int>& vec, int value) {
        for (int num : vec) {
            if (num == value) {
                return false;
            }
        }
        return true;
    }

    void Cheese::ageTheCheese() {
        for (const auto &node: this->cheeseBalls) {
           for (const auto &conn: node.connections) {
                if (isNotInVector(this->cheeseBalls[conn].connections, node.index)) {
                    this->cheeseBalls[conn].connections.push_back(node.index);
                }
           } 
        }
    }
}
