#include "cheeseOps.h"

#define CHEESEBALLS 16 

int main(){
    cheese::Cheese cheese = cheese::MakeCheese(2,2,2);
    auto cheesePtr = std::make_shared<cheese::Cheese>(cheese);
    std::shared_ptr<cheeseOps::CheeseKeeper> keeper = cheeseOps::EducateCheeseKeeper(cheesePtr);

    auto allTheCheeses = cuda::cheesenerate<CHEESEBALLS>(CHEESEBALLS);
    size_t cheeseCount = allTheCheeses.size();

    int maxHoles = -1;
    int progress = 0;
    int c;
    std::cin>>c;
    std::bitset<CHEESEBALLS> mostHolesomeCheese; 

    #pragma omp parallel for reduction(max:maxHoles)
    for (const auto &holeset: allTheCheeses) {
        cheese::Cheese cheeseCopy = cheese;
        keeper->carveTheCheese<CHEESEBALLS>(cheeseCopy, holeset);

        #pragma omp atomic
        progress++;
        if (omp_get_thread_num() % 3 == 0 && progress % (cheeseCount / 100) == 0 || progress == cheeseCount) {
            std::cout << "\rCheesed: " << (100 * progress / cheeseCount) << "%" << std::flush;
        }

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

    std::cout<<std::endl;
    keeper->carveTheCheese<CHEESEBALLS>(cheese, mostHolesomeCheese);
    if (keeper->verifyCheese(cheese, 3, 5, 2, true)) std::cout<<"One of optimal cheeses is "<<mostHolesomeCheese.to_string()<<", number of holes: "<<CHEESEBALLS-mostHolesomeCheese.count()<<std::endl;
    cheese.info();
    
    return 0;
}