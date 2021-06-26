#include <iostream>
#include <exception>

#include "Application.h"

int _tmain(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    //std::locale::global(std::locale("ru_RU.UTF-8"));
    //std::locale utf8_locale("ru_RU.UTF-8");
    //std::locale::global(utf8_locale);
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