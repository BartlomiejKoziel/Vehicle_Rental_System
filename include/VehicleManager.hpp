#pragma once

#include "Vehicle.hpp"
#include "Customer.hpp"
#include "Rental.hpp"
#include "CombustionCar.hpp"
#include "ElectricCar.hpp"
#include "Truck.hpp"
#include "Motorcycle.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

namespace bk {

/**
 * @class VehicleManager
 * @brief Central class for managing Vehicles, Customers, and Rentals.
 * @note Follows Strict Rule: Uses RAW POINTERS for all object management.
 *       Responsible for manual memory allocation and deallocation.
 */
class VehicleManager {
private:
    std::vector<Vehicle*> vehicles;   ///< Container for all vehicles (owns memory)
    std::vector<Customer*> customers; ///< Container for all customers (owns memory)
    std::vector<Rental*> rentals;     ///< Container for active rentals (owns memory)
    std::vector<std::string> rentalHistory; ///< Archive of past rentals

    /**
     * @brief Helper to check if a vehicle registration number is unique.
     */
    bool isRegNumberUnique(const std::string& regNumber) const {
        for (const auto* v : vehicles) {
            if (v->getRegNumber() == regNumber) return false;
        }
        return true;
    }

    /**
     * @brief Helper to check if a customer ID is unique.
     */
    bool isCustomerIdUnique(const std::string& id) const {
        for (const auto* c : customers) {
            if (c->getId() == id) return false;
        }
        return true;
    }

public:
    /**
     * @brief Constructor.
     */
    VehicleManager() = default;

    /**
     * @brief Destructor.
     * CRITICAL: Manually deletes all managed objects to prevent memory leaks.
     */
    ~VehicleManager() {
        for (auto* r : rentals) delete r;
        rentals.clear();

        for (auto* v : vehicles) delete v;
        vehicles.clear();

        for (auto* c : customers) delete c;
        customers.clear();
    }

    // --- Vehicle Management ---

    /**
     * @brief Add a new vehicle to the system.
     * @param v Raw pointer to the vehicle (takes ownership).
     * @throws std::invalid_argument If vehicle is null or regNumber not unique.
     */
    void addVehicle(Vehicle* v) {
        if (!v) throw std::invalid_argument("Vehicle cannot be null.");
        if (!isRegNumberUnique(v->getRegNumber())) {
            throw std::invalid_argument("Vehicle with this registration number already exists.");
        }
        vehicles.push_back(v);
    }

    /**
     * @brief Remove a vehicle by registration number.
     * @note Also deletes the object from memory.
     */
    void removeVehicle(const std::string& regNumber) {
        for (const auto* r : rentals) {
            if (r->getVehicle()->getRegNumber() == regNumber) {
                throw std::invalid_argument("Cannot remove vehicle that is currently rented.");
            }
        }

        auto it = std::remove_if(vehicles.begin(), vehicles.end(),
            [&regNumber](Vehicle* v) {
                if (v->getRegNumber() == regNumber) {
                    delete v; // Free memory
                    return true;
                }
                return false;
            });
        
        if (it != vehicles.end()) {
            vehicles.erase(it, vehicles.end());
        } else {
            throw std::invalid_argument("Vehicle not found.");
        }
    }

    /**
     * @brief Find a vehicle by registration number.
     * @return Raw pointer to vehicle or nullptr if not found.
     */
    Vehicle* getVehicle(const std::string& regNumber) const {
        for (auto* v : vehicles) {
            if (v->getRegNumber() == regNumber) return v;
        }
        return nullptr;
    }

    /**
     * @brief Find vehicles by brand.
     * @return Vector of matching vehicles.
     */
    std::vector<Vehicle*> findVehiclesByBrand(const std::string& brand) const {
        std::vector<Vehicle*> matches;
        for (auto* v : vehicles) {
            if (v->getBrand() == brand) {
                matches.push_back(v);
            }
        }
        return matches;
    }

    /**
     * @brief Find vehicles with base price <= maxPrice.
     */
    std::vector<Vehicle*> findVehiclesByPrice(double maxPrice) const {
        std::vector<Vehicle*> matches;
        for (auto* v : vehicles) {
            if (v->getBaseCost() <= maxPrice) {
                matches.push_back(v);
            }
        }
        return matches;
    }

