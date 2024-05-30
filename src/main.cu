#include "cheeseOps.h"

#define CHEESEBALLS 32 

int main(){
    cheese::Cheese cheese = cheese::MakeCheese(2,4,2);
    auto cheesePtr = std::make_shared<cheese::Cheese>(cheese);
    std::shared_ptr<cheeseOps::CheeseKeeper> keeper = cheeseOps::EducateCheeseKeeper(cheesePtr);

    int n;
    std::cout << "Enter the number of binary digits (n): ";
    std::cin >> n;
    auto allTheCheeses = cuda::cheesenerate<CHEESEBALLS>(n);

    int maxHoles = -1;
    std::bitset<CHEESEBALLS> mostHolesomeCheese; 

    #pragma omp parallel for reduction(max:maxHoles)
    for (const auto &holeset: allTheCheeses) {
        cheese::Cheese cheeseCopy = cheese;
        keeper->carveTheCheese<CHEESEBALLS>(cheeseCopy, holeset);
        if (keeper->verifyCheese(cheeseCopy, 3, 5, 2, false)) {
            int holes = holeset.size() - holeset.count();
            #pragma omp critical
            {
                if (holes > maxHoles) {
                    maxHoles = holes;
                    mostHolesomeCheese = holeset;
                }
            } 
        }
    }


    keeper->carveTheCheese<CHEESEBALLS>(cheese, mostHolesomeCheese);
    if (keeper->verifyCheese(cheese, 3, 5, 2, false)) std::cout<<"One of optimal cheeses is "<<mostHolesomeCheese<<", number of holes: "<<CHEESEBALLS-mostHolesomeCheese.count()<<std::endl;
    cheese.info();
    
    return 0;
}