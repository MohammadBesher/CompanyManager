//
// Created by ahmad on 02/06/22.
//

#ifndef WET2_SPRING_ARRDATA_H
#define WET2_SPRING_ARRDATA_H

#include "CompanyUF.h"
#include "EmployeeData.h"
#include "EkeyBySalary.h"
#include "IntObject.h"
#include <cstdlib>
#include <memory>



class ArrData {
public:
    HashTable<EmployeeData>* employees_hash_arr;
    RankTree<EKeyBySalary,intObject>* employees_tree_arr;
    int sum_grades_arr;
    int employees_with_zero_Salary_arr;

    ArrData()
    {
        this->employees_hash_arr = new HashTable<EmployeeData>();
        this->employees_tree_arr = new RankTree<EKeyBySalary,intObject>();
        this->sum_grades_arr = 0;
        this->employees_with_zero_Salary_arr = 0;
    }

    ~ArrData()
    {
        //delete this->employees_hash_arr;
        //this->employees_tree_arr->treeClear();
        //delete this->employees_tree_arr;
    }

};


#endif //WET2_SPRING_ARRDATA_H
