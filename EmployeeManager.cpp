//
// Created by ahmad on 02/06/22.
//

#include "EmployeeManager.h"

EmployeeManager::EmployeeManager(int k)//:arr(new std::shared_ptr<ArrData>[k+1])
{
    this->num_of_compaines = k;
    this->sumGrade = 0;
    this->employees_with_zero_Salary = 0;
    this->employees_hash = new HashTable<EmployeeData>();
    this->companies = new companyUf(k);
    this->employees_tree = new RankTree<EKeyBySalary , intObject>();
    this->arr = new ArrData*[k +1];
//    for (int i = 1; i < k+1 ; ++i) {
//        this->arr[i] = std::shared_ptr<ArrData>(new ArrData(i) );
//    }
    for (int i = 1; i < k+1 ; ++i) {
        this->arr[i] = new ArrData();
    }

}

EmployeeManager::~EmployeeManager() {
    delete this->employees_hash;
    employees_tree->treeClear();
    delete this->employees_tree;
    this->employees_tree = nullptr;
    delete this->companies;
    for (int i = 1; i <= this->num_of_compaines ; ++i) {
        if (this->arr[i] != nullptr)
        {
            this->arr[i]->employees_tree_arr->treeClear();
            delete this->arr[i]->employees_tree_arr;
            this->arr[i]->employees_tree_arr = nullptr;
            delete this->arr[i]->employees_hash_arr;
            delete this->arr[i];
            this->arr[i] = nullptr;
        }

    }
    delete []  this->arr;
    this->arr = nullptr;
}

StatusType EmployeeManager::AddEmployee(int employeeID, int companyID, int grade) {

    if (companyID > this->num_of_compaines || companyID <= 0 || grade <0 || employeeID <=0)
        return INVALID_INPUT;

    if (this->employees_hash->find(employeeID) != nullptr )
    {
        return FAILURE;
    }


    int company = this->companies->Find(companyID)->groupId;
    EmployeeData data(employeeID,0,grade,company);
    this->employees_hash->insert(employeeID,&data);

//    for (int i = 0; i < this->num_of_compaines; ++i) {
//        if (this->arr[i] != nullptr)
//            std::cout << "the company is here" << i << std::endl;
//    }
    this->arr[company]->employees_hash_arr->insert(employeeID,&data);

    this->employees_with_zero_Salary++;
    this->arr[company]->employees_with_zero_Salary_arr++;

    this->sumGrade += grade;
    this->arr[company]->sum_grades_arr += grade;
    return SUCCESS;
}

StatusType EmployeeManager::RemoveEmployee(int employeeID) {

    if (this->employees_hash->find(employeeID) == nullptr )
    {
        return FAILURE;
    }

    int company = this->employees_hash->find(employeeID)->company_id;
    int salary = this->employees_hash->find(employeeID)->salary;
    int grade = this->employees_hash->find(employeeID)->grade;
    if (salary == 0)
    {
        this->sumGrade -=grade;
        this->arr[company]->sum_grades_arr -= grade;
        this->arr[company]->employees_hash_arr->remove(employeeID);
        this->employees_hash->remove(employeeID);

        this->employees_with_zero_Salary--;
        this->arr[company]->employees_with_zero_Salary_arr--;

    } else{
        EKeyBySalary key(employeeID,salary);
        this->employees_tree->remove(key);
        this->arr[company]->employees_tree_arr->remove(key);
        this->arr[company]->employees_hash_arr->remove(employeeID);
        this->employees_hash->remove(employeeID);
    }
    return SUCCESS;
}

