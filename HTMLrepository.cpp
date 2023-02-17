#include <fstream>
#include "HTMLrepository.h"
#include "repository.h"

HTMLRepo::HTMLRepo(const std::vector<Coat> &shoppingBasket, const std::string &userFilename) {
    this->shoppingBasket = shoppingBasket;
    this->userFilename = userFilename;
}

std::vector<Coat>& HTMLRepo::getAllUserRepo() {
    return this->shoppingBasket;
}

unsigned int HTMLRepo::getNrElems() {
    return this->shoppingBasket.size();
}

unsigned int HTMLRepo::getCap() {
    return this->shoppingBasket.capacity();
}

std::string& HTMLRepo::getFilename() {
    return this->userFilename;
}

void HTMLRepo::addUserRepo(const Coat &coat) {
    this->shoppingBasket.push_back(coat);
    this->writeToFile();
}

void HTMLRepo::updateUserRepo(int update_index, const Coat& new_Coat) {
    //this->shoppingBasket.at(update_index).updateCoat(new_Coat);
   /* if (update_index == -1) {
        std::string error;
        error += std::string("The coat does not exist!");
        if (!error.empty())
            throw RepositoryException(error);
    }*/
    this->shoppingBasket[update_index] = new_Coat;
    this->writeToFile();
}

void HTMLRepo::deleteUserRepo(const Coat& coat) {
    int index = this->userfind(coat.sizeGetter(), coat.colourGetter(), coat.photoGetter());
    if (index == -1) {
        std::string error;
        error += std::string("The coat does not exist!");
        if (!error.empty())
            throw RepositoryException(error);
    }
    this->shoppingBasket.erase(this->shoppingBasket.begin() + index);
    this->writeToFile();
}

unsigned int HTMLRepo::userfind(string size, string colour, string photograph) {
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

void HTMLRepo::writeToFile() {
    std::ofstream fout(this->userFilename);
    fout << "<!DOCTYPE html>\n<html><head><title>Shopping Basket</title></head><body>\n";
    fout << "<table border=\"1\">\n";
    fout << "<tr><td>Size</td><td>Colour</td><td>Price</td><td>Quantity</td><td>Link</td></tr>\n";
    for (const Coat& coat: this->shoppingBasket) {
        fout << "<tr><td>" << coat.sizeGetter() << "</td>"
                   << "<td>" << coat.colourGetter() << "</td>"
                   << "<td>" << std::to_string(coat.priceGetter()) << "</td>"
                   << "<td>" << std::to_string(coat.quantityGetter()) << "</td>"
                   << "<td><a href=\"" << coat.photoGetter() << "\">"<< coat.photoGetter()<<"</a></td>" << '\n';
    }
    fout << "</table></body></html>";
    fout.close();
}

HTMLRepo::~HTMLRepo()=default;
