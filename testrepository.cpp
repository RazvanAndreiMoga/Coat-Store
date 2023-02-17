
#include "testrepository.h"
#include <cassert>
#include<iostream>

void testAdminRepository() {
    vector<Coat> adminRepoVector;
    adminRepoVector.reserve(10);
    Repository repo{ adminRepoVector };
    repo.initialiseRepo();
    assert(repo.getNrElems() == 10);
    //cout << repo.getCap();
    //assert(repo.getCap() == 10);
    //cout << repo.getAllRepo()[0].colourGetter();
    assert(repo.getAllRepo()[0].colourGetter() == "Black");
    Coat Coat11 = Coat("Large", "Black", 10, 1, "https://www.unsplash.com/photos/9ix0Rvy2m5g");
    repo.addRepo(Coat11);
    //cout << repo.getNrElems();
    assert(repo.getNrElems() == 11);
    //cout << repo.getCap();
    //assert(repo.getCap() == 20);
    assert(repo.find("Medium", "Pink", "https://www.unsplash.com/photos/ziubUDopHmc") == 2);
    repo.deleteRepo(2);
    assert(repo.getNrElems() == 10);
    Coat Coat12 = Coat("Small", "Pink", 11, 1, "https://www.unsplash.com/photos/ziubUDopHmc");
    repo.updateRepo(9, Coat12);
    assert(repo.getAllRepo()[9].colourGetter() == "Pink");
    assert(repo.getAllRepo()[9].priceGetter() == 11);
}