//merging two arrays to sorted array
 void mergeArrays(EKeyBySalary arr1[], EKeyBySalary arr2[], EKeyBySalary arr3[], int n1,int n2,
                 intObject arr4[], intObject arr5[],intObject arr6[])
{
    int i = 0, j = 0, k = 0;

    while (i<n1 && j <n2 && k <n1+n2)
    {
        if (arr1[i] < arr2[j])
        {
            arr3[k] = arr1[i];
            arr6[k] = arr4[i];
            i++;
            k++;
        }
        else {
            arr3[k] = arr2[j];
            arr6[k] = arr5[j];
            j++;
            k++;
        }
    }

    while (i < n1) {
        arr3[k] = arr1[i];
        arr6[k] = arr4[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr3[k] = arr2[j];
        arr6[k] = arr5[j];
        j++;
        k++;
    }
}

int hightUpdate(GNode<EKeyBySalary , intObject> *node )
{
    if (node == nullptr)
        return -1;

    node->height = hightUpdate(node->left_son) + 1;
    node->height = hightUpdate(node->right_son) + 1;
    return node->height;
}

void gradeSum_update(GNode<EKeyBySalary , intObject> *node )
{
    if(node == nullptr)
    {
        return;
    }

    gradeSum_update(node->left_son);
    gradeSum_update(node->right_son);
    node->grade_sum = node->get_gradeSum(node->left_son) + node->get_gradeSum(node->right_son) + node->data->num;
}

void numOfSonsUpdate(GNode<EKeyBySalary , intObject> *node )
{
    if(node == nullptr)
    {
        return;
    }

    numOfSonsUpdate(node->left_son);
    numOfSonsUpdate(node->right_son);
    node->sons_num = node->sonsNum(node->left_son) + node->sonsNum(node->right_son) + 1;

}

 RankTree<EKeyBySalary, intObject>* mergeTrees(RankTree<EKeyBySalary,intObject>* tree1,
                                               RankTree<EKeyBySalary,intObject>* tree2, int size1, int size2)
{

    auto array1_key = new EKeyBySalary[size1];
    auto array2_key = new EKeyBySalary[size2];
    auto array1_data = new intObject[size1];
    auto array2_data = new intObject[size2];
    auto array_key = new EKeyBySalary[size1 + size2];
    auto array_data = new intObject[size1 + size2];

    int cnt1 = 0;
    int cnt2 = 0;
    int cnt3 = 0;
    int cnt4 = 0;
    int cnt5 = 0;

    tree1->TreeKey_to_array(tree1->getRoot(),array1_key,&cnt1);
    tree2->TreeKey_to_array(tree2->getRoot(), array2_key, &cnt2);
    tree1->TreeData_to_array(tree1->getRoot(), array1_data, &cnt3);
    tree2->TreeData_to_array(tree2->getRoot(), array2_data, &cnt4);

    mergeArrays(array1_key, array2_key, array_key, size1, size2, array1_data, array2_data, array_data);

    tree1->treeClear();
    tree1->arrayToTree(array_key, array_data, 0, size1 + size2 - 1, &cnt5);
    //tree2->treeClear();
    //delete tree2;
    //tree2 = nullptr;
    hightUpdate(tree1->getRoot());
    numOfSonsUpdate(tree1->getRoot());
    gradeSum_update(tree1->getRoot());

    delete[]array1_key;
    array1_key = nullptr;

    delete[]array2_key;
    array2_key = nullptr;

    delete[]array1_data;
    array1_data = nullptr;

    delete[]array2_data;
    array2_data = nullptr;

    delete[]array_key;
    array_key = nullptr;

    delete[]array_data;
    array_data = nullptr;

    return tree1;

}

 void updateCompany(GNode<EKeyBySalary,intObject>* root,int new_id,HashTable<EmployeeData>* my_hash)
{
    if (root == nullptr)
        return;

    updateCompany(root->left_son,new_id,my_hash);
    my_hash->find(root->key->employeeId)->company_id = new_id;
    updateCompany(root->right_son,new_id,my_hash);
}

void updateCompanyForHash(HashTable<EmployeeData>* old_hash, int new_id,HashTable<EmployeeData>* my_hash)
{
        for (int i = 0; i < old_hash->size; ++i)
        {
            if(old_hash->arr[i] != nullptr)
            {
                ListNode<EmployeeData,int>* tmp = old_hash->arr[i]->getFirst();
                while (tmp != nullptr)
                {
                    my_hash->find(*tmp->key)->company_id = new_id;
                    tmp = tmp->next;
                }
            }

        }

}

StatusType EmployeeManager::AcquireCompany(int companyID1, int companyID2, double factor) {

    if (companyID1 <= 0 || companyID1 > num_of_compaines || companyID2 <= 0 || companyID2 > num_of_compaines
                                                                    || companyID2 ==companyID1 || factor <=0)
    {
        return INVALID_INPUT;
    }

    int group_id1 = this->companies->Find(companyID1)->groupId;
    int group_id2 = this->companies->Find(companyID2)->groupId;
    int size_group1 = arr[group_id1]->employees_tree_arr->getSize();
    int size_group2 = arr[group_id2]->employees_tree_arr->getSize();
    double val = this->companies->Find(group_id2)->temp_value * factor ;

    if (group_id2 == group_id1)
    {
        return INVALID_INPUT;
    }


    auto DataT = new intObject[size_group2];
    auto keyT = new EKeyBySalary[size_group2];
    int indexA = 0;
    int indexB = 0;

    auto all_key = new EKeyBySalary[size_group1 + size_group2];
    auto all_data = new intObject[size_group1 + size_group2];
    if (size_group1 == 0 && size_group2 == 0)
    {
        updateCompanyForHash(arr[group_id2]->employees_hash_arr,group_id1, this->employees_hash );
        this->arr[group_id1]->employees_hash_arr->mergeHash(arr[group_id2]->employees_hash_arr);
        this->arr[group_id1]->sum_grades_arr += this->arr[group_id2]->sum_grades_arr;
        this->arr[group_id1]->employees_with_zero_Salary_arr += this->arr[group_id2]->employees_with_zero_Salary_arr;

        delete this->arr[group_id2]->employees_tree_arr;
        this->arr[group_id2]->employees_tree_arr = nullptr;
        delete arr[group_id2]->employees_hash_arr;
        arr[group_id2]->employees_hash_arr = nullptr;
        delete this->arr[group_id2];
        this->arr[group_id2] = nullptr;

        companies->Union(group_id1,group_id2,val);
        delete[] DataT;
        delete[] keyT;
        delete[] all_data;
        delete[] all_key;
        return SUCCESS;

    } else if (size_group1 == 0 && size_group2 != 0)
    {
        updateCompany(this->arr[group_id2]->employees_tree_arr->getRoot(),group_id1, this->employees_hash);
        this->arr[group_id2]->employees_tree_arr->TreeKey_to_array(this->arr[group_id2]->employees_tree_arr->getRoot(),keyT,&indexA);
        this->arr[group_id2]->employees_tree_arr->TreeData_to_array(this->arr[group_id2]->employees_tree_arr->getRoot(),DataT,&indexB);
        indexA =0;
        this->arr[group_id1]->employees_tree_arr->treeClear();
        this->arr[group_id1]->employees_tree_arr->arrayToTree(keyT,DataT,0,size_group2 -1,&indexA);


    } else if (size_group1 != 0 && size_group2 == 0)
    {

        updateCompanyForHash(arr[group_id2]->employees_hash_arr,group_id1, this->employees_hash );
        this->arr[group_id1]->employees_hash_arr->mergeHash(arr[group_id2]->employees_hash_arr);
        this->arr[group_id1]->sum_grades_arr += this->arr[group_id2]->sum_grades_arr;
        this->arr[group_id1]->employees_with_zero_Salary_arr += this->arr[group_id2]->employees_with_zero_Salary_arr;

        delete this->arr[group_id2]->employees_tree_arr;
        this->arr[group_id2]->employees_tree_arr = nullptr;
        delete arr[group_id2]->employees_hash_arr;
        arr[group_id2]->employees_hash_arr = nullptr;
        delete this->arr[group_id2];
        this->arr[group_id2] = nullptr;

        companies->Union(group_id1,group_id2,val);
        delete[] DataT;
        delete[] keyT;
        delete[] all_data;
        delete[] all_key;
        return SUCCESS;
    } else
    {
        updateCompany(this->arr[group_id2]->employees_tree_arr->getRoot(),group_id1, this->employees_hash);
        auto DataA = new intObject[size_group1];
        auto keyA = new EKeyBySalary[size_group1];
        indexA = 0;
        indexB =0;
        this->arr[group_id1]->employees_tree_arr->TreeKey_to_array(this->arr[group_id1]->employees_tree_arr->getRoot(),keyA,&indexA);
        this->arr[group_id1]->employees_tree_arr->TreeData_to_array(this->arr[group_id1]->employees_tree_arr->getRoot(),DataA,&indexB);
        indexA = 0;
        indexB =0;
        this->arr[group_id2]->employees_tree_arr->TreeKey_to_array(this->arr[group_id2]->employees_tree_arr->getRoot(),keyT,&indexA);
        this->arr[group_id2]->employees_tree_arr->TreeData_to_array(this->arr[group_id2]->employees_tree_arr->getRoot(),DataT,&indexB);
        indexA = 0;
        this->arr[group_id1]->employees_tree_arr->treeClear();
        mergeArrays(keyT,keyA,all_key,size_group2 ,size_group1 ,DataT,DataA,all_data);
        this->arr[group_id1]->employees_tree_arr->arrayToTree(all_key,all_data,0,size_group1 + size_group2 -1,&indexA);

        delete[] DataA;
        delete[] keyA;
    }

    updateCompanyForHash(arr[group_id2]->employees_hash_arr,group_id1, this->employees_hash );
    this->arr[group_id1]->employees_hash_arr->mergeHash(arr[group_id2]->employees_hash_arr);
    this->arr[group_id1]->sum_grades_arr += this->arr[group_id2]->sum_grades_arr;
    this->arr[group_id1]->employees_with_zero_Salary_arr += this->arr[group_id2]->employees_with_zero_Salary_arr;

    hightUpdate(this->arr[group_id1]->employees_tree_arr->getRoot());
    numOfSonsUpdate(this->arr[group_id1]->employees_tree_arr->getRoot());
    gradeSum_update(this->arr[group_id1]->employees_tree_arr->getRoot());
    delete this->arr[group_id2]->employees_tree_arr;
    this->arr[group_id2]->employees_tree_arr = nullptr;
    delete arr[group_id2]->employees_hash_arr;
    arr[group_id2]->employees_hash_arr = nullptr;
    delete this->arr[group_id2];
     this->arr[group_id2] = nullptr;

    companies->Union(group_id1,group_id2,val);
    delete[] DataT;
    delete[] keyT;
    delete[] all_data;
    delete[] all_key;
    return SUCCESS;

}

void invertedInOrderSearch(int *grade, GNode<EKeyBySalary,intObject> *node, int *m )
{
    if (node == nullptr)
        return;

    invertedInOrderSearch(grade,node->right_son, m);

    if( (*m) > 0 )
    {
        (*grade) = (*grade) + node->data->num;
        (*m)--;
    }

    invertedInOrderSearch(grade, node->left_son, m);
}

StatusType EmployeeManager::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m) {

    if ( companyID > this->num_of_compaines || companyID < 0 || m <= 0)
        return INVALID_INPUT;

    RankTree<EKeyBySalary, intObject>* temp_tree;
    if (companyID == 0)
    {
        temp_tree = this->employees_tree;
    } else
    {
        temp_tree = this->arr[companies->Find(companyID)->groupId]->employees_tree_arr;
    }

    if (temp_tree->getSize() < m )
        return FAILURE;


    int sum =0;
    int i =m;
    invertedInOrderSearch(&sum,temp_tree->getRoot(),&i);
    printf("SumOfBumpGradeBetweenTopWorkersByGroup: %d\n",sum);
    return SUCCESS;

}
GNode<EKeyBySalary,intObject>* PrevDad(GNode<EKeyBySalary,intObject>* root, EKeyBySalary minEmployeeID,EKeyBySalary maxEmployeeId)
{
    GNode<EKeyBySalary,intObject>* itr = root;
    if (itr == nullptr)
    {
        return nullptr;
    }
    while (itr != nullptr )
    {
        if (maxEmployeeId > *itr->key && minEmployeeID > *itr->key)
        {
            itr = itr->right_son;
        }else if (maxEmployeeId < *itr->key && minEmployeeID < *itr->key)
        {
            itr = itr->left_son;
        } else break;
    }
    return itr;
}

