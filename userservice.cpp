#include "userservice.h"
#include <algorithm>
#include <iterator>
#include "CSVrepository.h"
#include "HTMLrepository.h"


UserService::UserService(Repository& repository1, UserRepository *userRepository1):repository(repository1) {   
    this->userRepository = userRepository1;
}

UserService::UserService(Repository& repository1): repository(repository1) {}

vector<Coat> UserService::getAllUserService() {
    if (this->userRepository->getAllUserRepo().empty()) {
        std::string error;
        error += std::string("The shopping basket is empty!");
        if (!error.empty())
            throw UserException(error);
    }
    return this->userRepository->getAllUserRepo();}

int UserService::getNrElemsUserService() {
    return this->userRepository->getNrElems();
}

int UserService::getCapUserService() {
    return this->userRepository->getCap();
}

std::string& UserService::getFileService() {
    return this->userRepository->getFilename();
}

void UserService::repositoryType(const std::string& fileType) {
    if (fileType == "csv") {
        std::vector<Coat> userVector;
        std::string userFile = R"(C:\Users\razva\Desktop\A5-6\A5-6\ShoppingBasket.csv)";
        auto* repo = new CSVRepo{ userVector, userFile };
        this->userRepository = repo;
    }
    else if (fileType == "html") {
        std::vector<Coat> userVector;
        std::string userFile = R"(C:\Users\razva\Desktop\A5-6\A5-6\ShoppingBasket.html)";
        auto* repo = new HTMLRepo{ userVector, userFile };
        this->userRepository = repo;
    }
    else {
        std::string error;
        error += std::string("The filename is invalid!");
        if (!error.empty())
            throw UserException(error);
    }
}

void UserService::addUserService(Coat coat) {
    
    string size = coat.sizeGetter();
    string colour = coat.colourGetter();
    string photograph = coat.photoGetter();
    int quantity = coat.quantityGetter();
    int price = coat.priceGetter();

    Coat new_coat1 = Coat(size, colour, price, 1, photograph);


    int search_index = this->userRepository->userfind(size, colour, photograph);

    if (search_index != -1) {
        
        vector<Coat> coats = this->userRepository->getAllUserRepo();
        
        Coat new_coat2 = Coat(size, colour, price, coats[search_index].quantityGetter() + 1, photograph);

        this->userRepository->updateUserRepo(search_index, new_coat2);
        
    }
    else
        this->userRepository->addUserRepo(new_coat1);

    if (quantity > 1) {
        int update_index = this->repository.find(size, colour, photograph);
        Coat new_Coat = Coat(size, colour, price, quantity - 1, photograph);
        this->repository.updateRepo(update_index, new_Coat);
    }
    else {
        int delete_index = this->repository.find(size, colour, photograph);
        this->repository.deleteRepo(delete_index);
    }
}

int UserService::getFiltered(vector<Coat>& valid_Coats, string filter_string) {
    int index;
    int counter = 0;
    int length = this->repository.getNrElems();
    vector<Coat> data;
    data.reserve(this->repository.getNrElems());
    data = this->repository.getAllRepo();
    if (filter_string[0] == '\0')
        copy_if(data.begin(), data.end(), back_inserter(valid_Coats), [&filter_string](Coat& coat) {return true; });
        /*for (index = 0; index < length; index++) {
            Coat Coat = this->repository.getAllRepo()[index];
            valid_Coats[counter] = Coat;
            counter++;
            
        }*/
    else {
        copy_if(data.begin(), data.end(), back_inserter(valid_Coats), [&filter_string](Coat& coat) {return coat.sizeGetter() == filter_string; });
        /*for (index = 0; index < length; index++) {
            Coat Coat = this->repository.getAllRepo()[index];
            if (filter_string == Coat.sizeGetter()) {
                valid_Coats[counter] = Coat;
                counter++;
            }
        }*/
    }
    return counter;
}

UserRepository* UserService::getUserRepo() {
    return this->userRepository;
}

UserService::~UserService() = default;