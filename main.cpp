#include <iostream>
#include <string>
#include <vector>

// Șablonul Factory
class Property {
public:
    virtual void displayInfo() const = 0;
};

class Apartment : public Property {
public:
    void displayInfo() const override {
        std::cout << "Apartment: Spacious living area, kitchen, and bedrooms." << std::endl;
    }
};

class House : public Property {
public:
    void displayInfo() const override {
        std::cout << "House: Private property with a yard and multiple rooms." << std::endl;
    }
};

class Condo : public Property {
public:
    void displayInfo() const override {
        std::cout << "Condo: Shared building with individual units." << std::endl;
    }
};

class PropertyFactory {
public:
    static Property* createProperty(const std::string& type) {
        if (type == "Apartment") {
            return new Apartment();
        } else if (type == "House") {
            return new House();
        } else if (type == "Condo") {
            return new Condo();
        } else {
            return nullptr;
        }
    }
};

// Șablonul Observer
class Observer {
public:
    virtual void update(const std::string& message) = 0;
};

class User : public Observer {
private:
    std::string username;

public:
    User(const std::string& name) : username(name) {}

    void update(const std::string& message) override {
        std::cout << "User " << username << " received update: " << message << std::endl;
    }

    // Public getter method for username
    std::string getUsername() const {
        return username;
    }
};

class PropertyListing {
private:
    std::vector<Observer*> observers;
    Property* property;

public:
    PropertyListing(Property* prop) : property(prop) {}

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyObservers(const std::string& message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }

    void setProperty(Property* prop) {
        property = prop;
        notifyObservers("Property has been updated.");
    }

    void displayInfo() const {
        property->displayInfo();
    }
};

// Clasa Template
template <typename T>
class Booking {
private:
    T* property;
    User* user;

public:
    Booking(T* prop, User* usr) : property(prop), user(usr) {}

    void displayBookingInfo() const {
        std::cout << "Booking Information: ";
        property->displayInfo();
        std::cout << "Booked by: " << user->getUsername() << std::endl;
    }
};

int main() {
    // Utilizare șablon Factory
    Property* apartment = PropertyFactory::createProperty("Apartment");
    Property* house = PropertyFactory::createProperty("House");
    Property* condo = PropertyFactory::createProperty("Condo");

    if (apartment) {
        apartment->displayInfo();
        delete apartment;
    }

    if (house) {
        house->displayInfo();
        delete house;
    }

    if (condo) {
        condo->displayInfo();
        delete condo;
    }

    // Utilizare șablon Observer
    User user1("Alice");
    User user2("Bob");

    PropertyListing propertyListing(new Apartment());
    propertyListing.addObserver(&user1);
    propertyListing.addObserver(&user2);

    propertyListing.displayInfo();

    propertyListing.setProperty(new House());
    propertyListing.displayInfo();

    // Utilizare clasă template
    Booking<Apartment> booking1(new Apartment(), &user1);
    Booking<House> booking2(new House(), &user2);

    booking1.displayBookingInfo();
    booking2.displayBookingInfo();

    return 0;
}
