

#include "testuserrepository.h"
#include <cassert>
#include<iostream>

void testUserRepository() {

    vector<Coat> adminRepoVector;
    adminRepoVector.reserve(2);
    UserRepository userRepository{ adminRepoVector };
    //cout << userRepository.getCap();
    //assert(userRepository.getCap() == 2);
    Coat Coat1 = Coat("German Shepherd", "Bond", 1, 1, "https://www.wowwow.ro/ciobanesc-german-caine/2145#");
    Coat Coat2 = Coat("BullCoat", "Yoda", 5, 1, "https://www.wowwow.ro/bullCoat-caine/2139");
    userRepository.addUserRepo(Coat1);
    assert(userRepository.getNrElems() == 1);
    userRepository.addUserRepo(Coat2);
    assert(userRepository.getAllUserRepo()[0].priceGetter() == 1);
    assert(userRepository.getAllUserRepo()[1].colourGetter() == "Yoda");
}