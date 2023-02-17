#pragma once
#include "service.h"
#include "userservice.h"
#include "validator.h"

class Console {
private:
    Service &service;
    UserService & userService;
    CoatValidator& validator;
public:
    Console(Service &service, UserService & userService, CoatValidator& validator);

    ///Method to check if a given string does not contain digits
    ///\param input - the string to be verified
    ///\return - true if it is valid, false otherwise
    //static bool validateString(string input);

    void addUi();

    void deleteUi();

    void updateUi();

    void listAll();

    void listAllUser();

    void listFilteredUser();

    void listshoppingBasket();

    void openFile();

    static void printAdministratorSubmenu();

    static void printUserSubmenu();

    void AdministratorMode();

    void UserMode();

    static void printMenu();

    void start();

    ~Console();
};

