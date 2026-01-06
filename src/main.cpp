#include "../include/VehicleManager.hpp"
#include "../include/UserInterface.hpp"
#include <iostream>

using namespace bk;

int main() {
    VehicleManager vm;
    
    // Auto-load data
    std::cout << "Loading data...\n";
    vm.loadFromFile("data.txt");
    std::cout << "Data loaded.\n";

    // Run UI
    UserInterface ui(vm);
    ui.run();

    return 0;
}