    /**
     * @brief Find vehicles that are NOT currently rented.
     */
    std::vector<Vehicle*> findAvailableVehicles() const {
        std::vector<Vehicle*> available;
        for (auto* v : vehicles) {
            bool isRented = false;
            for (const auto* r : rentals) {
                if (r->getVehicle() == v) {
                    isRented = true;
                    break;
                }
            }
            if (!isRented) {
                available.push_back(v);
            }
        }
        return available;
    }

    /**
     * @brief Display all vehicles.
     */
    void showAllVehicles() const {
        if (vehicles.empty()) {
            std::cout << "No vehicles in the system.\n";
            return;
        }
        for (const auto* v : vehicles) {
            std::cout << *v << "\n-----------------\n";
        }
    }

    void showCars() const {
        bool found = false;
        for (const auto* v : vehicles) {
            if (dynamic_cast<const CombustionCar*>(v) || dynamic_cast<const ElectricCar*>(v)) {
                std::cout << *v << "\n-----------------\n";
                found = true;
            }
        }
        if (!found) std::cout << "No cars found.\n";
    }

    void showCombustionCars() const {
        bool found = false;
        for (const auto* v : vehicles) {
            if (dynamic_cast<const CombustionCar*>(v)) {
                std::cout << *v << "\n-----------------\n";
                found = true;
            }
        }
        if (!found) std::cout << "No combustion cars found.\n";
    }

    void showElectricCars() const {
        bool found = false;
        for (const auto* v : vehicles) {
            if (dynamic_cast<const ElectricCar*>(v)) {
                std::cout << *v << "\n-----------------\n";
                found = true;
            }
        }
        if (!found) std::cout << "No electric cars found.\n";
    }

    void showMotorcycles() const {
        bool found = false;
        for (const auto* v : vehicles) {
            if (dynamic_cast<const Motorcycle*>(v)) {
                std::cout << *v << "\n-----------------\n";
                found = true;
            }
        }
        if (!found) std::cout << "No motorcycles found.\n";
    }

    void showTrucks() const {
        bool found = false;
        for (const auto* v : vehicles) {
            if (dynamic_cast<const Truck*>(v)) {
                std::cout << *v << "\n-----------------\n";
                found = true;
            }
        }
        if (!found) std::cout << "No trucks found.\n";
    }

    // --- Customer Management ---

    /**
     * @brief Add a new customer to the system.
     * @param c Raw pointer to the customer.
     * @throws std::invalid_argument If customer is null or ID not unique.
     */
    void addCustomer(Customer* c) {
        if (!c) throw std::invalid_argument("Customer cannot be null.");
        if (!isCustomerIdUnique(c->getId())) {
            throw std::invalid_argument("Customer with this ID already exists.");
        }
        customers.push_back(c);
    }

    /**
     * @brief Remove a customer by ID.
     * @note Also deletes the object from memory.
     */
    void removeCustomer(const std::string& id) {
        for (const auto* r : rentals) {
            if (r->getCustomer()->getId() == id) {
                throw std::invalid_argument("Cannot remove customer who has active rentals.");
            }
        }

        auto it = std::remove_if(customers.begin(), customers.end(),
            [&id](Customer* c) {
                if (c->getId() == id) {
                    delete c; // Free memory
                    return true;
                }
                return false;
            });

        if (it != customers.end()) {
            customers.erase(it, customers.end());
        } else {
            throw std::invalid_argument("Customer not found.");
        }
    }

    /**
     * @brief Find a customer by ID.
     * @return Raw pointer to customer or nullptr if not found.
     */
    Customer* getCustomer(const std::string& id) const {
        for (auto* c : customers) {
            if (c->getId() == id) return c;
        }
        return nullptr;
    }

    /**
     * @brief Display all customers.
     */
    void showAllCustomers() const {
        if (customers.empty()) {
            std::cout << "No customers in the system.\n";
            return;
        }
        for (const auto* c : customers) {
            std::cout << *c << "\n-----------------\n";
        }
    }

    void showPrivateCustomers() const {
        bool found = false;
        for (const auto* c : customers) {
            if (dynamic_cast<const PrivateCustomer*>(c)) {
                std::cout << *c << "\n-----------------\n";
                found = true;
            }
        }
        if (!found) std::cout << "No private customers found.\n";
    }

    void showBusinessCustomers() const {
        bool found = false;
        for (const auto* c : customers) {
            if (dynamic_cast<const BusinessCustomer*>(c)) {
                std::cout << *c << "\n-----------------\n";
                found = true;
            }
        }
        if (!found) std::cout << "No business customers found.\n";
    }

