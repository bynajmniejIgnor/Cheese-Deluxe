#include "cudaGen.h"
#include "cheeseOps.h"

int main(){
    //cuda::generate();
   std::shared_ptr<cheese::Cheese> cheese = cheese::MakeCheese(2,2,1);
   cheese->info();

    std::shared_ptr<cheeseOps::CheeseKeeper> keeper = cheeseOps::EducateCheeseKeeper(cheese);

    bool test = keeper->verify(cheese);
}