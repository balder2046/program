#include <stdio.h>
#include "loginstance.h"

int main() {
    CLogInstance *inst = new CLogInstance(stdout);
    
    inst->printf("Hello World! NI HAO");
    return 0;
 
}
