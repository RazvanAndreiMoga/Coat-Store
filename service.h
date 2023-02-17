#pragma once
#include "repository.h"
#include <memory>
#include "undoredo.h"

class Service{
private:
    Repository& repository;
    std::vector<std::shared_ptr<UndoRedoAction>> undoAdmin;
    std::vector<std::shared_ptr<UndoRedoAction>> redoAdmin;
public:
    ///Constructor for the Service class
    ///\param repo - the admin repository
    explicit Service(Repository& repo);

    ///Method to get all the elements of the repository
    ///\return - the elements from the repository
    //Coat * getAllService();
    vector<Coat> getAllService();

    ///Method to get the number of elements from the repository
    ///\return - the number of elements from the repository
    int getNrElemsService();

    ///Method to get the capacity of the repository
    ///\return - the capacity
    int getCapService();

    ///Method to add an element to the repository
    ///\param size - the size of the Coat
    ///\param colour - the colour of the Coat
    ///\param price - the price of the Coat
    ///\param photograph - the link of the photograph of the Coat
    ///\return - 1 if not added, 0 otherwise
    int addService(string size, string colour, int price, int quantity, string photograph);

    ///Method to delete an element from the repository
    ///\param colour - the colour of the Coat to be deleted
    ///\return - 1 if not deleted, 0 otherwise
    int deleteService(int index);

    ///Method to update an element from the repository
    ///\param old_colour - the old colour of the Coat
    ///\param new_size - the new size of the Coat
    ///\param new_colour - the new colour of the Coat
    ///\param new_price - the new price of the Coat
    ///\param new_photo - the new link to the photograph
    ///\return - 1 if not updated, 0 otherwise
    int updateService(int index, string new_size, string new_colour, int new_price, int new_quantity, string new_photo);

    void undoLastAction();
    void redoLastAction();
    void clearUndoRedo();
    ///Destructor
    ~Service();
};
