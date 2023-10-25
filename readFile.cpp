#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream myfile("questions.txt");
    if (myfile.is_open())
    {
        char mychar;
        while (myfile)
        {
            mychar = myfile.get();
            std::cout << mychar;
        }
    }
}