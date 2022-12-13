#include <iostream>
using namespace std;

int main()
{
    int num, i;
    int product =1;
    std::cout<<"Enter a number:\n"<< std::endl;
    std::cin>>num;
    for(i=num;i>0; i--)
        product = product * i;
    std::cout<<"The factorial for " << num << "is: \n"<< product;
    return 1;
}

