//
// Created by ahmad on 02/06/22.
//

#ifndef WET2_SPRING_COMPANYUF_H
#define WET2_SPRING_COMPANYUF_H

#include "Card.h"


class companyUf{

public:

    int size;
    Card **arrUF;

    companyUf(int k)
    {
        arrUF = new Card* [k + 1];

        this->size = k + 1;
        arrUF[0] = nullptr;
        for (int i = 1; i < k + 1; i++)
        {
            auto *new_card = new Card(i,i);
            new_card->node->card = new_card;
            this->arrUF[i] = new_card;

        }

    }

    ~companyUf()
    {
        for (int i = 1; i < size; i++)
        {
            delete arrUF[i];
        }

        delete [] arrUF;
        arrUF = nullptr;
    }

    Card* Find(int id) // return group node
    {
        if(id > size - 1)
            return nullptr;
        CompanyNodeUF *root = this->arrUF[id]->node;
        double sum =0;
        double old_val=0;
        while(root->father != nullptr)
        {
            sum += root->value;
            root = root->father;

        }

        root->card->temp_value= sum +root->value;
        if (root != nullptr && this->arrUF[id]->node->father != nullptr )
        {
            CompanyNodeUF *node = this->arrUF[id]->node;
            CompanyNodeUF *temp = this->arrUF[id]->node;
            while (temp->father != root)
            {
                temp = temp->father;
                node->father = root;
                old_val= node->value;
                sum -= old_val;
                node->value += sum;
                node = temp;
            }
        }
        return root->card;
    }

    //Aux function to merge the score array ;
    void mergeArray(int arr[] , int old_arr[])
    {
        for (int i = 0; i < 200; ++i)
        {
            arr[i] += old_arr[i];
            old_arr[i] = 0;
        }
    }

    Card* Union(int group1_id, int group2_id,double val)
    {

        if(group1_id > size || group2_id >size)
            return nullptr;

        CompanyNodeUF *root1 = this->arrUF[group1_id]->node;
        while(root1->father != nullptr)
        {
            root1 = root1->father;

        }

        CompanyNodeUF *root2 = this->arrUF[group2_id]->node;
        while(root2->father != nullptr)
        {
            root2 = root2->father;

        }
        if((this->arrUF[group1_id])->size < (this->arrUF[group2_id])->size )
        {


            root1->father = root2;
            this->arrUF[group2_id]->size += this->arrUF[group1_id]->size;
            root1->value =  root1->value + val - root2->value;
            this->arrUF[group2_id]->groupId = group1_id;
            this->arrUF[group1_id]->groupId = group1_id;
            root2->card->groupId = group1_id;
            root1->card->groupId = group1_id;
            return this->arrUF[group2_id];
            //merge the rank trees;

        }
        else
        {

            root2->father = root1;
            this->arrUF[group1_id]->size += this->arrUF[group2_id]->size;
            root1->value +=  val;
            root2->value -=  root1->value ;
            this->arrUF[group2_id]->groupId = group1_id;
            this->arrUF[group1_id]->groupId = group1_id;
            root1->card->groupId = group1_id;
            root2->card->groupId = group1_id;
            return this->arrUF[group1_id];

        }

    }
};


#endif //WET2_SPRING_COMPANYUF_H
