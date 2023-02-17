#pragma once
#include "repository.h"
#include "userrepository.h"

class UserService {
private:
    Repository& repository;
    UserRepository* userRepository;
public:
    ///Constructor for the UserService class
    ///\param repository1 - the admin repository
    ///\param userRepository1 - the user repository
    UserService(Repository& repository1, UserRepository* userRepository1);

    explicit UserService(Repository& repository1);

    ///Method to get all the elements from the user repository
    ///\return - the elements from the user repository
    //Coat * getAllUserService();
    vector<Coat> getAllUserService();

    ///Method to get the number of elements from the user repository
    ///\return - the number of elements
    int getNrElemsUserService();

    ///Method to get the capacity of the user repository
    ///\return - the capacity
    int getCapUserService();

    ///Method to add a new Coat to the user repository
    ///\param Coat - the Coat to be added
    void addUserService(Coat Coat);

    void repositoryType(const std::string& fileType);

    std::string& getFileService();

    ///Method to get the filtered list of Coats based on their size and price
    ///\param valid_Coats - the array of valid Coats
    ///\param filter_string - the size filter
    ///\param price_filter - the price filter
    ///\return - the number of elements from the valid_Coats array
    int getFiltered(vector<Coat>& valid_Coats, string filter_string);

    UserRepository* getUserRepo();
  
    ///Destructor
    ~UserService();
};
