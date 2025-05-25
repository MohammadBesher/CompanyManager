//
// Created by ahmad on 02/06/22.
//

#include "EmployeeManager.h"
#include <memory>


void *Init(int k){
    EmployeeManager *DS ;
    try {
        DS = new EmployeeManager(k);
    } catch (std::bad_alloc &e) {
        DS = nullptr;
    }
    return (void *) DS;

}
StatusType AddEmployee(void *DS, int employeeID, int companyID, int grade){
    if (DS == nullptr || companyID <= 0 || grade <0 || employeeID <=0 )
        return INVALID_INPUT;
    return ((EmployeeManager *) DS)->AddEmployee(employeeID,companyID,grade);

}

StatusType RemoveEmployee(void *DS, int employeeID){
    if (DS == nullptr || employeeID <=0 )
        return INVALID_INPUT;
    return ((EmployeeManager *) DS)->RemoveEmployee(employeeID);
}

StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor){

    if (DS == nullptr || companyID1 <=0 || companyID2 < 0 ||factor <= 0.0 )
        return INVALID_INPUT;
    return ((EmployeeManager *) DS)->AcquireCompany(companyID1,companyID2,factor);
}

StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease){
    if (DS == nullptr || employeeID <= 0 ||  salaryIncrease <=0 )
        return INVALID_INPUT;
    return ((EmployeeManager *) DS)->EmployeeSalaryIncrease(employeeID,salaryIncrease);

}

StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade){
    if (DS == nullptr || employeeID <= 0  )
        return INVALID_INPUT;
    return ((EmployeeManager *) DS)->PromoteEmployee(employeeID,bumpGrade);
}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m){
    if (DS == nullptr || companyID <0 || m <= 0 )
        return INVALID_INPUT;
    return ((EmployeeManager *) DS)->SumOfBumpGradeBetweenTopWorkersByGroup(companyID,m);
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary){
    if (DS == nullptr || companyID <0 || lowerSalary < 0  || higherSalary < 0 || higherSalary < lowerSalary)
        return INVALID_INPUT;
    return ((EmployeeManager *) DS)->AverageBumpGradeBetweenSalaryByGroup(companyID,lowerSalary,higherSalary);
}

StatusType CompanyValue(void *DS, int companyID){
    if (DS == nullptr || companyID <= 0)
        return INVALID_INPUT;
    return ((EmployeeManager *) DS)->CompanyValue(companyID);
}
StatusType BumpGradeToEmployees(void *DS, int lowerSalary, int higherSalary, int bumpGrade){
    if (DS == nullptr || higherSalary < lowerSalary || bumpGrade < 0)
        return INVALID_INPUT;
    return ((EmployeeManager *) DS)->BumpGradeToEmployees(lowerSalary,higherSalary,bumpGrade);
}


void Quit(void** DS)
{
    delete (EmployeeManager *)(*DS);
    (*DS) = nullptr;
}
