#pragma once

#include "VehicleManager.hpp"
#include <iostream>
#include <string>

namespace bk {

/**
 * @class UserInterface
 * @brief Handles all user interaction and menu logic.
 */
class UserInterface {
private:
    VehicleManager& vm; ///< Reference to the vehicle manager (Model)

    // --- Helper Functions ---

    /**
     * @brief Helper function to get valid integer input.
     * @param prompt Text to display to user.
     * @param min Minimum acceptable value.
     * @return Validated integer.
     */
    int getValidInt(const std::string& prompt, int min = -2147483647) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(10000, '\n'); 
                if (value >= min) {
                    return value;
                } else {
                    std::cout << "Invalid input. Value must be at least " << min << ".\n";
                }
            } else {
                std::cout << "Invalid input. Please enter a valid integer number.\n";
                std::cin.clear(); 
                std::cin.ignore(10000, '\n'); 
            }
        }
    }

    /**
     * @brief Helper function to get valid double input.
     * @param prompt Text to display to user.
     * @param min Minimum acceptable value.
     * @return Validated double.
     */
    double getValidDouble(const std::string& prompt, double min = -1e18) {
        double value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(10000, '\n'); 
                if (value >= min) {
                    return value;
                } else {
                    std::cout << "Invalid input. Value must be at least " << min << ".\n";
                }
            } else {
                std::cout << "Invalid input. Please enter a valid decimal number.\n";
                std::cin.clear(); 
                std::cin.ignore(10000, '\n'); 
            }
        }
    }

    /**
     * @brief Helper function to get valid yes/no input.
     * @param prompt Text to display.
     * @return true for 'y', false for 'n'.
     */
    bool getValidYesNo(const std::string& prompt) {
        char value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                std::cin.ignore(10000, '\n'); 
                if (value == 'y' || value == 'Y') return true;
                if (value == 'n' || value == 'N') return false;
                std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
            } else {
                std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        }
    }

    /**
     * @brief Helper to get valid fuel type.
     * @return Selected FuelType enum.
     */
    CombustionVehicle::FuelType getValidFuelType() {
        char fChoice;
        while (true) {
            std::cout << "Fuel Type (d - Diesel, p - Petrol): ";
            if (std::cin >> fChoice) {
                std::cin.ignore(10000, '\n');
                if (tolower(fChoice) == 'd') return CombustionVehicle::FuelType::Diesel;
                if (tolower(fChoice) == 'p') return CombustionVehicle::FuelType::Gasoline;
            } else {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            std::cout << "Invalid fuel type.\n";
        }
    }

    /**
     * @brief Helper to get valid number of doors.
     * @return Integer between 2 and 5.
     */
    int getValidDoors() {
        int doors;
        while (true) {
            doors = getValidInt("Number of Doors (2-5): ", 2);
            if (doors >= 2 && doors <= 5) return doors;
            std::cout << "Doors must be between 2 and 5.\n";
        }
    }

    /**
     * @brief Helper function to get non-empty string input.
     * @param prompt Text to display.
     * @return Non-empty string.
     */
    std::string getValidString(const std::string& prompt) {
        std::string value;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, value);
            if (!value.empty()) {
                return value;
            } else {
                std::cout << "Input cannot be empty. Please try again.\n";
            }
        }
    }

    /**
     * @brief Helper function to get valid date string.
     * @param prompt Text to display.
     * @return Validated date string (YYYY-MM-DD).
     */
    std::string getValidDate(const std::string& prompt) {
        std::string date;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, date);
            if (Rental::isValidDate(date)) {
                return date;
            } else {
                std::cout << "Invalid date format or value. Please use YYYY-MM-DD.\n";
            }
        }
    }

    /**
     * @brief Helper function to get valid NIP input.
     * @param prompt Text to display.
     * @return Validated NIP string (10 digits).
     */
    std::string getValidNIP(const std::string& prompt) {
        std::string nip;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, nip);

            bool allDigits = !nip.empty(); // Ensure not empty starting point
            for (char c : nip) {
                if (!isdigit(c)) {
                    allDigits = false;
                    break;
                }
            }

            if (nip.length() == 10 && allDigits) {
                return nip;
            } else {
                std::cout << "Invalid NIP. It must consist of exactly 10 digits.\n";
            }
        }
    }

    /**
     * @brief Displays the main application menu.
     */
    void printMenu() {
        std::cout << "\n=== VEHICLE RENTAL SYSTEM ===\n";
        std::cout << "1. Add Vehicle\n";
        std::cout << "2. Remove Vehicle\n";
        std::cout << "3. Show Vehicles\n";
        std::cout << "4. Add Customer\n";
        std::cout << "5. Remove Customer\n";
        std::cout << "6. Show Customers\n";
        std::cout << "7. Rent Vehicle\n";
        std::cout << "8. Return Vehicle\n";
        std::cout << "9. Show Active Rentals\n";
        std::cout << "10. Show Rental History\n";
        std::cout << "11. Search\n";
        std::cout << "12. Save Data\n";
        std::cout << "0. Exit\n";
        std::cout << "Select option: ";
    }

    /**
     * @brief UI handling for adding a new vehicle.
     */
    void addVehicleUI() {
        int type = getValidInt("Select Type:    1.CombustionCar    2.ElectricCar    3.Truck    4.Motorcycle: ", 1);

        if (type < 1 || type > 4) {
            std::cout << "Invalid vehicle type selected.\n";
            return;
        }
        
        std::string brand, model, reg;
        double price, mileage;
        brand = getValidString("Brand: ");
        model = getValidString("Model: ");
        reg = getValidString("Reg Number: ");
        price = getValidDouble("Base Price (zl/day): ", 0);
        mileage = getValidDouble("Initial Mileage (km): ", 0);

        try {
            if (type == 1) { //add combustion car
                int engineDisplacement = getValidInt("Engine Displacement (cm^3): ", 0);
                double consumption = getValidDouble("Fuel Consumption (L/100km): ", 0);
                auto fuel = getValidFuelType();
                int doors = getValidDoors();
                vm.addVehicle(new CombustionCar(
                    reg, brand, model, mileage, price, 
                    Vehicle::LicenceCategory::B, 
                    engineDisplacement, consumption, 
                    fuel, doors
                ));
                std::cout << "Vehicle added successfully.\n";
            } else if (type == 2) { //add electric car
                double battery = getValidDouble("Battery Capacity (kWh): ", 0);
                int doors = getValidDoors();
                vm.addVehicle(new ElectricCar(reg, brand, model, mileage, price, Vehicle::LicenceCategory::B, battery, doors));
                std::cout << "Vehicle added successfully.\n";
            } else if (type == 3) { //add truck
                int engine = getValidInt("Engine Displacement (cm^3): ", 0);
                double cargo = getValidDouble("Cargo Capacity (kg): ", 0);
                double consumption = getValidDouble("Fuel Consumption (L/100km): ", 0);
                auto fuel = getValidFuelType();
                vm.addVehicle(new Truck(
                    reg, brand, model, mileage, price, 
                    Vehicle::LicenceCategory::C, 
                    engine, consumption, fuel, 
                    static_cast<int>(cargo)
                ));
                std::cout << "Vehicle added successfully.\n";
            } else if (type == 4) { //add motorcycle
                int engine = getValidInt("Engine Displacement (cm^3): ", 0);
                double consumption = getValidDouble("Fuel Consumption (L/100km): ", 0);
                vm.addVehicle(new Motorcycle(
                    reg, brand, model, mileage, price, 
                    Vehicle::LicenceCategory::A, 
                    engine, consumption, 
                    CombustionVehicle::FuelType::Gasoline
                ));
                std::cout << "Vehicle added successfully.\n";
            } else {
                std::cout << "Invalid type.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        }
    }

    /**
     * @brief UI handling for adding a new customer.
     */
    void addCustomerUI() {
        int type = getValidInt("Select Type:   1.Private    2.Business: ");

        if (type < 1 || type > 2) {
            std::cout << "Invalid customer type selected.\n";
            return;
        }

        std::string name, address; 
        if (type == 1) {
            name = getValidString("Name and Surname: ");
        } else {
            name = getValidString("Company Name: ");
        }
        address = getValidString("Address (City, street, house number): ");

        try {
            if (type == 1) {
                std::string idCard;
                idCard = getValidString("ID Card Number: ");
                // PrivateCustomer(name, addr, idCard) - ID will be idCard
                vm.addCustomer(new PrivateCustomer(name, address, idCard));
            } else if (type == 2) {
                std::string nip;
                nip = getValidNIP("NIP: ");
                // BusinessCustomer(name, addr, nip) - ID will be nip
                vm.addCustomer(new BusinessCustomer(name, address, nip));
            } else {
                std::cout << "Invalid type.\n";
            }
            std::cout << "Customer added successfully.\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    /**
     * @brief UI handling for searching.
     */
    void searchUI() {
        std::cout << "\n=== SEARCH ===\n";
        std::cout << "1. Vehicle by Registration\n";
        std::cout << "2. Vehicles by Brand\n";
        std::cout << "3. Customer by ID\n";
        std::cout << "4. Vehicles by Max Price\n";
        std::cout << "5. Available Vehicles\n";
        int choice = getValidInt("Select option: ");

        if (choice == 1) {
            std::string reg;
            reg = getValidString("Enter Registration: ");
            Vehicle* v = vm.getVehicle(reg);
            if (v) std::cout << "\n" << *v << "\n";
            else std::cout << "Vehicle not found.\n";
        } else if (choice == 2) {
            std::string brand;
            brand = getValidString("Enter Brand: ");
            auto results = vm.findVehiclesByBrand(brand);
            if (results.empty()) {
                std::cout << "No vehicles found for brand: " << brand << "\n";
            } else {
                std::cout << "\n";
                for (auto* v : results) {
                    std::cout << *v << "\n-----------------\n";
                }
            }
        } else if (choice == 3) {
            std::string id;
            id = getValidString("Enter Customer ID (NIP/ID Card): ");
            Customer* c = vm.getCustomer(id);
            if (c) std::cout << *c << "\n";
            else std::cout << "Customer not found.\n";
        } else if (choice == 4) {
            double maxPrice = getValidDouble("Enter Max Price: ", 0);
            auto results = vm.findVehiclesByPrice(maxPrice);
            if (results.empty()) {
                std::cout << "No vehicles found within this price range.\n";
            } else {
                std::cout << "\n";
                for (auto* v : results) {
                    std::cout << *v << "\n-----------------\n";
                }
            }
        } else if (choice == 5) {
            auto results = vm.findAvailableVehicles();
            if (results.empty()) {
                std::cout << "No available vehicles at the moment.\n";
            } else {
                std::cout << "\n";
                for (auto* v : results) {
                    std::cout << *v << "\n-----------------\n";
                }
            }
        } else {
            std::cout << "Invalid option.\n";
        }
    }

public:
    /**
     * @brief Constructor.
     * @param vehicleManager Reference to the logic logic controller.
     */
    explicit UserInterface(VehicleManager& vehicleManager) : vm(vehicleManager) {}

    /**
     * @brief Main Application Loop.
     */
    void run() {
        int choice;
        do {
            printMenu();
            choice = getValidInt("");

            try {
                switch (choice) {
                    case 1: addVehicleUI(); break;
                    case 2: {
                        std::string reg;
                        reg = getValidString("Reg Number: ");
                        vm.removeVehicle(reg);
                        std::cout << "Vehicle removed successfully.\n";
                        break;
                    }
                    case 3: {
                        std::cout << "\nChoose display option:\n";
                        std::cout << "1. All Vehicles\n";
                        std::cout << "2. Cars\n";
                        std::cout << "3. Motorcycles\n";
                        std::cout << "4. Trucks\n";
                        int subChoice = getValidInt("");

                        if (subChoice == 1) {
                            std::cout << "\n";
                            vm.showAllVehicles();
                        } else if (subChoice == 2) {
                            std::cout << "\nChoose Car Type:\n";
                            std::cout << "1. All Cars\n";
                            std::cout << "2. Combustion Cars\n";
                            std::cout << "3. Electric Cars\n";
                            int carChoice = getValidInt("");
                            
                            std::cout << "\n"; 
                            if (carChoice == 1) vm.showCars();
                            else if (carChoice == 2) vm.showCombustionCars();
                            else if (carChoice == 3) vm.showElectricCars();
                            else std::cout << "Invalid car type.\n";
                        } else if (subChoice == 3) {
                            std::cout << "\n";
                            vm.showMotorcycles();
                        } else if (subChoice == 4) {
                            std::cout << "\n";
                            vm.showTrucks();
                        } else {
                            std::cout << "Invalid option.\n";
                        }
                        break; 
                    }
                    case 4: addCustomerUI(); break;
                    case 5: {
                        std::string id;
                        id = getValidString("ID: ");
                        vm.removeCustomer(id);
                        break;
                    }
                    case 6: {
                        std::cout << "\nChoose display option:\n";
                        std::cout << "1. All Customers\n";
                        std::cout << "2. Private Customers\n";
                        std::cout << "3. Business Customers\n";
                        int subChoice = getValidInt("");

                        if (subChoice == 1) {
                            std::cout << "\n";
                            vm.showAllCustomers();
                        } else if (subChoice == 2) {
                            std::cout << "\n";
                            vm.showPrivateCustomers();
                        } else if (subChoice == 3) {
                            std::cout << "\n";
                            vm.showBusinessCustomers();
                        } else {
                            std::cout << "Invalid option.\n";
                        }
                        break; 
                    }
                    case 7: {
                        std::string reg, id, start, end;
                        reg = getValidString("Vehicle Reg: ");
                        id = getValidString("Customer ID: ");
                        start = getValidDate("Start (YYYY-MM-DD): ");
                        end = getValidDate("End (YYYY-MM-DD): ");
                        vm.rentVehicle(reg, id, start, end);
                        break;
                    }
                    case 8: {
                        std::string reg;
                        reg = getValidString("Vehicle Reg: ");
                        double newMileage = getValidDouble("New Mileage (km): ", 0);
                        double cost = vm.returnVehicle(reg, newMileage);
                        std::cout << "Vehicle returned. Total Cost: " << cost << " zl\n";
                        break;
                    }
                    case 9: std::cout << "\n"; vm.showInfo(); break;
                    case 10: vm.showRentalHistory(); break;
                    case 11: searchUI(); break;
                    case 12: vm.saveToFile("data.txt"); std::cout << "Saved.\n"; break;
                    case 0: {
                        if (getValidYesNo("Do you want to save data before exiting? (y/n): ")) {
                            vm.saveToFile("data.txt");
                            std::cout << "Data saved.\n";
                        }
                        std::cout << "Exiting...\n"; 
                        break;
                    }
                    default: std::cout << "Invalid option.\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Operation failed: " << e.what() << "\n";
            }
        } while (choice != 0);
    }
};

} // namespace bk
