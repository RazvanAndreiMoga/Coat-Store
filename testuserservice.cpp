

#include "testuserservice.h"
#include <cassert>

void testUserService() {

    vector<Coat> adminRepoVector;
    adminRepoVector.reserve(10);
    Repository repo{ adminRepoVector };
    repo.initialiseRepo();
    vector<Coat> userRepoVector;
    userRepoVector.reserve(10);
    UserRepository userRepo{ userRepoVector };
    UserService userService{ repo, userRepo };
    assert(userService.getNrElemsUserService() == 0);
    //assert(userService.getCapUserService() == 10);
    Coat coat = repo.getAllRepo()[0];
    userService.addUserService(coat);
    assert(userService.getNrElemsUserService() == 1);
    assert(userService.getAllUserService()[0].colourGetter() == "Black");
    userService.addUserService(coat);
    Coat coat2 = Coat("Large", "Black", 1, 1, "https://www.unsplash.com/photos/1M5X5kyB6uc");
    userService.addUserService(coat2);
    Coat * validCoats1 = new Coat[10];
    string empty;
    empty[0] = '\0';
    int counter1 = userService.getFiltered(validCoats1, empty);
    assert(counter1 == 9);
    Coat * validCoats2 = new Coat[10];
    int counter2 = userService.getFiltered(validCoats2, "Small");
    assert(counter2 == 3);
}