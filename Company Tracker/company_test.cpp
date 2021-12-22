#include "company.hpp"
#include <iostream>

int main() {
    CompanyTracker* comp = new CompanyTracker(6);
    comp->split(1);
    std::cout << comp->inSameCompany(1, 2) << std::endl;  // Check splitting single company
    comp->merge(1, 2);
    std::cout << comp->inSameCompany(1, 3) << std::endl;  // Check inSameCompany
    std::cout << comp->inSameCompany(1, 2) << std::endl;
    comp->merge(3, 4);
    comp->merge(1, 3);                                    // Merging 2  merged companies
    std::cout << comp->inSameCompany(2, 4) << std::endl;  // Checking 2 companies merged companies
    comp->split(2);                                       // Checking split
    std::cout << comp->inSameCompany(1, 2) << std::endl;
    comp->merge(2, 5);  // Checking Merging after a split & edge case
    std::cout << comp->inSameCompany(2, 3) << std::endl;
    comp->merge(1, 8);  // Checking out of bounds case
    std::cout << comp->inSameCompany(2, 4) << std::endl;
    comp->merge(1, 1);  // Check self merge
    std::cout << comp->inSameCompany(2, 4) << std::endl;
    comp->split(-1);  // Out of bounds case
    std::cout << comp->inSameCompany(2, 3) << std::endl;
    delete comp;
}