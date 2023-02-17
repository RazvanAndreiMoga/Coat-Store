#pragma once

#include "userrepository.h"

class CSVRepo: public UserRepository {
public:

    CSVRepo(const std::vector<Coat>& shoppingBasket, const std::string& userFilename);

    std::vector<Coat>& getAllUserRepo() override;

    unsigned int getNrElems() override;

    unsigned int getCap() override;

    void addUserRepo(const Coat &coat) override;

    unsigned int userfind(string size, string colour, string photograph) override;

    void updateUserRepo(int update_index, const Coat& new_Coat) override;

    void deleteUserRepo(const Coat& coat) override;

    void writeToFile() override;

    std::string& getFilename() override;

    ~CSVRepo();
};

