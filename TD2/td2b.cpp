#include "CountDown.h"

int main(){

    CountDown cd(10);
    cd.start_ms(1000, true);

    while(cd.getCounter() > 0);
    
    return 0;
}