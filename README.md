# 🚀 Employee Manager (C++)

A high-performance employee and company management system built in C++ using custom data structures like Hash Tables, Rank Trees, and Union-Find (Disjoint Sets). The system supports dynamic company operations such as hiring, promotions, and mergers with efficiency and scalability in mind.

---

## 🧩 Features

✅ Object-oriented design  
✅ Union-Find data structure for company management  
✅ Efficient employee operations (hiring, promotions, etc.)  
✅ Custom-built data structures:  
🔹 `HashTable`  
🔹 `List`  
🔹 `RankTree`  
✅ Exception-safe with modular error handling

---

## 📁 Project Structure

| File | Description |
|------|-------------|
| `EmployeeManager.cpp / .h` | Core logic for managing employees |
| `CompanyUF.h / CompanyNodeUF.h` | Union-Find for company mergers |
| `HashTable.h`, `List.h`, `RankTree.h` | Custom data structures |
| `exceptions.h` | Custom exception classes |
| `Dry.pdf` | System design document |
| `submissions.txt` | Metadata for submissions |


---

## 💡 Example Usage

```cpp
#include "EmployeeManager.h"

int main() {
    EmployeeManager manager;

    // Add companies
    manager.addCompany(101);
    manager.addCompany(102);

    // Add employees
    manager.addEmployee(1, 101, 50000);
    manager.addEmployee(2, 102, 60000);

    // Promote employee
    manager.promoteEmployee(1, 5000);

    // Merge companies
    manager.mergeCompanies(101, 102);

    // Query total employees
    std::cout << "Total Employees: " << manager.getEmployeeCount() << std::endl;

    return 0;
}
```

🧪 This example adds two companies, hires employees, promotes one of them, merges the companies, and prints the total number of employees.

---

---

## 🛠️ Build Instructions

> **Requires:** C++17 or higher

```bash
g++ -std=c++17 -o employee_manager EmployeeManager.cpp library2.cpp
./employee_manager
```

## 👤 Author

-MohammadBesher

