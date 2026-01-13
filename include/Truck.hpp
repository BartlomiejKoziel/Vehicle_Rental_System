#pragma once

#include "CombustionVehicle.hpp"
#include <sstream>
#include <string>
#include <stdexcept>

namespace bk {

/**
 * @class Truck
 * @brief Represents a transport truck with cargo capacity.
 */
class Truck : public CombustionVehicle {
protected:
    int cargoCapacity; ///< Cargo capacity in kg



public:

    /**
     * @brief Default Constructor.
     */
    Truck() : CombustionVehicle(), cargoCapacity(1) {}

    /**
     * @brief Parametric Constructor.
     * @param reg Registration number.
     * @param brand Brand name.
     * @param model Model name.
     * @param miles Initial mileage.
     * @param cost Base daily cost.
     * @param cat Required licence category.
     * @param engine Engine size in cm3.
     * @param consumption Fuel consumption logic.
     * @param fuel Fuel type.
     * @param capacity Cargo capacity in kg.
     * @throws std::invalid_argument If validation fails (e.g. cargo <= 0).
     */
    Truck(const std::string& reg, const std::string& brand, const std::string& model,
          double miles, double cost, LicenceCategory cat,
          int engine, double consumption, FuelType fuel, int capacity)
        : CombustionVehicle(reg, brand, model, miles, cost, cat, engine, consumption, fuel),
          cargoCapacity(capacity)
    {
        if (cargoCapacity <= 0) {
            throw std::invalid_argument("Cargo capacity must be positive.");
        }
    }

    /**
     * @brief Virtual Destructor.
     */
    virtual ~Truck() = default;

    /**
     * @brief Calculate rent cost.
     * @param days Number of rental days.
     * @return Total cost: Base cost + (Cargo capacity * 0.1 * Days)
     */
    double calculateRentCost(int days) const override {
        if (days <= 0) return 0.0;
        return (baseCost * days) + (cargoCapacity * 0.1 * days);
    }

    /**
     * @brief Get detailed information about the truck.
     * @return String containing truck details.
     */
    std::string getInfo() const override {
        std::stringstream ss;
        ss << "Truck: " << brand << " " << model << " [" << regNumber << "]\n"
           << "  Mileage: " << mileage << " km\n"
           << "  Base Cost: " << baseCost << " zl/day\n"
           << "  Licence: " << Vehicle::licenceCategoryToString(licenceCat) << "\n"
           << "  Engine: " << engineSize << " cm3\n"
           << "  Fuel: " << CombustionVehicle::fuelTypeToString(fuelType) << " (" 
               << fuelConsumption << " L/100km)\n"
           << "  Cargo Capacity: " << cargoCapacity << " kg";
        return ss.str();
    }

    /**
     * @brief Get the main vehicle type.
     * @return MainVehicleType enum value.
     */
    MainVehicleType getMainVehicleType() const override {
        return MainVehicleType::Truck;
    }

    // Setters
    /**
     * @brief Set the cargo capacity.
     * @param capacity New capacity in kg.
     * @throws std::invalid_argument If capacity is non-positive.
     */
    void setCargoCapacity(int capacity) {
        if (capacity <= 0) {
            throw std::invalid_argument("Cargo capacity must be positive.");
        }
        cargoCapacity = capacity;
    }

    // Getters
    /**
     * @brief Get the cargo capacity.
     * @return Capacity in kg.
     */
    int getCargoCapacity() const { return cargoCapacity; }
};

} // namespace bk
