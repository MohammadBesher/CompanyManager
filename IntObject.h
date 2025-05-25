//
// Created by ahmad on 02/06/22.
//

#ifndef WET2_SPRING_INTOBJECT_H
#define WET2_SPRING_INTOBJECT_H

#include <memory>

class intObject {
public:
    long long num;

    intObject():num(0){};

    intObject(int num) : num(num) {}

//    intObject(intObject& other)
//    {
//        other.num = this->num;
//    }

    ~intObject() = default;

    bool operator>(intObject object) {
        if (this->num > object.num)
            return true;

        return false;
    }

    bool operator<(intObject object) {
        return !((*this) > object);
    }

    bool operator==(const intObject object) {

        return (this->num == object.num);
    }

    bool operator!=(intObject object) {
        return !((*this) == object);
    }

    intObject &operator=( intObject other)
    {
        if ((*this) == other)
            return (*this);

        this->num = other.num;
        return (*this);
    }

    friend intObject operator+( const intObject &other1,const intObject &other2)
    {
        return intObject(other1.num + other2.num);
    }
    friend intObject operator-( const intObject &other1,const intObject &other2)
    {
        return intObject(other1.num - other2.num);
    }

    friend std::ostream& operator<<(std::ostream& os, intObject const & object) {
        return os << object.num << std::endl;
    }


};

#endif //WET2_SPRING_INTOBJECT_H
