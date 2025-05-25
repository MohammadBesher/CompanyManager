//
// Created by ahmad on 02/06/22.
//

#ifndef WET2_SPRING_EMPLOYEEMANAGER_H
#define WET2_SPRING_EMPLOYEEMANAGER_H


#include "library2.h"
#include "ArrData.h"

class EmployeeManager {
public:
    HashTable<EmployeeData> *employees_hash;
    RankTree<EKeyBySalary,intObject> *employees_tree;
    companyUf* companies;
    //std::shared_ptr<ArrData>* arr;
    ArrData** arr;
    int sumGrade;
    int num_of_compaines;
    int employees_with_zero_Salary;


    EmployeeManager() = default;
    EmployeeManager(int k);

    ~EmployeeManager();

    StatusType AddEmployee( int employeeID, int companyID, int grade);


    StatusType
    RemoveEmployee( int employeeID);

    StatusType AcquireCompany( int companyID1, int companyID2, double factor);

    StatusType EmployeeSalaryIncrease( int employeeID, int salaryIncrease);

    StatusType PromoteEmployee( int employeeID, int bumpGrade);

    StatusType SumOfBumpGradeBetweenTopWorkersByGroup( int companyID, int m);

    StatusType AverageBumpGradeBetweenSalaryByGroup( int companyID, int lowerSalary, int higherSalary);

    StatusType CompanyValue( int companyID);
    StatusType BumpGradeToEmployees( int lowerSalary, int higherSalary, int bumpGrade);



};


#endif //WET2_SPRING_EMPLOYEEMANAGER_H
