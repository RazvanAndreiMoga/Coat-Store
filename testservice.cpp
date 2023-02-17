
#include "testservice.h"
#include <cassert>

void testAdminService() {
    vector<Coat> adminRepoVector;
    adminRepoVector.reserve(10);
    Repository repo{ adminRepoVector };
    repo.initialiseRepo();
    Service service{ repo };    
    assert(service.getAllService()[0].colourGetter() == "Black");
    //assert(service.getCapService() == 10);
    assert(service.getNrElemsService() == 10);
    int added = service.addService("Medium", "Blue", 10, 1, "https://www.unsplash.com/photos/ziubUDopHmc");
    assert(added == 0);
    assert(service.getNrElemsService() == 11);
    //assert(service.getCapService() == 20);
    added = service.addService("Medium", "Blue", 10, 1, "https://www.unsplash.com/photos/ziubUDopHmc");
    assert(added == 1);
    int deleted = service.deleteService(1);
    assert(deleted == 0);
    assert(service.getNrElemsService() == 10);
    deleted = service.deleteService(0);
    assert(deleted == 1);
    int updated = service.updateService(1, "Medium", "Red", 2, 1, "https://www.unsplash.com/photos/ziubUDopHmc");
    assert(updated == 0);
    updated = service.updateService(0, "Medium", "Red", 2, 1, "https://www.unsplash.com/photos/ziubUDopHmc");
    assert(updated == 1);
}