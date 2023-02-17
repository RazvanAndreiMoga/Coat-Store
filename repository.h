#pragma once
#include "dynamicarray.h"
#include <vector>
#include "domain.h"

class Repository {
private:
    //DynamicArray<Coat>* dynamicArray;
    vector<Coat> coats;
    string coatsFilename;
public:

    void loadCoatsFromFile();

    void writeCoatsToFile();
    
    ///Constructor for the Repository class
    ///\param repo_array - the dynamic array in which the Coats will be stored
    explicit Repository(vector<Coat>& repo_array, string& coat_filename);
    //Repository() {}

    ///Method to initialise the repository with a number of entities
    void initialiseRepo();

    ///Method to get all the elements of the repository
    ///\return - the array of elements
    //Coat * getAllRepo();
    vector<Coat>& getAllRepo();

    ///Method to get the number of elements in the repository
    ///\return - the number of elements
    int getNrElems();

    ///Method to get the capacity of the repository
    ///\return - the capacity
    int getCap();

    ///Method to add an element to the repository
    ///\param Coat - the entity to be added
    void addRepo(const Coat& Coat);

    ///Method to find an entity
    int find(string size, string colour, string photograph);

    ///Method to delete an entity based on its index
    ///\param delete_index - the index of the Coat to be deleted
    void deleteRepo(int delete_index);

    ///Method to update an entity based on its index with a new entity
    ///\param update_index - the index of the Coat to be updated
    ///\param new_Coat - the new Coat with which the update is done
    void updateRepo(int update_index, const Coat& new_Coat);

    ///Destructor
    ~Repository();
};

class RepositoryException : public std::exception {
private:
    std::string message;
public:
    explicit RepositoryException(std::string& _message);

    const char* what() const noexcept override;
};
