#include "clockapp.hpp"

int main(int argc, char** argv)
{
        std::cout << app::watch_exist() << "\n";
        std::cout << app::timer_exist() << "\n";
        std::cout << app::stopwatch_exist() << "\n";
        std::cout << app::worldwatch_exist() << "\n";
        std::cout << app::pomadoro_exist() << "\n";

        return 0;
}
