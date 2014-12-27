#include <iostream>
#include <vector>
int main()
{
    std::vector<int> nums;
    for (int i = 0; i < 100; ++i)
    {
        nums.push_back(i);
    }
    int sum = 0;
    for (std::vector<int>::iterator iter = nums.begin(); iter != nums.end(); ++iter)
    {
        sum += *iter;
    }
    std::cout << sum;
}
