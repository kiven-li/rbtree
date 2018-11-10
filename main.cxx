#include "rbtree.hxx"
#include <iostream>
#include <exception>

int main()
{
    try
    {
        RBTree rbt;
        for(int i = 1; i < 100; i++)
        {
            rbt.Insert(i);
        }
        rbt.Delete(4);
        rbt.Display();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