int update_min_from_prv(GNode<EKeyBySalary,intObject>* prev , EKeyBySalary key)
{
    GNode<EKeyBySalary,intObject>* itr = prev;
    int num =0;

    while (itr != nullptr && *itr->key != key)
    {
        if (*itr->key > key)
        {
            itr = itr->left_son;

        } else
        {
            num += itr->get_gradeSum(itr->left_son).num;
            num += itr->data->num;
            itr = itr->right_son;
        }
    }
    return num;
}

int update_max_from_prv(GNode<EKeyBySalary,intObject>* prev , EKeyBySalary key)
{
    GNode<EKeyBySalary,intObject>* itr = prev;
    int num =0;

    while (itr != nullptr && *itr->key != key)
    {
        if (*itr->key > key)
     {
         num += itr->get_gradeSum(itr->right_son).num;
         num +=itr->data->num;
        itr = itr->left_son;
     } else
    {
        itr = itr->right_son;
    }
}
return num;
}
StatusType EmployeeManager::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary) {
    if (  higherSalary < 0 || lowerSalary < 0 ||
        lowerSalary > higherSalary || companyID < 0 || companyID > this->num_of_compaines)
        return INVALID_INPUT;

    double range = 0, num = 0;
    RankTree<EKeyBySalary, intObject>* temp_tree;

    if (companyID == 0) {
        if (lowerSalary == 0) {
            range += this->employees_with_zero_Salary;
            num += this->sumGrade;
        }

        temp_tree = this->employees_tree;

    } else {
        int group_id = this->companies->Find(companyID)->groupId;
        if (lowerSalary == 0) {
            range += this->arr[group_id]->employees_with_zero_Salary_arr;
            num += this->arr[group_id]->sum_grades_arr;
        }
        temp_tree = this->arr[group_id]->employees_tree_arr;
    }


    //inserting temp nodes
    EKeyBySalary lower_key(-1, lowerSalary);
    EKeyBySalary higher_key(-2, higherSalary);
    intObject temp_data(0);
    temp_tree->insert(lower_key, temp_data);
    temp_tree->insert(higher_key, temp_data);
    int higher_rank = temp_tree->rank(higher_key);
    int lower_rank = temp_tree->rank(lower_key);
    if (higher_rank - lower_rank - 1 == 0 && range == 0) {
        temp_tree->remove(lower_key);
        temp_tree->remove(higher_key);
        return FAILURE;
    }
    //gradeSum_update(temp_tree->getRoot());
    range += (higher_rank - lower_rank - 1);

    num += PrevDad(temp_tree->getRoot(), lower_key, higher_key)->grade_sum.num;
    num -=update_min_from_prv(PrevDad(temp_tree->getRoot(), lower_key, higher_key),lower_key);
    num -=update_max_from_prv(PrevDad(temp_tree->getRoot(), lower_key, higher_key),higher_key);
    num -= temp_tree->find(lower_key)->get_gradeSum(temp_tree->find(lower_key)->left_son).num;
    num -= temp_tree->find(higher_key)->get_gradeSum(temp_tree->find(higher_key)->right_son).num;

    temp_tree->remove(lower_key);
    temp_tree->remove(higher_key);
    printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n",(double)(num / range)) ;
    return SUCCESS;
}

