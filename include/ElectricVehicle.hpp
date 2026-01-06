#pragma once

#include "Vehicle.hpp"
#include <string>
#include <stdexcept>

namespace bk {

/**
 * @class ElectricVehicle
 * @brief Abstract intermediate class for vehicles with electric motors.
 */
class ElectricVehicle : public Vehicle {
protected:
    double batteryCapacity;    ///< Battery capacity in kWh

public:
    /**
     * @brief Default Constructor.
     */
    ElectricVehicle() : Vehicle(), batteryCapacity(0.0) {}

    /**
     * @brief Parametric Constructor.
     * @param reg Registration number.
     * @param brand Brand name.
     * @param model Model name.
     * @param miles Initial mileage.
     * @param cost Base daily cost.
     * @param cat Required licence category.
     * @param battery Battery capacity in kWh.
     * @throws std::invalid_argument If battery capacity is non-positive.
     */
    ElectricVehicle(const std::string& reg, const std::string& brand, const std::string& model,
                    double miles, double cost, LicenceCategory cat, double battery)
        : Vehicle(reg, brand, model, miles, cost, cat), batteryCapacity(battery)
    {
        if (batteryCapacity <= 0.0) {
            throw std::invalid_argument("Battery capacity must be positive.");
        }
    }

    /**
     * @brief Virtual Destructor.
     */
    virtual ~ElectricVehicle() = default;

    // Getters
    /**
     * @brief Get the battery capacity.
     * @return Battery capacity in kWh.
     */
    double getBatteryCapacity() const { return batteryCapacity; }

    // Setters
    /**
     * @brief Set battery capacity.
     * @param capacity Capacity in kWh.
     * @throws std::invalid_argument If capacity is non-positive.
     */
    void setBatteryCapacity(double capacity) {
        if (capacity <= 0.0) {
            throw std::invalid_argument("Battery capacity must be positive.");
        }
        batteryCapacity = capacity;
    }
};

} // namespace bk
