#include "cudaGen.h"
#include "cheese.h"

int main(){
    //cuda::generate();
   std::shared_ptr<cheese::Cheese> cheese = cheese::MakeCheese(2,2,1);

   cheese -> info();
}