    // --- Rental Management ---

    /**
     * @brief Create a rental transaction.
     * @param regNumber Registration number of the vehicle.
     * @param customerId ID of the customer.
     * @param startDate Start date (YYYY-MM-DD).
     * @param endDate End date (YYYY-MM-DD).
     * @param showMessage If true, prints success message.
     * @throws std::invalid_argument If vehicle/customer invalid or vehicle already rented.
     */
    void rentVehicle(const std::string& regNumber, const std::string& customerId, 
                     const std::string& startDate, const std::string& endDate, 
                     bool showMessage = true) {
        Vehicle* v = getVehicle(regNumber);
        if (!v) throw std::invalid_argument("Vehicle not found.");

        Customer* c = getCustomer(customerId);
        if (!c) throw std::invalid_argument("Customer not found.");

        // Check if vehicle is already rented
        for (const auto* r : rentals) {
            if (r->getVehicle()->getRegNumber() == regNumber) {
                throw std::invalid_argument("Vehicle is already rented.");
            }
        }

        // Create new rental (Raw pointer managed by vector)
        Rental* rental = new Rental(v, c, startDate, endDate);
        rentals.push_back(rental);
        if (showMessage) std::cout << "Vehicle rented successfully.\n";
    }

    /**
     * @brief Return a vehicle (end the rental).
     * @param regNumber Registration number of the vehicle to return.
     * @return Total cost of the rental.
     * @throws std::invalid_argument If vehicle is not currently rented.
     */
    double returnVehicle(const std::string& regNumber, double newMileage) {
        auto it = std::find_if(rentals.begin(), rentals.end(),
            [&regNumber](Rental* r) {
                return r->getVehicle()->getRegNumber() == regNumber;
            });

        if (it == rentals.end()) {
            throw std::invalid_argument("Rental not found for this vehicle.");
        }

        Rental* r = *it;
        
        // Update mileage
        r->getVehicle()->setMileage(newMileage);

        double cost = r->calculateTotalCost();

        // Add to history
        std::stringstream ss;
        ss << r->getVehicle()->getBrand() << " " << r->getVehicle()->getModel() 
           << " (" << r->getVehicle()->getRegNumber() << ");"
           << r->getCustomer()->getName() << " (" << r->getCustomer()->getId() << ");"
           << r->getStartDate() << ";" << r->getEndDate() << ";" << cost;
        rentalHistory.push_back(ss.str());
        
        // Cleanup
        delete r;
        rentals.erase(it);

        return cost;
    }

    /**
     * @brief Display all active rentals.
     */
    void showInfo() const {
        if (rentals.empty()) {
            std::cout << "No active rentals.\n";
            return;
        }
        for (const auto* r : rentals) {
            std::cout << r->getInfo() << "\n=================\n";
        }
    }

    void showRentalHistory() const {
        if (rentalHistory.empty()) {
            std::cout << "No rental history.\n";
            return;
        }
        std::cout << "=== Rental History ===\n";
        for (const auto& entry : rentalHistory) {
            std::stringstream ss(entry);
            std::string segment;
            std::vector<std::string> parts;
            while(std::getline(ss, segment, ';')) parts.push_back(segment);

            if (parts.size() >= 5) {
                std::cout << "Vehicle: " << parts[0] << "\n"
                          << "Customer: " << parts[1] << "\n"
                          << "Period: " << parts[2] << " - " << parts[3] << "\n"
                          << "Cost: " << parts[4] << " zl\n"
                          << "-----------------\n";
            }
        }
    }

    // --- Persistence ---

    /**
     * @brief Save global state to file.
     * @param filename Path to file.
     */
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Could not open file for saving.");

