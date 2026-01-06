#pragma once

#include <string>
#include <stdexcept>
#include <sstream>

namespace bk {

/**
 * @brief Enum representing the type of customer.
 */
enum class CustomerType {
    Private,
    Business
};

/**
 * @class Customer
 * @brief Abstract base class representing a customer.
 */
class Customer {
protected:
    std::string id;      ///< Unique identifier (internal)
    std::string name;    ///< Full name or company name
    std::string address; ///< Contact address

public:
    /**
     * @brief Default Constructor.
     */
    Customer() : id(""), name("Unknown"), address("Unknown") {}

    /**
     * @brief Parametric Constructor.
     * @param idVal Unique ID.
     * @param nameVal Name.
     * @param addrVal Address.
     * @throws std::invalid_argument If strings are empty.
     */
    Customer(const std::string& idVal, const std::string& nameVal, const std::string& addrVal)
        : id(idVal), name(nameVal), address(addrVal)
    {
        if (id.empty()) throw std::invalid_argument("ID cannot be empty.");
        if (name.empty()) throw std::invalid_argument("Name cannot be empty.");
        if (address.empty()) throw std::invalid_argument("Address cannot be empty.");
    }

    /**
     * @brief Virtual Destructor.
     */
    virtual ~Customer() = default;

    /**
     * @brief Get detailed information about the customer.
     * @return String with customer details.
     */
    virtual std::string getInfo() const = 0;

    /**
     * @brief Get the type of customer.
     * @return CustomerType enum.
     */
    virtual CustomerType getType() const = 0;

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }

    /**
     * @brief Stream insertion operator.
     */
    friend std::ostream& operator<<(std::ostream& os, const Customer& c) {
        os << c.getInfo();
        return os;
    }
};

/**
 * @class PrivateCustomer
 * @brief Represents an individual customer with an ID Card number.
 */
class PrivateCustomer : public Customer {
private:
    std::string idCardNumber; ///< ID Card Number

public:
    /**
     * @brief Default Constructor.
     */
    PrivateCustomer() : Customer(), idCardNumber("Unknown") {}

    /**
     * @brief Parametric Constructor.
     * @param name Full Name.
     * @param addr Address.
     * @param idCard ID Card Number (used as System ID).
     * @throws std::invalid_argument If validation fails.
     */
    PrivateCustomer(const std::string& name, const std::string& addr, const std::string& idCard)
        : Customer(idCard, name, addr), idCardNumber(idCard)
    {
        if (idCardNumber.empty()) throw std::invalid_argument("ID Card number cannot be empty.");
    }

    std::string getInfo() const override {
        std::stringstream ss;
        ss << "Private Customer [" << id << "]: " << name << "\n"
           << "  Address: " << address << "\n"
           << "  ID Card: " << idCardNumber;
        return ss.str();
    }

    CustomerType getType() const override {
        return CustomerType::Private;
    }

    std::string getIdCardNumber() const { return idCardNumber; }
};

/**
 * @class BusinessCustomer
 * @brief Represents a business customer with a NIP (Tax ID).
 */
class BusinessCustomer : public Customer {
private:
    std::string nip; ///< Tax Identification Number (NIP)

public:
    /**
     * @brief Default Constructor.
     */
    BusinessCustomer() : Customer(), nip("Unknown") {}

    /**
     * @brief Parametric Constructor.
     * @param name Company Name.
     * @param addr Address.
     * @param nipVal NIP number (used as System ID).
     * @throws std::invalid_argument If validation fails.
     */
    BusinessCustomer(const std::string& name, const std::string& addr, const std::string& nipVal)
        : Customer(nipVal, name, addr), nip(nipVal)
    {
        if (nip.empty()) throw std::invalid_argument("NIP cannot be empty.");
    }

    std::string getInfo() const override {
        std::stringstream ss;
        ss << "Business Customer [" << id << "]: " << name << "\n"
           << "  Address: " << address << "\n"
           << "  NIP: " << nip;
        return ss.str();
    }

    CustomerType getType() const override {return CustomerType::Business;}

    std::string getNip() const { return nip; }
};

} // namespace bk
