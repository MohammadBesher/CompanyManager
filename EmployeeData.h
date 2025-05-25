//
// Created by ahmad on 02/06/22.
//

#ifndef WET2_SPRING_EMPLOYEEDATA_H
#define WET2_SPRING_EMPLOYEEDATA_H


class EmployeeData{
public:
    int employeeId;
    int salary;
    int grade;
    int company_id;

    EmployeeData() =default;
    ~EmployeeData() = default;
    EmployeeData(int employeeId,int salary,int grade,int company_id) : employeeId(employeeId), salary(salary), grade(grade),company_id(company_id)
    {

    }


};;


#endif //WET2_SPRING_EMPLOYEEDATA_H