        // Save Vehicles
        file << vehicles.size() << "\n"; // Number of vehicles
        for (const auto* v : vehicles) {
            if (auto* p = dynamic_cast<const CombustionCar*>(v)) {
                // Type;Brand;Model;Reg;Cost;Engine;FuelCons;FuelType;Licence;Mileage;Doors
                file << "CombustionCar;" 
                     << p->getBrand() << ";" << p->getModel() << ";" << p->getRegNumber() << ";" 
                     << p->getBaseCost() << ";" << p->getEngineSize() << ";" 
                     << p->getFuelConsumption() << ";" << static_cast<int>(p->getFuelType()) << ";" 
                     << static_cast<int>(p->getLicenceCategory()) << ";" << p->getMileage() << ";" 
                     << p->getDoors() << "\n";
            } else if (auto* p = dynamic_cast<const ElectricCar*>(v)) {
                // Type;Brand;Model;Reg;Cost;Battery;Licence;Mileage;Doors
                file << "ElectricCar;" 
                     << p->getBrand() << ";" << p->getModel() << ";" << p->getRegNumber() << ";" 
                     << p->getBaseCost() << ";" << p->getBatteryCapacity() << ";" 
                     << static_cast<int>(p->getLicenceCategory()) << ";" << p->getMileage() << ";" 
                     << p->getDoors() << "\n";
            } else if (auto* p = dynamic_cast<const Truck*>(v)) {
                // Type;Brand;Model;Reg;Cost;Engine;FuelCons;FuelType;Licence;Mileage;Capacity
                file << "Truck;" 
                     << p->getBrand() << ";" << p->getModel() << ";" << p->getRegNumber() << ";" 
                     << p->getBaseCost() << ";" << p->getEngineSize() << ";" 
                     << p->getFuelConsumption() << ";" << static_cast<int>(p->getFuelType()) << ";" 
                     << static_cast<int>(p->getLicenceCategory()) << ";" << p->getMileage() << ";" 
                     << p->getCargoCapacity() << "\n";
            } else if (auto* p = dynamic_cast<const Motorcycle*>(v)) {
                // Type;Brand;Model;Reg;Cost;Engine;FuelCons;FuelType;Licence;Mileage
                file << "Motorcycle;" 
                     << p->getBrand() << ";" << p->getModel() << ";" << p->getRegNumber() << ";" 
                     << p->getBaseCost() << ";" << p->getEngineSize() << ";" 
                     << p->getFuelConsumption() << ";" << static_cast<int>(p->getFuelType()) << ";" 
                     << static_cast<int>(p->getLicenceCategory()) << ";" << p->getMileage() << "\n";
            }
        }

        // Save Customers
        file << customers.size() << "\n"; // Number of customers
        for (const auto* c : customers) {
            if (auto* p = dynamic_cast<const PrivateCustomer*>(c)) {
                // PrivateCustomer;Name;Address;IDCard
                file << "PrivateCustomer;" << p->getName() << ";" 
                     << p->getAddress() << ";" << p->getIdCardNumber() << "\n";
            } else if (auto* p = dynamic_cast<const BusinessCustomer*>(c)) {
                // BusinessCustomer;Name;Address;NIP
                file << "BusinessCustomer;" << p->getName() << ";" << p->getAddress() << ";" << p->getNip() << "\n";
            }
        }

        // Save Rentals
        file << rentals.size() << "\n"; // Number of rentals
        for (const auto* r : rentals) {
            file << r->getVehicle()->getRegNumber() << ";"
                 << r->getCustomer()->getId() << ";"
                 << r->getStartDate() << ";"
                 << r->getEndDate() << "\n";
        }

        // Save History
        file << rentalHistory.size() << "\n";
        for (const auto& entry : rentalHistory) {
             file << entry << "\n";
        }

        file.close();
    }

    /**
     * @brief Load global state from file.
     * @param filename Path to file.
     * @note Clears current state before loading.
     */
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        // Clear existing
        for (auto* r : rentals) delete r; rentals.clear();
        for (auto* v : vehicles) delete v; vehicles.clear();
        for (auto* c : customers) delete c; customers.clear();

        std::string line; //buffer for reading lines
        
        // Load Vehicles
        int vCount = 0;
        if (std::getline(file, line)) vCount = std::stoi(line);

