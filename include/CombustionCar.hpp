#pragma once

#include "CombustionVehicle.hpp"
#include <sstream>
#include <string>
#include <stdexcept>

namespace bk {

/**
 * @class CombustionCar
 * @brief Represents a standard combustion engine car.
 */
class CombustionCar : public CombustionVehicle {
protected:
    int doors; ///< Number of doors

public:
    /**
     * @brief Default Constructor.
     */
    CombustionCar() : CombustionVehicle(), doors(1) {}


    /**
     * @brief Parametric Constructor.
     * @param reg Registration.
     * @param brand Brand name.
     * @param model Model name.
     * @param miles Mileage.
     * @param cost Base cost.
     * @param cat Licence cat.
     * @param engine Engine size.
     * @param consumption Fuel consumption.
     * @param fuel Fuel type.
     * @param numDoors Number of doors.
     * @throws std::invalid_argument If validation fails (e.g. doors <= 0).
     */
    CombustionCar(const std::string& reg, const std::string& brand, const std::string& model,
                  double miles, double cost, LicenceCategory cat,
                  int engine, double consumption, FuelType fuel, int numDoors)
        : CombustionVehicle(reg, brand, model, miles, cost, cat, engine, consumption, fuel),
          doors(numDoors)
    {
        if (doors <= 0) {
            throw std::invalid_argument("Number of doors must be positive.");
        }
    }

    /**
     * @brief Virtual Destructor.
     */
    virtual ~CombustionCar() = default;

    /**
     * @brief Calculate rent cost.
     * @param days Number of days.
     * @return Cost (base * days).
     */
    double calculateRentCost(int days) const override {
        if (days <= 0) {
            throw std::invalid_argument("Rental duration must be positive.");
        }
        return baseCost * days;
    }

    /**
     * @brief Get info string.
     */
    std::string getInfo() const override {
        std::stringstream ss;
        ss << "Car: " << brand << " " << model << " [" << regNumber << "]\n"
           << "  Mileage: " << mileage << " km\n"
           << "  Base Cost: " << baseCost << " zl/day\n"
           << "  Licence: " << Vehicle::licenceCategoryToString(licenceCat) << "\n"
           << "  Engine: " << engineSize << " cm3\n"
           << "  Fuel: " << CombustionVehicle::fuelTypeToString(fuelType) << " (" 
               << fuelConsumption << " L/100km)\n"
           << "  Doors: " << doors;
        return ss.str();
    }

    /**
     * @brief Get main vehicle type.
     */
    MainVehicleType getMainVehicleType() const override {
        return MainVehicleType::Car;
    }

    // Setters
    /**
     * @brief Set number of doors.
     * @throws std::invalid_argument If num <= 0.
     */
    void setDoors(int num) {
        if (num <= 0) throw std::invalid_argument("Doors must be positive.");
        doors = num;
    }
    
    // Getters
    /**
     * @brief Get number of doors.
     */
    int getDoors() const { return doors; }
};

} // namespace bk
