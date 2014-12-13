#include <iostream>
#include <boost/timer.hpp>
using namespace boost;
int main() {
    timer timerutil;
    std::cout << "Max Elasped Time is " << timerutil.elapsed_max() / 3600 << "h"<< std::endl;
    std::cout << "Min Elapsed Time is" << timerutil.elapsed_min()* 1000 << "ms" << std::endl;
    std::cout << "Elapsed time " << timerutil.elapsed() << std::endl;
}
