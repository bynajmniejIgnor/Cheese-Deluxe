#include "cheeseOps.h"

namespace cheeseOps {
    std::shared_ptr<CheeseKeeper> EducateCheeseKeeper(std::shared_ptr<cheese::Cheese> cheese) {
        auto keeper = std::make_shared<CheeseKeeper>();

        int c = 0;
        for (int h=0; h<cheese->height; h++) {
           for (int x=0; x<cheese->length; x++) {
                keeper->wallBounds[LEFT].push_back(c);
                keeper->wallBounds[RIGHT].push_back(c+cheese->width-1);
                c+=cheese->width;
            }
            for (int w=0; w<cheese->width; w++){
                keeper->wallBounds[BACK].push_back(w+h*cheese->sliceArea);
                keeper->wallBounds[FRONT].push_back(w+cheese->width*(cheese->length*(h+1)-1));
            }
        }

        for (int i=0; i<cheese->sliceArea; i++) {
            keeper->wallBounds[DOWN].push_back(i);
            keeper->wallBounds[TOP].push_back(i+cheese->sliceArea*(cheese->height-1));
        } 

        return keeper;
    }

    bool CheeseKeeper::verifyCheese(cheese::Cheese &cheese, size_t C1, size_t C2, size_t C3, bool verbose) { //Checks for mandatory wall cheeseballs, connectivity (graph theory) and contitions
        std::array<bool, 6> checkMarks;
        checkMarks.fill(false);
        int checkPointer = 0;

        for (const auto &node: cheese.cheeseBalls) {
            if(checkPointer==6) break;
            for (size_t wall = 0; wall < this->wallBounds.size(); wall++) {
                if (checkMarks[wall]) continue;
                for (const auto &num : wallBounds[wall]) {
                    if (node.index == num) {
                        checkMarks[wall] = true;
                        checkPointer++;
                        break;
                    }
                }
            }
        }

        for (size_t check=0; check<checkMarks.size(); check++) {
            if (!checkMarks[check]) {
                if (verbose) std::cout<<"This cheese has failed at least one wall condition ("<<check<<")"<<std::endl;
                return false;
            }       
        }

        if(!this->connectivityCheck(cheese)) {
            if (verbose) std::cout<<"This cheese is not a connected graph :(("<<std::endl;
            return false;
        }

        for (const auto &cheeseball: cheese.cheeseBalls) {
            if (!this->validateCheeseBall(std::make_shared<cheese::CheeseBall>(cheeseball), std::make_shared<cheese::Cheese>(cheese), C1, C2, C3)) {
                if (verbose) std::cout<<"This cheese is about to collapse!"<<std::endl;
                return false;
            }
        }

        if (verbose) std::cout<<"The walls and connectivity of this piece of cheese stand strong!"<<std::endl;
        return true;
    }

    int CheeseKeeper::getConnectedCheeseBall(std::shared_ptr<cheese::CheeseBall> cheeseball, int avoidIdx) {
        for (int conn : cheeseball->connections) {
            if (conn != cheeseball->index /*this condition is a sanity check, shouldn't happen*/ && conn != avoidIdx && conn != -1) return conn;
        }
        return -1;
    }

    bool CheeseKeeper::condition1(std::shared_ptr<cheese::CheeseBall> cheeseball, size_t C1) {
        return cheeseball->connections.size() >= C1;
    }

    bool CheeseKeeper::condition2(std::shared_ptr<cheese::CheeseBall> cheeseball, std::shared_ptr<cheese::Cheese> cheese, size_t C2) {
        if (cheeseball->connections.size()==1) {
            int hook = this->getConnectedCheeseBall(cheeseball, -1);
            if (hook != -1) return cheese->cheeseBalls[hook].connections.size()-1 >= C2;
        }
        return false;
    }

    bool CheeseKeeper::condition3(std::shared_ptr<cheese::CheeseBall> cheeseball, std::shared_ptr<cheese::Cheese> cheese, size_t C3) {
        if(cheeseball->connections.size() == 2) {
            int hook = this->getConnectedCheeseBall(cheeseball, -1);
            int other_hook = this->getConnectedCheeseBall(cheeseball, hook);
            if (hook != -1 && other_hook != -1) return cheese->cheeseBalls[hook].connections.size()-1 >= C3 || cheese->cheeseBalls[other_hook].connections.size()-1 >= C3;
        }
        return false;
    }

    bool CheeseKeeper::validateCheeseBall(std::shared_ptr<cheese::CheeseBall> cheeseball, std::shared_ptr<cheese::Cheese> cheese, size_t C1, size_t C2, size_t C3){
        if(!this->condition1(cheeseball, C1)) {
            if(!this->condition2(cheeseball, cheese, C2)) {
                if(!this->condition3(cheeseball, cheese, C3)) {
                    return false;
                }
            }
        }
        return true;
    }

    void CheeseKeeper::dfs(cheese::Cheese &cheese, int current) {
        cheese.cheeseBalls[current].visited = true;
        for (int conn : cheese.cheeseBalls[current].connections) {
            if (!cheese.cheeseBalls[conn].visited && cheese.cheeseBalls[conn].index != -1) this->dfs(cheese, conn);
        }
    }

    bool CheeseKeeper::connectivityCheck(cheese::Cheese &cheese) {
        for (const auto &cheeseball: cheese.cheeseBalls) {
            if (cheeseball.index != -1) {
                this->dfs(cheese, cheeseball.index);
                break;
            }
        }
       
       for (const auto &cheeseball: cheese.cheeseBalls) {
            if (cheeseball.visited == false && cheeseball.index != -1) {
                return false;
            }
        }
        return true;
    }

    void CheeseKeeper::obliterateCheeseBall(cheese::CheeseBall &cheeseball){
        cheeseball.index = -1;
        // :))
    }

    template <int BITSET_SIZE>
    void CheeseKeeper::carveTheCheese(cheese::Cheese &cheese, std::bitset<BITSET_SIZE> mask) {
        for (size_t i=0; i<mask.size(); i++) {
            if (!mask[i]) this->obliterateCheeseBall(cheese.cheeseBalls[i]);
        }
    }

    template void CheeseKeeper::carveTheCheese<8>(cheese::Cheese &cheese, std::bitset<8> mask);
    template void CheeseKeeper::carveTheCheese<16>(cheese::Cheese &cheese, std::bitset<16> mask);
    template void CheeseKeeper::carveTheCheese<24>(cheese::Cheese &cheese, std::bitset<24> mask);
    template void CheeseKeeper::carveTheCheese<27>(cheese::Cheese &cheese, std::bitset<27> mask);
    template void CheeseKeeper::carveTheCheese<32>(cheese::Cheese &cheese, std::bitset<32> mask);
}