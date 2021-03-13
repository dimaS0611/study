#include "Employee.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "wait: creator.exe filename.bin\n";
        return -1;
    }

    std::string filename_in(argv[1]);
    std::string filename_out(argv[2]);

    std::cout << "create out filename: " << filename_out << std::endl;

    std::vector<Employee> emploees;
    {
        std::ifstream bin(filename_in, std::ios_base::binary);
        if (!bin.is_open())
        {
            std::cout << "Opening file FAILED\n";
        }

        while (!bin.eof())
        {
            Employee emp = {0};
            bin.read((char*)&emp, sizeof(emp));

            if (bin.gcount() < sizeof(emp))
                break;

            emploees.push_back(emp);
        }

        bin.close();
    }

    double price = std::atoi(argv[3]);

    auto EmployeeLessByName = [](const Employee& lhs, const Employee& rhs)->bool
    {
        return std::string(lhs.m_name) <= std::string(rhs.m_name);
    };

    std::sort(emploees.begin(), emploees.end(), EmployeeLessByName);

    std::ofstream txt(filename_out);

    txt << "ID\t| Name\t\t| Hours\t\t| Salary\t|\n";
    txt << "----------------------------------------------------------\n\n";


    std::cout << "\n-----------------------------------------------------------\n";
    std::cout << "ID\t| Name\t\t| Hours\t\t| Salary\t|\n";
    std::cout << "----------------------------------------------------------\n\n";

    for (auto emploee : emploees)
    {
        txt.precision(2);
        double salary = emploee.m_hours * price;

        txt << emploee.m_id << "\t  " << std::string(emploee.m_name) << "\t\t  " << emploee.m_hours << "\t\t  " << salary << "\n\n";\

        std::cout << emploee.m_id << "\t  " << std::string(emploee.m_name) << "\t\t  " << emploee.m_hours << "\t\t  " << salary << "\n\n";
    }

    std::cout << "\n-----------------------------------------------------------\n";

    txt.close();
}

