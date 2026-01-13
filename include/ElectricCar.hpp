#pragma once

#include "ElectricVehicle.hpp"
#include <sstream>
#include <stdexcept>

namespace bk {

/**
 * @class ElectricCar
 * @brief Represents a standard electric car.
 */
class ElectricCar : public ElectricVehicle {
protected:
    int doors; // Number of doors

public:
    /**
     * @brief Default Constructor.
     */
    ElectricCar() : ElectricVehicle(), doors(0) {}


    /**
     * @brief Parametric Constructor.
     * @param reg Registration number.
     * @param brand Brand name.
     * @param model Model name.
     * @param miles Initial mileage.
     * @param cost Base daily cost.
     * @param cat Required licence category.
     * @param battery Battery capacity in kWh.
     * @param numDoors Number of doors.
     * @throws std::invalid_argument If doors are non-positive.
     */
    ElectricCar(const std::string& reg, const std::string& brand, const std::string& model,
                double miles, double cost, LicenceCategory cat,
                double battery, int numDoors)
        : ElectricVehicle(reg, brand, model, miles, cost, cat, battery), doors(numDoors)
    {
        if (doors <= 0) {
            throw std::invalid_argument("Number of doors must be positive.");
        }
    }

    /**
     * @brief Virtual Destructor.
     */
    virtual ~ElectricCar() = default;

    /**
     * @brief Calculate rent cost.
     * @param days Number of days.
     * @return Cost (base * days).
     */
    double calculateRentCost(int days) const override {
        if (days <= 0) return 0.0;
        return baseCost * days;
    }

    /**
     * @brief Get info string.
     */
    std::string getInfo() const override {
        std::stringstream ss;
        ss << "Electric Car: " << brand << " " << model << " [" << regNumber << "]\n"
        << "  Battery: " << batteryCapacity << " kWh\n"
           << "  Mileage: " << mileage << " km\n"
           << "  Base Cost: " << baseCost << " zl/day\n"
           << "  Licence: " << Vehicle::licenceCategoryToString(licenceCat) << "\n"
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
