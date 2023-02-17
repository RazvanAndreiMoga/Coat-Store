#include "repository.h"
#include <algorithm>
#include <fstream>

RepositoryException::RepositoryException(std::string& _message) : message(_message) {}

const char* RepositoryException::what() const noexcept {
    return message.c_str();
}

Repository::Repository(vector<Coat>& repo_array, string& coat_filename) {
    this->coats = repo_array; 
    this->coatsFilename = coat_filename;
}

void Repository::loadCoatsFromFile() {
    if (!this->coatsFilename.empty()) {
        Coat coatFromFile;
        std::ifstream fin(this->coatsFilename);
        while (fin >> coatFromFile) {
            if (std::find(this->coats.begin(), this->coats.end(), coatFromFile) ==
                this->coats.end())
                this->coats.push_back(coatFromFile);
        }
        fin.close();
    }
}

void Repository::writeCoatsToFile() {
    if (!this->coatsFilename.empty()) {
        std::ofstream fout(this->coatsFilename);
        for (const Coat& coat : this->coats) {
            fout << coat << "\n";
        }
        fout.close();
    }
}

void Repository::initialiseRepo() {
    this->loadCoatsFromFile();
    //Coat Coat1 = Coat("Large", "Black", 100, 10, "https://www.unsplash.com/photos/1M5X5kyB6uc");
    //Coat Coat2 = Coat("Small", "Yellow", 500, 24, "https://www.unsplash.com/photos/7s5WyvsMtNc");
    //Coat Coat3 = Coat("Medium", "Pink", 350, 3, "https://www.unsplash.com/photos/ziubUDopHmc");
    //Coat Coat4 = Coat("Large", "Gray", 280, 4, "https://www.unsplash.com/photos/fYXGEXyaXyM");
    //Coat Coat5 = Coat("Medium", "Blue", 775, 5, "https://www.unsplash.com/photos/4nsADl_RhW4");
    //Coat Coat6 = Coat("Small", "Black", 430, 85, "https://www.unsplash.com/photos/Yh3DxI5ThUo");
    //Coat Coat7 = Coat("Medium", "White", 190, 10, "https://www.unsplash.com/photos/9ix0Rvy2m5g");
    //Coat Coat8 = Coat("Large", "Orange", 353, 37, "https://www.unsplash.com/photos/FJst_OBiFhY");
    //Coat Coat9 = Coat("Large", "Green", 600, 16, "https://www.unsplash.com/photos/M7hQ60IGlos");
    //Coat Coat10 = Coat("Small", "Purple", 1123, 19, "https://www.unsplash.com/photos/eSaTQ2F8qzQ");
    ////this->dynamicArray->addElem(Coat1);    
    ////this->dynamicArray->addElem(Coat2);
    ////this->dynamicArray->addElem(Coat3);
    ////this->dynamicArray->addElem(Coat4);
    ////this->dynamicArray->addElem(Coat5);
    ////this->dynamicArray->addElem(Coat6);
    ////this->dynamicArray->addElem(Coat7);
    ////this->dynamicArray->addElem(Coat8);
    ////this->dynamicArray->addElem(Coat9);
    ////this->dynamicArray->addElem(Coat10);
    //this->coats.push_back(Coat1);
    //this->coats.push_back(Coat2);
    //this->coats.push_back(Coat3);
    //this->coats.push_back(Coat4);
    //this->coats.push_back(Coat5);
    //this->coats.push_back(Coat6);
    //this->coats.push_back(Coat7);
    //this->coats.push_back(Coat8);
    //this->coats.push_back(Coat9);
    //this->coats.push_back(Coat10);
}

vector<Coat>& Repository::getAllRepo() {
    if (this->coats.empty()) {
        std::string error;
        error += std::string("The database is empty!");
        if (!error.empty())
            throw RepositoryException(error);
    }
    return this->coats;
}

int Repository::getNrElems() {
    //return this->dynamicArray->nrEntitiesGetter();
    if (this->coats.empty()) {
        std::string error;
        error += std::string("The database is empty!");
        if (!error.empty())
            throw RepositoryException(error);
    }
    return this->coats.size();
}

int Repository::getCap() {
    //return this->dynamicArray->capacityGetter();
    return this->coats.capacity();
}

void Repository::addRepo(const Coat& coat) {
    //this->dynamicArray->addElem(Coat);
    int existing = this->find(coat.sizeGetter(), coat.colourGetter(), coat.photoGetter());
    if (existing != -1) {
        std::string error;
        error += std::string("The coat already exists!");
        if (!error.empty())
            throw RepositoryException(error);
    }
    this->coats.push_back(coat);
    this->writeCoatsToFile();
}

int Repository::find(string size, string colour, string photograph) {
    int searched_index = -1;
    std::vector<Coat>::iterator it;
    it = std::find_if(this->coats.begin(), this->coats.end(), [&size, &colour, &photograph](Coat& coat) {return coat.sizeGetter() == size && coat.colourGetter() == colour && coat.photoGetter() == photograph; });
    if (it != this->coats.end())
    {
        searched_index = it - this->coats.begin();
    }
    return searched_index;
}

void Repository::deleteRepo(int delete_index) {
    //this->dynamicArray->deleteElem(delete_index);
    if (delete_index == -1) {
        std::string error;
        error += std::string("The coat does not exist!");
        if (!error.empty())
            throw RepositoryException(error);
    }
    this->coats.erase(this->coats.begin() + delete_index);
    this->writeCoatsToFile();
}

void Repository::updateRepo(int update_index, const Coat& new_Coat) {
    //this->dynamicArray->updateElem(update_index, new_Coat);
    if (update_index == -1) {
        std::string error;
        error += std::string("The coat does not exist!");
        if (!error.empty())
            throw RepositoryException(error);
    }
    this->coats[update_index] = new_Coat;
    this->writeCoatsToFile();
}

Repository::~Repository() = default;