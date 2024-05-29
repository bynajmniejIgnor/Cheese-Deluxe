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

    bool CheeseKeeper::verifyCheese(std::shared_ptr<cheese::Cheese> cheese) { //Checks for mandatory wall cheeseballs and connectivity (graph theory)
        std::array<bool, 6> checkMarks;
        checkMarks.fill(false);
        int checkPointer = 0;

        for (const auto &node: cheese->cheeseBalls) {
            if(checkPointer==6) break;
            for (size_t wall = 0; wall < this->wallBounds.size(); wall++) {
                if (checkMarks[wall]) continue;
                for (const auto &num : wallBounds[wall]) {
                    if (node->index == num) {
                        checkMarks[wall] = true;
                        checkPointer++;
                        break;
                    }
                }
            }
        }

        for (size_t check=0; check<checkMarks.size(); check++) {
            if (!checkMarks[check]) {
                std::cout<<"This cheese has failed at least one wall condition ("<<check<<")"<<std::endl;
                return false;
            }       
        }

        if(!this->connectivityCheck(cheese)) {
            std::cout<<"This cheese is not a connected graph :(("<<std::endl;
            return false;
        }

        std::cout<<"The walls and connectivity of this piece of cheese stand strong!"<<std::endl;
        return true;
    }

    int CheeseKeeper::getConnectedCheeseBall(std::shared_ptr<cheese::CheeseBall> cheeseball, int avoidIdx) {
        for (int conn : cheeseball->connections) {
            if (conn != cheeseball->index /*this condition is a sanity check, shouldn't happen*/ && conn != avoidIdx) return conn;
        }
        return -1;
    }

    bool CheeseKeeper::condition1(std::shared_ptr<cheese::CheeseBall> cheeseball, size_t C1) {
        return cheeseball->connections.size() >= C1;
    }

    bool CheeseKeeper::condition2(std::shared_ptr<cheese::CheeseBall> cheeseball, std::shared_ptr<cheese::Cheese> cheese, size_t C2) {
        if (cheeseball->connections.size()==1) {
            int hook = this->getConnectedCheeseBall(cheeseball, -1);
            if (hook != -1) return cheese->cheeseBalls[hook]->connections.size()-1 >= C2;
        }
        return false;
    }

    bool CheeseKeeper::condition3(std::shared_ptr<cheese::CheeseBall> cheeseball, std::shared_ptr<cheese::Cheese> cheese, size_t C3) {
        if(cheeseball->connections.size() == 2) {
            int hook = this->getConnectedCheeseBall(cheeseball, -1);
            int other_hook = this->getConnectedCheeseBall(cheeseball, hook);
            return cheese->cheeseBalls[hook]->connections.size()-1 >= C3 || cheese->cheeseBalls[other_hook]->connections.size()-1 >= C3;
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


    void CheeseKeeper::dfs(std::shared_ptr<cheese::Cheese> cheese, int current) {
        cheese->cheeseBalls[current]->visited = true;
        for (int conn : cheese->cheeseBalls[current]->connections) {
            if (!cheese->cheeseBalls[conn]->visited) this->dfs(cheese, conn);
        }
    }

    bool CheeseKeeper::connectivityCheck(std::shared_ptr<cheese::Cheese> cheese) {
        for (const auto &cheeseball: cheese->cheeseBalls) {
            if (cheeseball->index != -1) {
                this->dfs(cheese, cheeseball->index);
                break;
            }
        }
       
       for (const auto &cheeseball: cheese->cheeseBalls) {
            if (cheeseball->visited == false) {
                return false;
            }
        }
        return true;
    }

    void CheeseKeeper::obliterateCheeseBall(std::shared_ptr<cheese::CheeseBall> cheeseball){
        cheeseball->index = -1;
        // :))
    }

    void CheeseKeeper::carveTheCheese(std::shared_ptr<cheese::Cheese> cheese, std::bitset<BITSET_SIZE> mask) {
        for (size_t i=0; i<mask.size(); i++) {
            if (!mask[i]) this->obliterateCheeseBall(cheese->cheeseBalls[i]);
        }
    }
}