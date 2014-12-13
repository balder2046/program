#include <stdio.h>
#include "loginstance.h"

int main() {
    CLogInstance *inst = new CLogInstance(stdout);
    
    inst->LogInfo("Hello, That's from log!");
    return 0;
 
}
