#ifndef HELPER_H
#define HELPER_H

#include <iostream>

class QStandardItemModel;

namespace Helper
{
QStandardItemModel* getPopulatedModel();

class Base
{
public:
    Base() = default;
    Base( std::string name, std::string secondName ):_name(name), _secondName(secondName)
    {
        std::cout<<"Custom Base Constructor with name: "<<_name<<" "<<_secondName<<std::endl;
    }
    ~Base()
    {
        std::cout<<"Custom Base Destructor"<<std::endl;
    }

    std::string getName() const {
        return _name+" "+_secondName ;
    }
protected:
    std::string _name;
    std::string _secondName;
};

class Derived
{
public:
    Derived() = default;

    Derived( std::string name ):_bigString( new std::string( "A very big string..." ) )
    {
        std::cout<<"Custom Derived Constructor"<<std::endl;
    }

    ~Derived()
    {
        std::cout<<"Custom Derived Destructor"<<std::endl;
        delete _bigString;
    }

    Derived( const Derived& d ):_bigString( new std::string( *d._bigString ) )
    {
        std::cout<<"Custom Copy Constructor"<<std::endl;
    }

    Derived& operator=( const Derived& d )
    {
        std::cout<<"Custom Copy Assignement"<<std::endl;
        delete _bigString;
        _bigString = new std::string( *d._bigString );
        return *this;
    }

    Derived( Derived&& d ):_bigString( d._bigString )    {
        std::cout << "Custom Move Constructor" << std::endl;
        d._bigString = nullptr;
    }

    Derived& operator=( Derived&& d )
    {
        std::cout<<"Custom Move Assignement"<<std::endl;
        delete _bigString;
        _bigString = d._bigString;
        d._bigString = nullptr;
        return *this;
    }

    void setBigString( const std::string& newBig )
    {
        *_bigString = newBig;
    }

    //std::string getName() const { return _name+" (derived)";}
    std::string getBigString() const { return *_bigString; }
private:
    std::string* _bigString;
};

}//end namespace


#endif // HELPER_H
