#pragma once

#include "Vehicle.hpp"
#include <string>
#include <stdexcept>

namespace bk {

/**
 * @class CombustionVehicle
 * @brief Abstract intermediate class for vehicles with internal combustion engines.
 */
class CombustionVehicle : public Vehicle {
public:
    /**
     * @enum FuelType
     * @brief Type of fuel used by the vehicle (Gasoline or Diesel).
     */
    enum class FuelType {
        Gasoline,
        Diesel
    };

protected:
    int engineSize;         ///< Engine displacement in cm3
    double fuelConsumption; ///< Fuel consumption in L/100km
    FuelType fuelType;      ///< Type of fuel

public:
    /**
     * @brief Default Constructor.
     */
    CombustionVehicle()
        : Vehicle(), engineSize(0), fuelConsumption(0.0), fuelType(FuelType::Gasoline)
    {}

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
     * @throws std::invalid_argument If engine size or consumption is non-positive.
     */
    CombustionVehicle(const std::string& reg, const std::string& brand, const std::string& model,
                      double miles, double cost, LicenceCategory cat,
                      int engine, double consumption, FuelType fuel)
        : Vehicle(reg, brand, model, miles, cost, cat),
          engineSize(engine),
          fuelConsumption(consumption),
          fuelType(fuel)
    {
        if (engineSize <= 0) {
            throw std::invalid_argument("Engine size must be positive.");
        }
        if (fuelConsumption <= 0) {
            throw std::invalid_argument("Fuel consumption must be positive.");
        }
    }

    /**
     * @brief Virtual Destructor.
     */
    virtual ~CombustionVehicle() = default;

    // Getters
    /**
     * @brief Get the engine size.
     * @return Engine size in cm3.
     */
    int getEngineSize() const { return engineSize; }

    /**
     * @brief Get the fuel consumption.
     * @return Fuel consumption in L/100km.
     */
    double getFuelConsumption() const { return fuelConsumption; }

    /**
     * @brief Get the fuel type.
     * @return FuelType enum value.
     */
    FuelType getFuelType() const { return fuelType; }

    // Setters
    /**
     * @brief Set engine size.
     * @param size Size in cm3.
     * @throws std::invalid_argument If size is non-positive.
     */
    void setEngineSize(int size) {
        if (size <= 0) {
            throw std::invalid_argument("Engine size must be positive.");
        }
        engineSize = size;
    }

    /**
     * @brief Set fuel consumption.
     * @param consumption Consumption in L/100km.
     * @throws std::invalid_argument If consumption is non-positive.
     */
    void setFuelConsumption(double consumption) {
        if (consumption <= 0) {
            throw std::invalid_argument("Fuel consumption must be positive.");
        }
        fuelConsumption = consumption;
    }

    /**
     * @brief Set fuel type.
     * @param type New fuel type.
     */
    void setFuelType(FuelType type) {
        if (!(type == FuelType::Gasoline || type == FuelType::Diesel)) {
            throw std::invalid_argument("Invalid fuel type.");
        }
        fuelType = type;
    }

    /**
     * @brief Helper to convert FuelType to string.
     */
    static std::string fuelTypeToString(FuelType type) {
        switch (type) {
            case FuelType::Gasoline: return "Gasoline";
            case FuelType::Diesel: return "Diesel";
            default: return "Unknown";
        }
    }
};

} // namespace bk
