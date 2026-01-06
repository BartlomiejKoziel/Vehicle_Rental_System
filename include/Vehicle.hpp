#pragma once

#include <string>
#include <stdexcept>

namespace bk {

class Vehicle {
public:
    /**
     * @enum MainVehicleType
     * @brief High-level type of the vehicle.
     */
    enum class MainVehicleType {
        Car,
        Truck,
        Motorcycle
    };

    /**
     * @enum LicenceCategory
     * @brief Represents the required driving licence category (A1, A2, B, C).
     */
    enum class LicenceCategory {
        A,
        B,
        C
    };

protected:
    std::string regNumber;      ///< Registration number (Unique ID)
    std::string brand;          ///< Vehicle Brand
    std::string model;          ///< Vehicle Model
    double mileage;             ///< Current mileage in km
    double baseCost;            ///< Base daily rental cost in zl
    LicenceCategory licenceCat; ///< Required licence category

public:
    /**
     * @brief Default Constructor.
     * Initializes with empty/zero values and Category B default.
     */
    Vehicle() : regNumber(""), brand("Unknown"), model("Unknown"), mileage(0.0), 
    baseCost(0.0), licenceCat(LicenceCategory::B) {}

    /**
     * @brief Parameterized Constructor.
     * @param reg Registration number.
     * @param brandVal Vehicle brand.
     * @param modelVal Vehicle model.
     * @param miles Initial mileage.
     * @param cost Base daily cost.
     * @param cat Required licence category.
     * @throws std::invalid_argument If validation fails.
     */
    Vehicle(const std::string& reg, const std::string& brandVal, const std::string& modelVal,
            double miles, double cost, LicenceCategory cat)
        : regNumber(reg), brand(brandVal), model(modelVal), mileage(miles), baseCost(cost), licenceCat(cat) 
    {
        if (regNumber.empty()) throw std::invalid_argument("Registration number cannot be empty.");
        if (regNumber.length() > 9) throw std::invalid_argument("Registration number cannot exceed 9 characters.");
        if (brand.empty()) throw std::invalid_argument("Brand cannot be empty.");
        if (model.empty()) throw std::invalid_argument("Model cannot be empty.");
    }

    /**
     * @brief Virtual Destructor.
     */
    virtual ~Vehicle() = default;

    /**
     * @brief Calculate the rental cost for a given number of days.
     * @param days Number of rental days.
     * @return Total cost as double.
     */
    virtual double calculateRentCost(int days) const = 0;

    /**
     * @brief Get detailed information about the vehicle.
     * @return String containing vehicle details.
     */
    virtual std::string getInfo() const = 0;

    /**
     * @brief Get the main type of the vehicle.
     * @return MainVehicleType enum value.
     */
    virtual MainVehicleType getMainVehicleType() const = 0;

    // Getters
    /**
     * @brief Get the registration number.
     * @return Registration number string.
     */
    std::string getRegNumber() const { return regNumber; }

    /**
     * @brief Get the brand.
     * @return Brand name.
     */
    std::string getBrand() const { return brand; }

    /**
     * @brief Get the model.
     * @return Model name.
     */
    std::string getModel() const { return model; }

    /**
     * @brief Get the current mileage.
     * @return Mileage in km.
     */
    double getMileage() const { return mileage; }

    /**
     * @brief Get the base daily rental cost.
     * @return Cost in zl.
     */
    double getBaseCost() const { return baseCost; }

    /**
     * @brief Get the required licence category.
     * @return LicenceCategory enum.
     */
    LicenceCategory getLicenceCategory() const { return licenceCat; }

    // Setters
    /**
     * @brief Set the new mileage.
     * @param newMileage New mileage value.
     * @throws std::invalid_argument If new mileage is negative or less than current.
     */
    void setMileage(double newMileage) {
        if (newMileage < 0) {
            throw std::invalid_argument("Mileage cannot be negative.");
        }
        if (newMileage < mileage) {
            throw std::invalid_argument("New mileage cannot be lower than current mileage.");
        }
        mileage = newMileage;
    }

    /**
     * @brief Change the base cost.
     * @param newCost New daily cost involved.
     * @throws std::invalid_argument If new cost is non-positive.
     */
    void setBaseCost(double newCost) {
        if (newCost <= 0) {
            throw std::invalid_argument("Base cost must be positive.");
        }
        baseCost = newCost;
    }

    // --- Operators ---

    /**
     * @brief Equality operator comparing registration numbers.
     */
    bool operator==(const Vehicle& other) const {
        return this->regNumber == other.regNumber;
    }

    /**
     * @brief Inequality operator.
     */
    bool operator!=(const Vehicle& other) const {
        return !(*this == other);
    }

    /**
     * @brief Helper to convert LicenceCategory to string.
     */
    static std::string licenceCategoryToString(LicenceCategory cat) {
        switch (cat) {
            case LicenceCategory::A: return "A";
            case LicenceCategory::B: return "B";
            case LicenceCategory::C: return "C";
            default: return "Unknown";
        }
    }

    /**
     * @brief Stream insertion operator.
     */
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v) {
        os << v.getInfo();
        return os;
    }
};

} // namespace bk
