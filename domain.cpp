#include <utility>
#include <vector>
#include <sstream>
#include "domain.h"

Coat::Coat(string size, string colour, int price, int quantity, string photograph) {
    if (price < 0) {
        throw "price can't be smaller than 0!";
    }
    if (quantity < 0) {
        throw "quantity can't be smaller than 0!";
    }
    this->size = std::move(size);
    this->colour = std::move(colour);
    this->price = price;
    this->quantity = quantity;
    this->photograph = std::move(photograph);
}

void Coat::updateCoat(Coat coat) {
    this->colour = coat.colour;
    this->size = coat.size;
    this->price = coat.price;
    this->quantity = coat.quantity;
    this->photograph = coat.photograph;
}

string Coat::sizeGetter() const {
    return this->size;
}

void Coat::sizeSetter(const string& new_size) {
    this->size = new_size;
}

string Coat::colourGetter() const {
    return this->colour;
}

void Coat::colourSetter(const string& new_colour) {
    this->colour = new_colour;
}

int Coat::priceGetter() const {
    return this->price;
}

void Coat::priceSetter(const int& new_price) {
    this->price = new_price;
}

int Coat::quantityGetter() const {
    return this->quantity;
}

void Coat::quantitySetter(const int& new_quantity) {
    this->quantity = new_quantity;
}

string Coat::photoGetter() const {
    return this->photograph;
}

void Coat::photoSetter(const string& new_photo) {
    this->photograph = new_photo;
}

Coat::~Coat() = default;

string Coat::toString() const {
    auto str_price = to_string(this->price);
    auto str_quantity = to_string(this->quantity);
    return "size: " + this->size + " | colour: " + this->colour + " | price: " + str_price + " | quantity: " + str_quantity + " | Photograph link: " + this->photograph;
}

std::vector<std::string> tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

bool Coat::operator==(const Coat& coatToCheck) const {
    return (this->size == coatToCheck.size && this->colour == coatToCheck.colour && this->photograph == coatToCheck.photograph);
}

std::istream& operator>>(std::istream& inputStream, Coat& coat) {
    std::string line;
    std::getline(inputStream, line);
    std::vector<std::string> tokens;
    if (line.empty())
        return inputStream;
    tokens = tokenize(line, ',');
    coat.size = tokens[0];
    coat.colour = tokens[1];
    coat.price = std::stoi(tokens[2]);
    coat.quantity = std::stoi(tokens[3]);
    coat.photograph = tokens[4];
    return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Coat& coatOutput) {
    outputStream << coatOutput.size << "," << coatOutput.colour << "," << std::to_string(coatOutput.price) << "," << std::to_string(coatOutput.quantity) << "," << coatOutput.photograph;
    return outputStream;
}




