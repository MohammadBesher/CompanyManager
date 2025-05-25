//
// Created by ahmad on 05/06/22.
//

#ifndef WET2_SPRING_COMPANYNODEUF_H
#define WET2_SPRING_COMPANYNODEUF_H

class Card;

class CompanyNodeUF {

public:

    int groupId;
    CompanyNodeUF *father;
    Card *card;
    long double value;

    CompanyNodeUF(int id,int value)
    {
        this->groupId = id;
        this->father = nullptr;
        this->card = nullptr;
        this->value = value;
    }

    ~CompanyNodeUF() = default;

};


#endif //WET2_SPRING_COMPANYNODEUF_H
