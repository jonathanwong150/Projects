#include "company.hpp"

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n) {
    numCompanies = n;
    companies = new Company*[numCompanies];
    for (int i = 0; i < numCompanies; ++i)
        companies[i] = new Company();
}

// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker() {
    // Loops through the CompanyTrack
    for (int i = 0; i < numCompanies; i++) {
        Company* x = findBiggest(i);
        while (x != companies[i]) {  // If the company at i is part of a parent company, split the biggest company
            split(i);
            x = findBiggest(i);  // Update iterator
        }
    }
    for (int i = 0; i < numCompanies; i++) {  // Loop through companytrack and delete the individal companies
        delete companies[i];
    }
    delete[] companies;  // Delete companytracker
}

void CompanyTracker::merge(int i, int j) {
    if (i < 0 || j < 0 || i >= numCompanies || j >= numCompanies) {  // Check edge cases
        return;
    }
    if (inSameCompany(i, j) == true) {  // Check if companies are already merged
        return;
    }
    Company* merged = new Company(findBiggest(i), findBiggest(j));  // Make new company with i and j
    findBiggest(i)->parent = merged;                                // Point i and j at new company
    findBiggest(j)->parent = merged;
}

void CompanyTracker::split(int i) {
    if (i < 0 || i >= numCompanies) {  // Check edge cases
        return;
    }
    if (findBiggest(i) == companies[i]) {  // Check if same company
        return;
    }
    if (findBiggest(i)->merge1 == nullptr) {  // Check if it is a single company
        return;
    }
    Company* y = findBiggest(i);
    y->merge1->parent = nullptr;  // Disconnect merged companies from parent company
    y->merge2->parent = nullptr;
    delete y;
}

bool CompanyTracker::inSameCompany(int i, int j) {
    if (i < 0 || j < 0 || i >= numCompanies || j >= numCompanies) {  // Check edge cases
        return false;
    }
    if (findBiggest(i) == findBiggest(j) || companies[i] == companies[j]) {  // If companies point at same thing
        return true;
    }
    return false;
}
Company* CompanyTracker::findBiggest(int i) {
    if (i < 0 || i >= numCompanies) {  // Edge cases
        return nullptr;
    }
    Company* it = companies[i];
    while (it->parent != nullptr) {  // While company has parent companies, go to parent
        it = it->parent;
    }
    return it;  // Return pointer to biggest company
}
