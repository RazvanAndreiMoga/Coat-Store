#pragma once
#include "dynamicarray.h"
#include "vector"
#include "domain.h"

class UserRepository {
protected:
    //DynamicArray<Coat>* shoppingBasket;
    vector<Coat> shoppingBasket;
    std::string userFilename;
public:
    ///Constructor for the UserRepository class
    ///\param shoppingBasket1 - the list of Coats that the user is buying
    explicit UserRepository(vector<Coat>& shoppingBasket1);

    UserRepository();

    ///Method to get all the elements of the UserRepository
    ///\return - the list of elements from the UserRepository
    //Coat * getAllUserRepo();
    virtual vector<Coat>& getAllUserRepo()=0;

    ///Method to get the number of elements from the UserRepository
    ///\return - the number of elements
    virtual unsigned int getNrElems()=0;

    ///Method to get the capacity of the dynamic array used in the UserRepository
    ///\return - the capacity
    virtual unsigned int getCap()=0;

    ///Method to add an element to the UserRepository
    ///\param Coat - the element to be added
    virtual void addUserRepo(const Coat& Coat)=0;

    virtual void deleteUserRepo(const Coat& coat) = 0;

    virtual unsigned int userfind(string size, string colour, string photograph);

    virtual void updateUserRepo(int update_index, const Coat& new_Coat);

    virtual void writeToFile() = 0;

    virtual std::string& getFilename() = 0;

    ///Destructor
    ~UserRepository();
};

class UserException : public std::exception {
private:
    std::string message;
public:
    explicit UserException(std::string& _message);

    const char* what() const noexcept override;
};

