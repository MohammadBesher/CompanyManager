//
// Created by ahmad on 02/06/22.
//

#ifndef WET2_SPRING_CARD_H
#define WET2_SPRING_CARD_H

#include <cstdlib>
#include <memory>
#include "HashTable.h"
#include "RankTree.h"
#include "CompanyNodeUF.h"

class Card{

public:
    int groupId;
    int size;
    long double temp_value;
    CompanyNodeUF *node;


    Card()
    {
    }

    Card(int id,int value) : groupId(id), size(1)
    {
        this->node = new CompanyNodeUF(id,value);
        node->groupId = id;
        node->card = this;

    }

    ~Card()
    {
        if(node != nullptr)
            delete node;
        node = nullptr;
    }


};


#endif //WET2_SPRING_CARD_H
