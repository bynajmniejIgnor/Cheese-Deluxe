#include "cheeseOps.h"

int main(){
    std::shared_ptr<cheese::Cheese> cheese = cheese::MakeCheese(2,2,2);
    std::shared_ptr<cheeseOps::CheeseKeeper> keeper = cheeseOps::EducateCheeseKeeper(cheese);

    /*  
    bool test = keeper->verifyCheese(cheese);
    cheese->info();
    for (const auto &cheeseball: cheese->cheeseBalls) {
        if(keeper->validateCheeseBall(cheeseball, cheese, 3, 5, 2)) std::cout<<"CheeseBall "<<cheeseball->index<<" is valid!"<<std::endl;
        else std::cout<<"CheeseBall "<<cheeseball->index<<" is not valid :(("<<std::endl; 
    }
    */

    cuda::generate();
}