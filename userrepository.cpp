#include "userrepository.h"
#include <fstream>

UserException::UserException(std::string& _message) : message(_message) {}

const char* UserException::what() const noexcept {
    return message.c_str();
}

UserRepository::UserRepository() = default;

UserRepository::UserRepository(vector<Coat>& shoppingBasket1) {
    this->shoppingBasket = shoppingBasket1;}


vector<Coat>& UserRepository::getAllUserRepo() {
    return this->shoppingBasket;
}

unsigned int UserRepository::getNrElems() {
    return this->shoppingBasket.size();
}

unsigned int UserRepository::getCap() {
    return this->shoppingBasket.capacity();
}

void UserRepository::addUserRepo(const Coat &Coat) {
    this->shoppingBasket.push_back(Coat);
}

void UserRepository::updateUserRepo(int update_index, const Coat& new_Coat) {
    //this->shoppingBasket.at(update_index).updateCoat(new_Coat);
    if (update_index == -1) {
        std::string error;
        error += std::string("The coat does not exist!");
        if (!error.empty())
            throw UserException(error);
    }
    this->shoppingBasket[update_index] = new_Coat;
    this->writeToFile();
}


unsigned int UserRepository::userfind(string size, string colour, string photograph) {
    int searched_index = -1;
    int index = 0;
    int length = this->getNrElems();
    while (index < length && searched_index == -1) {
        Coat someCoat = this->shoppingBasket.at(index);
        string other_size = someCoat.sizeGetter();
        string other_colour = someCoat.colourGetter();
        string other_photograph = someCoat.photoGetter();
        if (other_size == size && other_colour == colour && other_photograph == photograph)
            searched_index = index;
        index++;
    }
    return searched_index;
}



UserRepository::~UserRepository() = default;