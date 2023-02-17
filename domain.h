#pragma once
#include <string>
using namespace std;

class Coat {
    private:
        string size;
        string colour;
        int price;
        int quantity;
        string photograph;
    public:

    ///Constructor method for the Coat class
    ///\param size - the size of the Coat, "empty" by default
    ///\param colour - the colour of the Coat, "empty" by default
    ///\param price - the price of the Coat, 0 by default
    ///\param photograph - the link of the photo of the Coat, "empty" by default
    Coat(string size = "empty", string colour = "empty", int price = 0, int quantity = 0, string photograph = "empty");

    ///Getter method for the size
    ///\return - the size of the Coat
    string sizeGetter() const;

    void sizeSetter(const string& new_size);

    ///Getter method for the colour
    ///\return - the colour of the Coat
    string colourGetter() const;

    void colourSetter(const string& new_colour);

    ///Getter method for the price
    ///\return - the price of the Coat
    int priceGetter() const;

    void priceSetter(const int& new_price);

    ///Getter method for the quantity
    ///\return - the quantity of the Coat
    int quantityGetter() const;

    void quantitySetter(const int& new_quantity);

    ///Getter method for the photograph
    ///\return - the link of the photo of the Coat
    string photoGetter() const;

    void photoSetter(const string& new_qunatity);

    ///Destructor of the class
    ~Coat();

    void updateCoat(Coat coat);

    ///Method to format an entity into a string
    ///\return - the string format of a Coat
    string toString() const;

    bool operator==(const Coat& coatToCheck) const;

    friend std::istream& operator>>(std::istream& inputStream, Coat& coat);

    friend std::ostream& operator<<(std::ostream& outputStream, const Coat& coatOutput);
};

