#include "Employee.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "wait: creator.exe filename.bin\n";
        return -1;
    }

    std::string filename(argv[1]);
    std::cout << "create filename: " << filename << std::endl;

    std::vector<Employee> employees;

    int count = std::stoi(argv[2]);
    
    std::cout << "\n-----------------------------------------------------------\n";
    for (int i = 1; i <= count; ++i)
    {
        int id = 0;
        std::string name;
        double hours = 0.0;

        std::cout << "Enter ID: ";
        std::cin >> id;
       
        std::cout << "Enter name: ";
        std::cin >> name;
        
        std::cout << "Enter working hours: ";
        std::cin >> hours;

        employees.emplace_back(id, name, hours);
    }

    std::ofstream bin(filename, std::ios_base::binary);
    if (!bin.is_open())
    {
        std::cout << "Creating file FAILED\n";
        return -2;
    }

    for (const auto emploee : employees)
    {
        bin.write((const char*)(&emploee), sizeof(emploee));
    }

    bin.close();
}
