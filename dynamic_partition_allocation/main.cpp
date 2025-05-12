#include <iostream>
#include "allocation.h"

signed main(int argc, char* argv[])
{
    if (argc < 2)
        std::cout << "error" << std::endl;
    try
    {
        dpa::FirstFit ff(argv[1]);
        ff.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}