#include <SFML/Window.hpp>

#include "main_controller.hpp"

int main()
{
    main_controller* MGC = new main_controller();
    MGC->start();
    delete MGC;
    return 0;
}
