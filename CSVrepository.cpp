#include <fstream>
#include "CSVrepository.h"
#include "repository.h"

CSVRepo::CSVRepo(const std::vector<Coat>& shoppingBasket, const std::string& userFilename) {
    this->shoppingBasket = shoppingBasket;
    this->userFilename = userFilename;
}

std::vector<Coat>& CSVRepo::getAllUserRepo() {
    return this->shoppingBasket;
}

unsigned int CSVRepo::getNrElems() {
    return this->shoppingBasket.size();
}

unsigned int CSVRepo::getCap() {
    return this->shoppingBasket.capacity();
}

std::string& CSVRepo::getFilename() {
    return this->userFilename;
}

void CSVRepo::addUserRepo(const Coat &coat) {
    this->shoppingBasket.push_back(coat);
    this->writeToFile();
}

void CSVRepo::updateUserRepo(int update_index, const Coat& new_Coat) {
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

void CSVRepo::deleteUserRepo(const Coat& coat) {
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

unsigned int CSVRepo::userfind(string size, string colour, string photograph) {
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

void CSVRepo::writeToFile() {
    std::ofstream fout(this->userFilename);
    if (!this->shoppingBasket.empty()) {
        for (const Coat& coat: this->shoppingBasket) {
            fout<<coat<<"\n";
        }
    }
    fout.close();
}

CSVRepo::~CSVRepo()=default;
