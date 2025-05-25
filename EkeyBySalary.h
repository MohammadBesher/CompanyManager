//
// Created by ahmad on 02/06/22.
//

#ifndef WET2_SPRING_EKEYBYSALARY_H
#define WET2_SPRING_EKEYBYSALARY_H


class EKeyBySalary{
        public:
        int employeeId;
        int salary;

        EKeyBySalary() = default;
        EKeyBySalary(int employeeId,int salary) : employeeId(employeeId) ,salary(salary)
        {

        }
        ~EKeyBySalary()= default;

        bool operator>(EKeyBySalary employee) {
            if (this->salary > employee.salary)
                return true;
            else {
                if (this->salary == employee.salary)
                {
                    if (this->employeeId == -2) // -2 means max id
                        return true;
                    else if (employee.employeeId == -2)
                        return false;
                    if (this->employeeId > employee.employeeId)
                        return true;
                    else
                        return false;
                }
                else
                    return false;
            }
        }

        bool operator<(EKeyBySalary employee) {
            return !((*this) > employee);
        }

        bool operator==(EKeyBySalary employee) {
            return ( this->salary == employee.salary && this->employeeId == employee.employeeId);
        }

        bool operator!=(EKeyBySalary employee) {
            return !((*this) == employee);
        }

        EKeyBySalary &operator=(const EKeyBySalary &other) = default;

        friend std::ostream& operator<<(std::ostream &os , const EKeyBySalary &key)
        {
            os << key.employeeId ;
            return os;
        }
};


#endif //WET2_SPRING_EKEYBYSALARY_H
