
#include "testdomain.h"
#include <cassert>
#include <cstring>

void testDomain() {
    Coat newCoat("Large", "Black", 5, 1, "https://unsplash.com/photos/eSaTQ2F8qzQ");
    assert(newCoat.sizeGetter() == "Large");
    assert(newCoat.colourGetter() == "Black");
    assert(newCoat.priceGetter() == 5);
    assert(newCoat.photoGetter() == "https://unsplash.com/photos/eSaTQ2F8qzQ");
    auto str_price = to_string(newCoat.priceGetter());
    string str = newCoat.toString();
    assert(str == "size: Large | colour: Black | price: 5 | quantity: 1 | Photograph link: https://unsplash.com/photos/eSaTQ2F8qzQ");
    try {
        Coat newInvalid("Large", "Black", -1, 1, "https://unsplash.com/photos/eSaTQ2F8qzQ");
    }catch (const char* msg) {
        assert(strcmp(msg, "price can't be smaller than 0!") == 0);
    }
    try {
        Coat newInvalid2("Large", "Black", 1, -1, "https://unsplash.com/photos/eSaTQ2F8qzQ");}
    catch (const char* msg2) {
        assert(strcmp(msg2, "quantity can't be smaller than 0!") == 0);
    }
    Coat newCoat3("Small", "White", 5, 1, "https://unsplash.com/");
    newCoat3.updateCoat(newCoat);
    assert(newCoat3.sizeGetter() == "Large");
}
