//
// Created by selen on 11/04/2021.
//

#include "validator.h"

ValidationException::ValidationException(std::string &_message): message(_message) {}

const char* ValidationException::what() const noexcept {
    return message.c_str();
}
CoatValidator::CoatValidator() = default;

bool CoatValidator::validateString(const std::string& input) {
    for (char i : input)
        if (isdigit(i) != false)
            return false;
    return true;
}

void CoatValidator::validateSize(const std::string& size) {
    std::string errors;
    if (!validateString(size))
        errors += std::string("The size input contains digits!");
    if (size.length() == 0)
        errors += std::string("The size input is empty!");
    if (!errors.empty())
        throw ValidationException(errors);
}

void CoatValidator::validateColour(const std::string& colour) {
    std::string errors;
    if (!validateString(colour))
        errors += std::string("The colour input contains digits!");
    if (colour.length() == 0)
        errors += std::string("The colour input is empty!");
    if (!errors.empty())
        throw ValidationException(errors);
}

void CoatValidator::validatePriceString(const std::string& price) {
    std::string errors;
    if (price.empty())
        errors += std::string("The price input is empty!");
    if (price.find_first_not_of("0123456789") != std::string::npos)
        errors += std::string("The price input has non-digit characters!");
    if(!errors.empty())
        throw ValidationException(errors);
}

void CoatValidator::validatePrice(int price) {
    std::string errors;
    if (price<0)
        errors += std::string("Price cannot be smaller than 0!");
    if(!errors.empty())
        throw ValidationException(errors);
}

void CoatValidator::validateQuantityString(const std::string& quantity) {
    std::string errors;
    if (quantity.empty())
        errors += std::string("The quantity input is empty!");
    if (quantity.find_first_not_of("0123456789") != std::string::npos)
        errors += std::string("The quantity input has non-digit characters!");
    if (!errors.empty())
        throw ValidationException(errors);
}

void CoatValidator::validateQuantity(int quantity) {
    std::string errors;
    if (quantity < 0)
        errors += std::string("Quantity cannot be smaller than 0!");
    if (!errors.empty())
        throw ValidationException(errors);
}


void CoatValidator::validatePhotoLink(const std::string& photograph) {
    std::string errors;
    if (photograph.length() == 0)
        errors += std::string("The link input is empty!");
    if (photograph.find("www") == std::string::npos)
        errors += std::string("The link is not a valid one!");
    if(!errors.empty())
        throw ValidationException(errors);
}

void CoatValidator::validateIndexString(const std::string& index) {
    std::string errors;
    if (index.empty())
        errors += std::string("The index input is empty!");
    if (index.find_first_not_of("0123456789") != std::string::npos)
        errors += std::string("The index input has non-digit characters!");
    if (!errors.empty())
        throw ValidationException(errors);
}

void CoatValidator::validateIndex(int index) {
    std::string errors;
    if (index < 0)
        errors += std::string("Index cannot be smaller than 0!");
    if (!errors.empty())
        throw ValidationException(errors);
}

CoatValidator::~CoatValidator()=default;