        for (int i = 0; i < vCount; ++i) {  //cutting line of text into parts
            if (!std::getline(file, line)) break;
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;
            while (std::getline(ss, segment, ';')) parts.push_back(segment);

            if (parts.empty()) continue;

            Vehicle* v = nullptr;
            try {

                if (parts[0] == "CombustionCar" && parts.size() >= 11) {
                    // Type;Brand;Model;Reg;Cost;Engine;FuelCons;FuelType;Licence;Mileage;Doors
                    //   0    1     2    3   4     5      6         7        8       9     10
                    auto fuel = static_cast<CombustionVehicle::FuelType>(std::stoi(parts[7]));
                    auto cat = static_cast<Vehicle::LicenceCategory>(std::stoi(parts[8]));
                    v = new CombustionCar(
                        parts[3], parts[1], parts[2], std::stod(parts[9]), std::stod(parts[4]), 
                        cat, std::stoi(parts[5]), std::stod(parts[6]), fuel, std::stoi(parts[10])
                    );
                } else if (parts[0] == "ElectricCar" && parts.size() >= 9) {
                    // Type;Brand;Model;Reg;Cost;Battery;Licence;Mileage;Doors
                    //   0    1     2     3   4    5       6       7       8
                    auto cat = static_cast<Vehicle::LicenceCategory>(std::stoi(parts[6]));
                    v = new ElectricCar(
                        parts[3], parts[1], parts[2], std::stod(parts[7]), std::stod(parts[4]), 
                        cat, std::stod(parts[5]), std::stoi(parts[8])
                    );
                } else if (parts[0] == "Truck" && parts.size() >= 11) {
                    // Type;Brand;Model;Reg;Cost;Engine;FuelCons;FuelType;Licence;Mileage;Capacity
                    //   0    1     2    3   4    5        6        7        8       9       10
                    auto fuel = static_cast<CombustionVehicle::FuelType>(std::stoi(parts[7]));
                    auto cat = static_cast<Vehicle::LicenceCategory>(std::stoi(parts[8]));
                    v = new Truck(
                        parts[3], parts[1], parts[2], std::stod(parts[9]), std::stod(parts[4]), 
                        cat, std::stoi(parts[5]), std::stod(parts[6]), fuel, std::stoi(parts[10])
                    );
                } else if (parts[0] == "Motorcycle" && parts.size() >= 10) {
                     // Type;Brand;Model;Reg;Cost;Engine;FuelCons;FuelType;Licence;Mileage
                     //   0    1     2    3   4    5        6        7        8       9
                    auto fuel = static_cast<CombustionVehicle::FuelType>(std::stoi(parts[7]));
                    auto cat = static_cast<Vehicle::LicenceCategory>(std::stoi(parts[8]));
                    v = new Motorcycle(
                        parts[3], parts[1], parts[2], std::stod(parts[9]), std::stod(parts[4]), 
                        cat, std::stoi(parts[5]), std::stod(parts[6]), fuel
                    );
                }

                if (v) vehicles.push_back(v);
            } catch (const std::exception& e) {
                std::cout << "[Error Loading Vehicle]: " << e.what() << " Line: " << line << "\n";
                if (v) delete v;
            }
        }

        // Load Customers
        int cCount = 0;
        if (std::getline(file, line)) cCount = std::stoi(line);

        for (int i = 0; i < cCount; ++i) {
            if (!std::getline(file, line)) break;
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;
            while (std::getline(ss, segment, ';')) parts.push_back(segment);

            if (parts.empty()) continue;

            Customer* c = nullptr;
            try {
                if (parts[0] == "PrivateCustomer") {
                    // PrivateCustomer;Name;Address;IDCard
                    // parts[0];parts[1];parts[2];parts[3]
                    if (parts.size() >= 4) {
                         // Use parts[3] (IDCard) as ID
                         c = new PrivateCustomer(parts[1], parts[2], parts[3]);
                    }
                } else if (parts[0] == "BusinessCustomer") {
                    // BusinessCustomer;Name;Address;NIP
                     if (parts.size() >= 4) {
                        // Use parts[3] (NIP) as ID
                        c = new BusinessCustomer(parts[1], parts[2], parts[3]);
                     }
                }

                if (c) customers.push_back(c);
            } catch (...) {
                if (c) delete c;
            }
        }

        // Load Rentals
        int rCount = 0;
        if (std::getline(file, line)) rCount = std::stoi(line);

        for (int i = 0; i < rCount; ++i) {
            if (!std::getline(file, line)) break;
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;
            while (std::getline(ss, segment, ';')) parts.push_back(segment);

            if (parts.size() < 4) continue;
            
            try {
                rentVehicle(parts[0], parts[1], parts[2], parts[3], false);
            } catch (...) {}
        }

        // Load History
        int hCount = 0;
        if (std::getline(file, line)) hCount = std::stoi(line);
        rentalHistory.clear();
        for (int i = 0; i < hCount; ++i) {
             if (std::getline(file, line)) {
                 rentalHistory.push_back(line);
             }
        }
        
        file.close();
    }
};

} // namespace bk
