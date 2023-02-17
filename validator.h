#pragma once

#include "domain.h"

class ValidationException: public std::exception {
private:
    std::string message;
public:
    explicit ValidationException(std::string& _message);

    const char *what() const noexcept override;
};

class CoatValidator {
public:
    CoatValidator();

    bool validateString(const std::string& input);

    void validateSize(const std::string& size);

    void validateColour(const std::string& colour);

    void validatePriceString(const std::string& price);

    void validatePrice(int price);

    void validateQuantityString(const std::string& quantity);

    void validateQuantity(int quantity);

    void validatePhotoLink(const std::string& photograph);

    void validateIndexString(const std::string& index);

    void validateIndex(int index);

    ~CoatValidator();
};