StatusType EmployeeManager::EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
{
    if(employeeID<=0 || salaryIncrease<=0)
    {
        return INVALID_INPUT;
    }
    if(this->employees_hash->find(employeeID) == nullptr )
    {
        return FAILURE;
    }
    int grade = this->employees_hash->find(employeeID)->grade;
    int salary = this->employees_hash->find(employeeID)->salary;
    int companyId =  this->employees_hash->find(employeeID)->company_id;
    this->employees_hash->find(employeeID)->salary += salaryIncrease;
    this->arr[companyId]->employees_hash_arr->find(employeeID)->salary += salaryIncrease;
    if (salary == 0) {
        this->sumGrade -= grade;
        arr[companyId]->sum_grades_arr-=grade;
        this->employees_with_zero_Salary -= 1;
        arr[companyId]->employees_with_zero_Salary_arr -=1;
    }
    EKeyBySalary key(employeeID,salary);
    EKeyBySalary new_key(employeeID,salary+salaryIncrease);
    intObject data(grade);
    try {
        if(arr[companyId]->employees_tree_arr->find(key) != nullptr && this->employees_tree->find(key) != nullptr )
        {
            arr[companyId]->employees_tree_arr->remove(key);
            arr[companyId]->employees_tree_arr->insert(new_key,data);
            this->employees_tree->remove(key);
            this->employees_tree->insert(new_key,data);
        } else
        {
            this->employees_tree->insert(new_key,data);
            arr[companyId]->employees_tree_arr->insert(new_key,data);
        }

    }catch (AllocatonError &e)
    {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}


StatusType EmployeeManager::PromoteEmployee(int employeeID, int bumpGrade)
{
    if(employeeID<=0)
    {
        return INVALID_INPUT;
    }
    if(this->employees_hash->find(employeeID) == nullptr )
    {
        return FAILURE;
    }
    if (bumpGrade <= 0)
    {
        return SUCCESS;
    }

    int grade = this->employees_hash->find(employeeID)->grade;
    int salary = this->employees_hash->find(employeeID)->salary;
    int companyId =  this->employees_hash->find(employeeID)->company_id;
    this->employees_hash->find(employeeID)->grade += bumpGrade;
    arr[companyId]->employees_hash_arr->find(employeeID)->grade += bumpGrade;
    if (salary == 0) {
        this->sumGrade += bumpGrade;
        arr[companyId]->sum_grades_arr +=bumpGrade;
    } else
    {
        EKeyBySalary key(employeeID,salary);
        EKeyBySalary new_key(employeeID,salary);
        intObject data(grade + bumpGrade);

        arr[companyId]->employees_tree_arr->remove(key);
        arr[companyId]->employees_tree_arr->insert(new_key,data);
        this->employees_tree->remove(key);
        this->employees_tree->insert(new_key,data);
    }

    return SUCCESS;
}

StatusType EmployeeManager::CompanyValue( int companyID)
{
    if (  companyID <= 0 || companyID > this->num_of_compaines)
        return INVALID_INPUT;
    double val =this->companies->Find(companyID)->temp_value;
    printf("CompanyValue: %.1f\n",val );
    return SUCCESS;
}

StatusType  EmployeeManager::BumpGradeToEmployees( int lowerSalary, int higherSalary, int bumpGrade) {
    if (bumpGrade <= 0)
        return SUCCESS;

    auto key_arr = new EKeyBySalary[this->employees_tree->getSize()];
    auto data_arr = new intObject[this->employees_tree->getSize()];
    int temp = 0;
    this->employees_tree->TreeKey_to_array(this->employees_tree->getRoot(), key_arr, &temp);
    temp = 0;
    this->employees_tree->TreeData_to_array(this->employees_tree->getRoot(), data_arr, &temp);

    for (int i = 0; i < this->employees_tree->getSize(); ++i) {
        if (key_arr[i].salary >= lowerSalary && key_arr[i].salary <= higherSalary) {
            intObject new_data(data_arr[i].num + bumpGrade);
            this->employees_tree->remove(key_arr[i]);
            this->employees_tree->insert(key_arr[i], new_data);
        }
    }
    if (lowerSalary < 0) {
        for (int t = 0; t < this->employees_hash->size; ++t) {
            if (this->employees_hash->arr[t] != nullptr) {
                ListNode<EmployeeData, int> *tmp_node = this->employees_hash->arr[t]->getFirst();
                while (tmp_node != nullptr) {
                    this->employees_hash->find(*tmp_node->key)->grade += bumpGrade;
                    this->sumGrade += bumpGrade;
                    tmp_node = tmp_node->next;
                }
            }

        }

        for (int i = 1; i <= num_of_compaines; ++i) {
            if (arr[i] != nullptr) {
                auto key_arr1 = new EKeyBySalary[this->arr[i]->employees_tree_arr->getSize()];
                auto data_arr1 = new intObject[this->arr[i]->employees_tree_arr->getSize()];
                int temp1 = 0;
                this->arr[i]->employees_tree_arr->TreeKey_to_array(this->arr[i]->employees_tree_arr->getRoot(), key_arr1, &temp1);
                temp1 = 0;
                this->arr[i]->employees_tree_arr->TreeData_to_array(this->arr[i]->employees_tree_arr->getRoot(), data_arr1, &temp1);

                for (int j = 0; j < this->arr[i]->employees_tree_arr->getSize(); ++j) {
                    if (key_arr[j].salary >= lowerSalary && key_arr[j].salary <= higherSalary) {
                        intObject new_data1(data_arr1[j].num + bumpGrade);
                        this->arr[j]->employees_tree_arr->remove(key_arr1[j]);
                        this->arr[j]->employees_tree_arr->insert(key_arr1[j], new_data1);
                    }
                }
                if (lowerSalary < 0) {
                    for (int k = 0; k < this->arr[i]->employees_hash_arr->size; ++k) {
                        if (this->arr[i]->employees_hash_arr->arr[k] != nullptr) {
                            ListNode<EmployeeData, int> *tmp_node1 = this->arr[i]->employees_hash_arr->arr[k]->getFirst();
                            while (tmp_node1 != nullptr) {
                                this->arr[i]->employees_hash_arr->find(*tmp_node1->key)->grade += bumpGrade;
                                this->arr[i]->sum_grades_arr += bumpGrade;
                                tmp_node1 = tmp_node1->next;
                            }
                        }

                    }
                }

            }
        }


    }
    return SUCCESS;
}