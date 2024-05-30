#include "cheeseOps.h"

int main(){
    cheese::Cheese cheese = cheese::MakeCheese(2,2,2);
    auto cheesePtr = std::make_shared<cheese::Cheese>(cheese);
    std::shared_ptr<cheeseOps::CheeseKeeper> keeper = cheeseOps::EducateCheeseKeeper(cheesePtr);

    int n;
    std::cout << "Enter the number of binary digits (n): ";
    std::cin >> n;
    auto allTheCheeses = cuda::cheesenerate<8>(n);

    for (const auto &holeset: allTheCheeses) {
        cheese::Cheese cheeseCopy = cheese;
        std::cout<<"{"<<holeset.to_string()<<"}"<<std::endl;
        cheeseCopy.info();
        keeper->carveTheCheese<8>(cheeseCopy, holeset);
        std::cout<<"============================="<<std::endl;
        keeper->verifyCheese(cheeseCopy, 3, 5, 2, false);
        cheeseCopy.info();
    }
   
    return 0;
}