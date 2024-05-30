#include "cheeseOps.h"

int main(){
    cheese::Cheese cheese = cheese::MakeCheese(2,2,2);
    auto cheesePtr = std::make_shared<cheese::Cheese>(cheese);
    std::shared_ptr<cheeseOps::CheeseKeeper> keeper = cheeseOps::EducateCheeseKeeper(cheesePtr);


    /*  
    bool test = keeper->verifyCheese(cheese);
    cheese->info();
    for (const auto &cheeseball: cheese->cheeseBalls) {
        if(keeper->validateCheeseBall(cheeseball, cheese, 3, 5, 2)) std::cout<<"CheeseBall "<<cheeseball->index<<" is valid!"<<std::endl;
        else std::cout<<"CheeseBall "<<cheeseball->index<<" is not valid :(("<<std::endl; 
    }
    */
    int n;
    std::cout << "Enter the number of binary digits (n): ";
    std::cin >> n;
    auto allTheCheeses = cuda::cheesenerate<8>(n);

    std::cout<<"Highest number generated: " << allTheCheeses[allTheCheeses.size()-1].to_string() <<std::endl;

    std::cout<<"====== ORIGINAL CHEESE ======="<<std::endl;
    cheese.info();
    std::cout<<"====== MODIFIED CHEESE ======="<<std::endl;
    keeper->carveTheCheese<8>(cheese, allTheCheeses[7]);
    cheese.info();
    return 0;
}