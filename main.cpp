#include <iostream>
#include <exception>

#include "Application.h"

int _tmain(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    try
    {
        Application app;
        app.loadData();
        app.showResult();
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what();
        return RETURN_FAILED;
    }
    return RETURN_OK;
}