#pragma once

#include "CombustionVehicle.hpp"
#include <sstream>
#include <string>
#include <stdexcept>

namespace bk {

/**
 * @class Motorcycle
 * @brief Represents a motorcycle.
 */
class Motorcycle : public CombustionVehicle {


public:
    /**
     * @brief Default Constructor.
     */
    Motorcycle() : CombustionVehicle() {}

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
     */
    Motorcycle(const std::string& reg, const std::string& brand, const std::string& model,
               double miles, double cost, LicenceCategory cat,
               int engine, double consumption, FuelType fuel)
        : CombustionVehicle(reg, brand, model, miles, cost, cat, engine, consumption, fuel)
    {}

    /**
     * @brief Virtual Destructor.
     */
    virtual ~Motorcycle() = default;

    /**
     * @brief Calculate rent cost.
     * @param days Number of rental days.
     * @return Total cost.
     */
    double calculateRentCost(int days) const override {
        if (days <= 0) {
            throw std::invalid_argument("Rental duration must be positive.");
        }
        return baseCost * days;
    }

    /**
     * @brief Get detailed information about the motorcycle.
     * @return String containing motorcycle details.
     */
    std::string getInfo() const override {
        std::stringstream ss;
        ss << "Motorcycle: " << brand << " " << model << " [" << regNumber << "]\n"
           << "  Mileage: " << mileage << " km\n"
           << "  Base Cost: " << baseCost << " zl/day\n"
           << "  Licence: " << Vehicle::licenceCategoryToString(licenceCat) << "\n"
           << "  Engine: " << engineSize << " cm3\n"
           << "  Fuel: " << CombustionVehicle::fuelTypeToString(fuelType) << " (" 
               << fuelConsumption << " L/100km)";
        return ss.str();
    }

    /**
     * @brief Get the main vehicle type.
     * @return MainVehicleType enum value.
     */
    MainVehicleType getMainVehicleType() const override {
        return MainVehicleType::Motorcycle;
    }
};

} // namespace bk
