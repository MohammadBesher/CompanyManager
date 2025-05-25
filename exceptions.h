//
// Created by ahmad on 02/06/22.
//

#ifndef WET2_SPRING_EXCEPTIONS_H
#define WET2_SPRING_EXCEPTIONS_H


#include <stdexcept>


class AlreadyExist :public std::exception{};

class DoNotExist :public std::exception{};

class InvalidInput :public std::exception{};

class AllocatonError :public std::exception{};


#endif //WET2_SPRING_EXCEPTIONS_H
