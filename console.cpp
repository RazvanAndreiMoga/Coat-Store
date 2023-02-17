#include "console.h"
#include <iostream>

using namespace std;

Console::Console(Service &service, UserService &userService, CoatValidator& validator1):service(service), userService(userService), validator(validator1) {
}

//bool Console::validateString(string input) {
//    for (int i = 0; i <input.length(); i++)
//        if (isdigit(input[i]) != false)
//            return false;
//    return true;
//}

void Console::addUi() {
    cout<<"Add a new Coat"<<endl;
    string size;
    string colour;
    string price_s;
    int price;
    string quantity_s;
    int quantity;
    string photograph;
    while (true) {
        try {
            std::cout << "Enter the size: " << std::endl;
            getline(std::cin, size);
            this->validator.validateSize(size);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the colour: " << std::endl;
            getline(std::cin, colour);
            this->validator.validateColour(colour);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the price: " << std::endl;
            getline(std::cin, price_s);
            this->validator.validatePriceString(price_s);
            price = stoi(price_s);
            this->validator.validatePrice(price);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the quantity: " << std::endl;
            getline(std::cin, quantity_s);
            this->validator.validateQuantityString(quantity_s);
            quantity = stoi(quantity_s);
            this->validator.validateQuantity(quantity);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the link to the photograph: " << std::endl;
            getline(std::cin, photograph);
            this->validator.validatePhotoLink(photograph);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    this->service.addService(size, colour, price, quantity, photograph);
    std::cout << "Coat added successfully!" << std::endl;
}

void Console::deleteUi() {
    cout<<"Delete a Coat"<<endl;
    string index_s;
    int index;
    while (true) {
        try {
            std::cout << "Enter the index: " << std::endl;
            getline(std::cin, index_s);
            this->validator.validatePriceString(index_s);
            index = stoi(index_s);
            this->validator.validatePrice(index);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    this->service.deleteService(index);
    std::cout << "Coat deleted successfully!" << std::endl;
}

void Console::updateUi() {
    cout<<"Update a Coat"<<endl;
    string index_s;
    int index;
    string new_size;
    string new_colour;
    string new_price_s;
    int new_price;
    string new_quantity_s;
    int new_quantity;
    string new_photograph;
    while (true) {
        try {
            std::cout << "Enter the index: " << std::endl;
            getline(std::cin, index_s);
            this->validator.validatePriceString(index_s);
            index = stoi(index_s);
            this->validator.validatePrice(index);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the size: " << std::endl;
            getline(std::cin, new_size);
            this->validator.validateSize(new_size);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the colour: " << std::endl;
            getline(std::cin, new_colour);
            this->validator.validateColour(new_colour);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the price: " << std::endl;
            getline(std::cin, new_price_s);
            this->validator.validatePriceString(new_price_s);
            new_price = stoi(new_price_s);
            this->validator.validatePrice(new_price);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the quantity: " << std::endl;
            getline(std::cin, new_quantity_s);
            this->validator.validateQuantityString(new_quantity_s);
            new_quantity = stoi(new_quantity_s);
            this->validator.validateQuantity(new_quantity);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the link to the photograph: " << std::endl;
            getline(std::cin, new_photograph);
            this->validator.validatePhotoLink(new_photograph);
            break;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    this->service.updateService(index, new_size, new_colour, new_price, new_quantity, new_photograph);
    std::cout << "Coat updated successfully!" << std::endl;
}

void Console::listAll() {
    vector<Coat> Coats = this->service.getAllService();
    int index = 0;
    int elemNo = this->service.getNrElemsService();
    if (elemNo == 0)
        throw "No Coats in the database!";
    for (const Coat& coat : Coats) {
        cout << index + 1 << ". " << Coats[index].toString() << endl;
        index++;
    }
}

void Console::listFilteredUser() {
    string size_filter;
    bool p = 1;
    int index;
    int sum = 0;
    try { vector<Coat> basket = this->userService.getAllUserService(); 
    }catch(UserException& ex) {
        //std::cout << ex.what() << std::endl;
        p = 0;
    }
    if (p) {
        vector<Coat> basket = this->userService.getAllUserService();        
        int elemNo = this->userService.getNrElemsUserService();
        for (index = 0; index < elemNo; index++)
            sum += basket[index].priceGetter();
    }
    cout << "Enter the size: " << endl;
    getline(cin, size_filter);
    if (!this->validator.validateString(size_filter)) {
        std::string error;
        error += std::string("Filter not valid!");
        if (!error.empty())
            throw ValidationException(error);
    }
    std::vector<Coat> validCoats;
    validCoats.reserve(this->service.getNrElemsService());
    this->userService.getFiltered(validCoats, size_filter);
    if (validCoats.empty()) {
        std::string error;
        error += std::string("The list of valid coats is empty!");
        if (!error.empty())
            throw UserException(error);
    }
    string option;
    bool done = false;
    index = 0;
    while (!done){
        if (validCoats.empty()) {
            std::string error;
            error += std::string("The list of valid coats is empty!");
            if (!error.empty())
                throw UserException(error);
        }
        if (index == validCoats.size())
            index = 0;
        std::cout << validCoats[index].toString() << std::endl;
        std::cout << "Buy? [Yes / No / exit]" << std::endl;
        std::string link = std::string("start ").append(validCoats[index].photoGetter());
        system(link.c_str());
        getline(std::cin, option);
        if (option == "Yes") {
            Coat coat = validCoats[index];
            sum += validCoats[index].priceGetter();
            cout << "Total sum: " << sum << endl;
            if (validCoats[index].quantityGetter() > 1) {
                this->userService.addUserService(coat);
                Coat new_coat = Coat(validCoats[index].sizeGetter(), validCoats[index].colourGetter(), validCoats[index].priceGetter(), validCoats[index].quantityGetter() - 1, validCoats[index].photoGetter());
                validCoats[index] = new_coat;
            }
            else {
                this->userService.addUserService(coat);
                for (int i = index; i < validCoats.size() - 1; i++)
                    validCoats[i] = validCoats[i + 1];
                //length--;
            }
        }
        else if (option == "No") {
            index++;
        }
        else if (option == "exit")
            done = true;
        else
            std::cout << "Invalid input!" << std::endl;
    }
}

void Console::listshoppingBasket() {
    vector<Coat> basket = this->userService.getAllUserService();
    int index = 0;
    int sum = 0;
    int elemNo = this->userService.getNrElemsUserService();
    if (elemNo == 0)
        throw "The shopping basket is empty!";
    for (const Coat &coat: basket) {
        cout << index + 1 << ". " << basket[index].toString() << endl;
        sum += basket[index].priceGetter();
        index++;
    }
    cout << "Total sum: " << sum << endl;
}

void Console::openFile() {
    std::string link = std::string("start ").append(this->userService.getFileService());
    system(link.c_str());
}

void Console::printAdministratorSubmenu() {
    cout<<"ADMINISTRATOR MENU: "<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"1. List all the Coats."<<endl;
    cout<<"2. Add a new Coat."<<endl;
    cout<<"3. Delete a Coat."<<endl;
    cout<<"4. Update a Coat."<<endl;
    cout<<"Choose an option: "<<endl;
}

void Console::printUserSubmenu() {
    cout<<"USER MENU: "<<endl;
    cout<<"0. Exit."<<endl;
    cout<<"1. See all the Coats, having a given size, one by one."<<endl;
    cout<<"2. See the shopping basket."<<endl;
    cout<<"3. See the shopping basket file." << std::endl;
    cout<<"Choose an option: "<<endl;
}

void Console::AdministratorMode() {
    cout<<"~You entered the administrator mode~"<<endl;
    bool done = false;
    while (!done) {
        try {
            printAdministratorSubmenu();
            string option;
            getline(cin, option);
            if (option == "0") {
                done = true;
                cout << "Exiting admin mode..." << endl;
            } else if (option == "1")
                this->listAll();
            else if (option == "2")
                this->addUi();
            else if (option == "3")
                this->deleteUi();
            else if (option == "4")
                this->updateUi();
            else
                cout << "Bad input!"<<endl;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
        catch (RepositoryException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
}

void Console::UserMode() {
    cout<<"~You entered the user mode~"<<endl;
    bool done = false;
    while(!done) {
        try {
            printUserSubmenu();
            string option;
            getline(cin, option);
            if (option == "0") {
                done = true;
                cout<<"Exiting user mode..."<<endl;
            }
            else if (option == "1")
                this->listFilteredUser();
            else if (option == "2")
                this->listshoppingBasket();
            else if (option == "3")
                this->openFile();
            else
                cout<<"Bad input!"<<endl;
        }
        catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
        catch (UserException& ex) {
            std::cout << ex.what() << std::endl;
        }
        catch (RepositoryException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
}

void Console::printMenu() {
    cout<<"MENU:"<<endl;
    cout<<"0. Exit."<<endl;
    cout<<"1. Administrator mode."<<endl;
    cout<<"2. User mode."<<endl;
    cout<<"Choose an option: "<<endl;
}

void Console::start() {
    cout<<"Proper Trench Coats store app"<<endl;
    int usermode = 0;
    bool done = false;
    while (!done) {
        printMenu();
        std::string option;
        getline(std::cin, option);
        if (option == "1")
            AdministratorMode();
        else if (option == "2") {
            if (usermode == 0) {
                std::cout << "Enter the type of the file in which you want to save the shopping basket(csv or html):" << std::endl;
                std::string fileType;
                while (true) {
                    try {
                        getline(std::cin, fileType);
                        this->userService.repositoryType(fileType);
                        break;
                    }
                    catch (UserException& ex) {
                        std::cout << ex.what() << std::endl;
                    }
                }
                usermode = 1;
            }
            UserMode();
        }
        else if (option == "0") {
            done = true;
            std::cout << "Goodbye!" << std::endl;
        }
        else
            std::cout << "Bad input!" << std::endl;
    }


}

Console::~Console() = default;