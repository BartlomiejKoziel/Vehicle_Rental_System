#pragma once

#include "Vehicle.hpp"
#include "Customer.hpp"
#include <string>
#include <stdexcept>
#include <sstream>

namespace bk {

/**
 * @class Rental
 * @brief Represents a rental transaction linking a Vehicle and a Customer.
 * @note Uses raw pointers. Manual date input.
 */
class Rental {
private:
    Vehicle* vehicle;   ///< Rented vehicle (Raw pointer)
    Customer* customer; ///< Customer renting the vehicle (Raw pointer)
    std::string startDate; ///< Start date of rental
    std::string endDate;   ///< End date of rental

    /**
     * @brief Helper to check if a year is a leap year.
     */
    static bool isLeapYear(int year) {
        return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    }

    /**
     * @brief Get number of days in a specific month of a specific year.
     */
    static int getDaysInMonth(int month, int year) {
        // Index 0 = January, 1 = February, etc.
        static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month < 1 || month > 12) return 0;
        
        int d = days[month - 1];
        if (month == 2 && isLeapYear(year)) d++;
        return d;
    }

public:
    /**
     * @brief Helper to validate date format "YYYY-MM-DD".
     */
    static bool isValidDate(const std::string& date) {
        if (date.length() != 10) return false;
        if (date[4] != '-' || date[7] != '-') return false;
        for (int i = 0; i < 10; ++i) {
            if (i == 4 || i == 7) continue;
            if (!isdigit(date[i])) return false;
        }
        
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));
        
        if (month < 1 || month > 12) return false;
        
        if (day < 1 || day > getDaysInMonth(month, year)) return false;

        return true;
    }

    /**
     * @brief Default Constructor.
     */
    Rental() : vehicle(nullptr), customer(nullptr), startDate(""), endDate("") {}

    /**
     * @brief Parametric Constructor.
     * @param v Raw pointer to the vehicle.
     * @param c Raw pointer to the customer.
     * @param start Start date string (YYYY-MM-DD).
     * @param end End date string (YYYY-MM-DD).
     * @throws std::invalid_argument If pointers are null, dates empty/invalid, or end <= start.
     */
    Rental(Vehicle* v, Customer* c, const std::string& start, const std::string& end)
        : vehicle(v), customer(c), startDate(start), endDate(end)
    {
        if (v == nullptr) throw std::invalid_argument("Vehicle cannot be null.");
        if (c == nullptr) throw std::invalid_argument("Customer cannot be null.");
        
        if (!isValidDate(start)) throw std::invalid_argument("Start date must be in format YYYY-MM-DD.");
        if (!isValidDate(end)) throw std::invalid_argument("End date must be in format YYYY-MM-DD.");

        if (end <= startDate) {
            throw std::invalid_argument("End date must be later than start date.");
        }
    }

    /**
     * @brief End the rental (update end date).
     * @note Strictly, end date is set in constructor now, but this allows extension.
     */
    void setEndDate(const std::string& end) {
         if (!isValidDate(end)) throw std::invalid_argument("End date must be in format YYYY-MM-DD.");
         if (end <= startDate) throw std::invalid_argument("End date must be later than start date.");
         endDate = end;
    }

    /**
     * @brief Get the rented vehicle.
     * @return Raw pointer to vehicle.
     */
    Vehicle* getVehicle() const { return vehicle; }

    /**
     * @brief Get the customer who rented.
     * @return Raw pointer to customer.
     */
    Customer* getCustomer() const { return customer; }

    /**
     * @brief Get the start date.
     * @return Start date string.
     */
    std::string getStartDate() const { return startDate; }

    /**
     * @brief Get the end date.
     * @return End date string.
     */
    std::string getEndDate() const { return endDate; }

    /**
     * @brief Calculate total days since year 0 to the given date.
     * simple loop-based algorithm for readability.
     */
    int countTotalDays(const std::string& date) const {
        int y = std::stoi(date.substr(0, 4));
        int m = std::stoi(date.substr(5, 2));
        int d = std::stoi(date.substr(8, 2));

        int total = d; // Add current month days

        // Add days for past years
        for (int i = 1; i < y; ++i) {
            total += isLeapYear(i) ? 366 : 365;
        }

        // Add days for past months in current year
        for (int i = 1; i < m; ++i) {
            total += getDaysInMonth(i, y);
        }
        
        return total;
    }

    /**
     * @brief Calculate number of days between start and end date.
     * @return Number of days (inclusive of start day, minimum 1).
     */
    int getRentalDays() const {
        if (startDate.empty() || endDate.empty()) return 0;
        
        // Calculate difference simply by subtracting total days from year 0
        int startTotal = countTotalDays(startDate);
        int endTotal = countTotalDays(endDate);
        
        int days = endTotal - startTotal;
        
        return (days < 1) ? 1 : days; 
    }

    /**
     * @brief Calculate the total cost of this rental.
     * @return Cost based on vehicle rules.
     */
    double calculateTotalCost() const {
        if (!vehicle) return 0.0;
        int days = getRentalDays();
        return vehicle->calculateRentCost(days);
    }

    /**
     * @brief Get info about the rental with cost.
     */
    std::string getInfo() const {
        if (!vehicle || !customer) return "Rental: [Empty/Invalid]";
        std::stringstream ss;
        ss << "Rental Details [" << startDate << " - " << endDate << "]:\n";
        ss << "  Duration: " << getRentalDays() << " days\n";
        ss << "  Total Cost: " << calculateTotalCost() << " zl\n";
        ss << "--- Vehicle Info ---\n" << vehicle->getInfo() << "\n";
        ss << "--- Customer Info ---\n" << customer->getInfo();
        return ss.str();
    }
};

} // namespace bk
