#include <drivers_loader/application.hpp>

int main(int argc, char *argv[])
{
    drivers_loader::application application{ argc, argv };
    return application.exec();
}