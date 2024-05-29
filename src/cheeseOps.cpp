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

    bool CheeseKeeper::verify(std::shared_ptr<cheese::Cheese> cheese) {
        std::array<bool, 6> checkMarks;
        checkMarks.fill(false);
        int checkPointer = 0;

        for (const auto &node: cheese->cheeseNodes) {
            if(checkPointer>=5) break;
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

        for (bool check : checkMarks) {
            if (!check) {
                std::cout<<"This cheese has failed at least one wall"<<std::endl;
                return false;
            }       
        }

        std::cout<<"The walls of this piece of cheese stand strong!"<<std::endl;
        return true;
    }
}