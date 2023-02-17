//#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <stdlib.h>
#include <crtdbg.h>
#include "dynamicarray.h"
#include "repository.h"
#include "service.h"
#include "console.h"
#include "testdomain.h"
#include "testdynamicarray.h"
#include "testrepository.h"
#include "testuserrepository.h"
#include "testservice.h"
#include "testuserservice.h"
#include "comparator.h"
#include "GUI.h"

//void testAll() {
//    testDomain();
//    testDynamicArray();
//    testAdminRepository();
//    testUserRepository();
//    testAdminService();
//    testUserService();
//}


void test_all() {

    list<Coat>coats;
    coats.push_back(Coat("Medium", "Blue", 10, 6, "www.test1.ro"));
    coats.push_back(Coat("Large", "Pink", 15, 56, "www.test2.ro"));
    coats.push_back(Coat("Small", "Red", 5, 123, "www.test3.ro"));
    ComparatorAscendingByPrice<Coat>cmp;
    coats.sort(cmp);
    assert(coats.front().priceGetter() == 5);
    assert(coats.back().priceGetter() == 15);
    ComparatorDescendingByQuantity<Coat>cmp2;
    coats.sort(cmp2);
    assert(coats.front().quantityGetter() == 123);
    assert(coats.back().quantityGetter() == 6);
    printf("Tests done !\n");
}


int main(int argc, char* argv[]) {
    test_all();
    QApplication a(argc, argv);
    std::vector<Coat> adminRepoVector;
    adminRepoVector.reserve(10);
    std::string filename = R"(C:\Users\razva\Desktop\t2oop\QtWidgetsApplication1\coats.txt)";
    Repository repo{ adminRepoVector, filename };
    repo.initialiseRepo();
    Service service{ repo };
    UserService userService{ repo };
    CoatValidator validator{};
    /*Console console{ service, userService, validator };
    console.start();*/
    GUI gui{ service, userService, validator, repo };
    gui.show();
    return a.exec();
    _CrtDumpMemoryLeaks();
    return 0;

    //auto * vector1 = new vector<Coat>(10);
    //auto* repo = new Repository(vector1);
    //repo->initialiseRepo();
    //auto * vector2 = new vector<Coat>(10);
    //auto *userRepo = new UserRepository(vector2);
    //auto* service = new Service(repo);
    //auto * userService = new UserService(repo, userRepo);
    //auto* console = new Console(service, userService);
    //console->start();
    //return 0;
}



