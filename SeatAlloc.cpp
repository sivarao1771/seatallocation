#include <stdio.h>
#include <iostream>
#include <algorithm>  
#include <cstdlib>  
#include <string>
#include <map>
#include <vector>

using namespace std;

// Structure to store student information
struct student
{
    int rank;
    string name;
    string category;
    vector<pair<int, string>> priorities;
    string colbranch;
    string selectedcategory;
};

// Structure to store college branch information
struct college_branch
{
    string col_bra;
    int num_seats_gen;
    int num_seats_ews;
    int num_seats_obc;
    int num_seats_sc;
    int num_seats_st;
    int num_seats_girl;
    int seats_filled;
    student* first;
};

// Function to display details of all students
void traverseStudents(student* store, int numStudents) 
{
    for (int i = 0; i < numStudents; ++i) 
    {
        cout << "Student Name: " << store[i].name << endl;
        cout << "Student Rank: " << store[i].rank << endl;
        cout << "Student Category: " << store[i].category << endl;
        cout << "Priorities:" << endl;
        for (const auto& priority : store[i].priorities) 
        {
            cout << "  Priority " << priority.first << ": " << priority.second << endl;
        }
        cout << endl << endl;
    }
}

// Function to allocate admission to students based on priorities
void give_admission(student* store, int numStudents, college_branch* josaa, map<string, int> collegeBranchToNumber) 
{
    for (int i = 0; i < numStudents; ++i) 
    {
        for (const auto& priority : store[i].priorities) 
        {
            int collegeNumber = collegeBranchToNumber[priority.second];
            // Allocate seat based on category and availability
            if(josaa[collegeNumber].num_seats_gen > 0)
            {
                store[i].colbranch = priority.second;
                store[i].selectedcategory = "General";
                josaa[collegeNumber].num_seats_gen--;   
                if(josaa[collegeNumber].seats_filled == 0)
                {
                    josaa[collegeNumber].first = &store[i];
                }                 
                josaa[collegeNumber].seats_filled++;
                break;
            }
            else if(josaa[collegeNumber].num_seats_ews > 0 && store[i].category == "ews")
            {
                store[i].colbranch = priority.second;
                store[i].selectedcategory = "EWS";
                josaa[collegeNumber].num_seats_ews--;
                josaa[collegeNumber].seats_filled++;
                break;
            }
            else if(josaa[collegeNumber].num_seats_obc > 0 && store[i].category == "obc")
            {
                store[i].colbranch = priority.second;
                store[i].selectedcategory = "OBC";
                josaa[collegeNumber].num_seats_obc--;
                josaa[collegeNumber].seats_filled++;
                break;
            }
            else if(josaa[collegeNumber].num_seats_sc > 0 && store[i].category == "sc")
            {
                store[i].colbranch = priority.second;
                store[i].selectedcategory = "SC";
                josaa[collegeNumber].num_seats_sc--;
                josaa[collegeNumber].seats_filled++;
                break;
            }
            else if(josaa[collegeNumber].num_seats_st > 0 && store[i].category == "st")
            {
                store[i].colbranch = priority.second;
                store[i].selectedcategory = "ST";
                josaa[collegeNumber].num_seats_st--;
                josaa[collegeNumber].seats_filled++;
                break;
            }
            else if(josaa[collegeNumber].num_seats_girl > 0 && store[i].category == "girl")
            {
                store[i].colbranch = priority.second;
                store[i].selectedcategory = "Girl";
                josaa[collegeNumber].num_seats_girl--;
                josaa[collegeNumber].seats_filled++;
                break;
            }
        }
        // Display admission details for each student
        cout << "  Admission of " << store[i].name << " is in " << store[i].colbranch << " under " << store[i].selectedcategory << " category" << endl;
    }
}

// Function to compare students based on rank
bool compareStudents(const student& a, const student& b) 
{
    return a.rank < b.rank;
}

// Function to display priority list for a student based on rank
void priority_list_through_rank(student* store, int n, int total)
{
    if (n > 0 && n <= total) 
    {
        cout << "The priorities of " << store[n-1].name << " are ->" << endl;
        if (!store[n-1].priorities.empty()) 
        {
            for (const auto& priority : store[n-1].priorities) 
            {
                cout << "Priority " << priority.first << " : " << priority.second << endl;
            }
        } 
        else 
        {
            cout << "No priorities available for this student." << endl;
        }
        cout << endl;
    } 
    else 
    {
        cout << "Invalid index. Please provide a valid index in the range 1 to " << total << endl;
    }
}

// Function to display priority list for a student based on name
void priority_list_through_name(student* store, string name1)
{
    int i;
    for(i = 0; i < 500; i++) 
    {
        if (store[i].name == name1) 
        {
            break;
        }
    }
    if(i == 500)
    {
        cout << "There is no student with that name" << endl;
        return ;
    }

    cout << "Priorities for student " << store[i].name << ":" << endl;
    for (const auto& priority : store[i].priorities) {
        cout << "Priority " << priority.first << ": " << priority.second << endl;
    }
    cout << endl;
}

// Function to display classmates in a specific college and branch
void know_your_classmates_by_colbra(student* store, string collbran, int total)
{
    for(int i=0;i<total;i++)
    {
        if(store[i].colbranch == collbran)
        {
            cout << store[i].name << " | ";
        }
    }
    cout << endl;
}

// Function to display college, branch and category based on student name
void know_your_colBraCat_by_name(student* store, string name, int total)
{
    for(int i=0;i<total;i++)
    {
        if(store[i].name == name)
        {
            cout << "College and branch of " << name << " is " << store[i].colbranch << " under " << store[i].selectedcategory << " category" << endl;
            break;
        }
    }
}

// Function to display college, branch and category based on student rank
void know_your_colBraCat_by_rank(student* store, int rank, int total)
{
    for(int i=0;i<total;i++)
    {
        if(store[i].rank == rank)
        {
            cout << "College and branch of " << store[i].name << " is " << store[i].colbranch << " under " << store[i].selectedcategory << " category" << endl;
            break;
        }
    }
}

// Function to display the number of classmates in a specific college and branch
void number_of_classmates(college_branch* josaa, string col_bra)
{
    for(int i=0;i<51;i++)
    {
        if(josaa[i].col_bra == col_bra)
        {
            cout << "There are " << josaa[i].seats_filled << " students in " << col_bra << endl; 
            break;
        }
    }
}

// Function to display opener for a branch in a college
void branch_opener(college_branch* josaa, string colbra, map<string, int> collegeBranchToNumber)
{
    int collegeNumber = collegeBranchToNumber[colbra];
    if(josaa[collegeNumber].seats_filled == 0)
    {
        cout << "There is no one in this branch yet" << endl;
        return;
    }
    cout << "Branch opener of " << colbra << " is " << josaa[collegeNumber].first->name << " with AIR rank " << josaa[collegeNumber].first->rank << endl;
}

// Function to display seats distribution in a branch of a college
void seat_left(college_branch* josaa, string colbra, map<string, int> collegeBranchToNumber)
{
    int collegeNumber = collegeBranchToNumber[colbra];
    cout << "Seats left in " << josaa[collegeNumber].col_bra << " :" << endl;
    cout << "   General - " << josaa[collegeNumber].num_seats_gen << endl;
    cout << "   EWS - " << josaa[collegeNumber].num_seats_ews << endl;
    cout << "   OBC - " << josaa[collegeNumber].num_seats_obc << endl;
    cout << "   SC - " << josaa[collegeNumber].num_seats_sc << endl;
    cout << "   ST - " << josaa[collegeNumber].num_seats_st << endl;
    cout << "   Girl - " << josaa[collegeNumber].num_seats_girl << endl;
}

int main()
{
    college_branch* josaa = new college_branch[51];     // Array to store college branch information
    map<string, int> collegeBranchToNumber;             // Map to store college branch name to array index mapping

    // Initializing college branch information
    josaa[0] = {"IITBom-CSE",3,2,2,1,1,2,0};   collegeBranchToNumber["IITBom-CSE"] = 0;
    josaa[1] = {"IITBom-EEE",4,1,2,1,1,1,0};   collegeBranchToNumber["IITBom-EEE"] = 1;
    josaa[2] = {"IITBom-EP",5,2,1,0,1,1,0};    collegeBranchToNumber["IITBom-EP"] = 2;
    josaa[3] = {"IITBom-MECH",5,2,1,0,1,1,0};  collegeBranchToNumber["IITBom-MECH"] = 3;
    josaa[4] = {"IITBom-AERO",4,2,2,0,1,1,0};  collegeBranchToNumber["IITBom-AERO"] = 4;
    josaa[5] = {"IITBom-CHEM",3,1,2,1,2,2,0};  collegeBranchToNumber["IITBom-CHEM"] = 5;
    josaa[6] = {"IITDel-CSE",4,2,2,1,1,2,0};   collegeBranchToNumber["IITDel-CSE"] = 6;
    josaa[7] = {"IITDel-MNC",4,1,2,1,1,1,0};   collegeBranchToNumber["IITDel-MNC"] = 7;
    josaa[8] = {"IITDel-CSE5",5,2,1,0,1,1,0};  collegeBranchToNumber["IITDel-CSE5"] = 8;
    josaa[9] = {"IITDel-MNC5",5,1,1,0,1,1,0};  collegeBranchToNumber["IITDel-MNC5"] = 9;
    josaa[10] = {"IITDel-EEE",4,2,2,0,1,1,0};  collegeBranchToNumber["IITDel-EEE"] = 10;
    josaa[11] = {"IITDel-CHEM",3,1,2,1,2,2,0}; collegeBranchToNumber["IITDel-CHEM"] = 11;   
    josaa[12] = {"IITMad-CSE",4,2,2,1,1,2,0};  collegeBranchToNumber["IITMad-CSE"] = 12;
    josaa[13] = {"IITMad-EEE",4,1,2,1,1,1,0};  collegeBranchToNumber["IITMad-EEE"] = 13;
    josaa[14] = {"IITMad-MECH",5,2,1,0,1,1,0}; collegeBranchToNumber["IITMad-MECH"] = 14;
    josaa[15] = {"IITMad-EP",5,1,1,0,1,1,0};   collegeBranchToNumber["IITMad-EP"] = 15;
    josaa[16] = {"IITMad-CIV",4,2,2,0,1,1,0};  collegeBranchToNumber["IITMad-CIV"] = 16;
    josaa[17] = {"IITMad-CHEM",3,1,2,1,2,2,0}; collegeBranchToNumber["IITMad-CHEM"] = 17;
    josaa[18] = {"IITKan-CSE",4,2,2,1,1,2,0};  collegeBranchToNumber["IITKan-CSE"] = 18;
    josaa[19] = {"IITKan-MNC",4,1,2,1,1,1,0};  collegeBranchToNumber["IITKan-MNC"] = 19;
    josaa[20] = {"IITKan-EEE",5,2,1,0,1,1,0};  collegeBranchToNumber["IITKan-EEE"] = 20;
    josaa[21] = {"IITKan-AERO",5,1,1,0,1,1,0}; collegeBranchToNumber["IITKan-AERO"] = 21;
    josaa[22] = {"IITKan-MECH",4,2,2,0,1,1,0}; collegeBranchToNumber["IITKan-MECH"] = 22;
    josaa[23] = {"IITKan-BSBE",3,1,2,1,2,2,0}; collegeBranchToNumber["IITKan-BSBE"] = 23;
    josaa[24] = {"IITKha-CSE",4,2,2,1,1,2,0};  collegeBranchToNumber["IITKha-CSE"] = 24;
    josaa[25] = {"IITKha-CSE5",4,1,2,1,1,1,0}; collegeBranchToNumber["IITKha-CSE5"] = 25;
    josaa[26] = {"IITKha-EECE",5,2,1,0,1,1,0}; collegeBranchToNumber["IITKha-EECE"] = 26;
    josaa[27] = {"IITKha-EEE",5,1,1,0,1,1,0};  collegeBranchToNumber["IITKha-EEE"] = 27;
    josaa[28] = {"IITKha-CIV",4,2,2,0,1,1,0};  collegeBranchToNumber["IITKha-CIV"] = 28;
    josaa[29] = {"IITKha-MET",2,1,2,1,2,2,0};  collegeBranchToNumber["IITKha-MET"] = 29;
    josaa[30] = {"IITRoo-CSE",4,2,2,1,1,2,0};  collegeBranchToNumber["IITRoo-CSE"] = 30;
    josaa[31] = {"IITRoo-DSAI",4,1,2,1,1,1,0}; collegeBranchToNumber["IITRoo-DSAI"] = 31;
    josaa[32] = {"IITRoo-EEE",5,2,1,0,1,1,0};  collegeBranchToNumber["IITRoo-EEE"] = 32;
    josaa[33] = {"IITRoo-EP",5,1,1,0,1,1,0};   collegeBranchToNumber["IITRoo-EP"] = 33;
    josaa[34] = {"IITRoo-BSBE",4,2,2,0,1,1,0}; collegeBranchToNumber["IITRoo-BSBE"] = 34;
    josaa[35] = {"IITRoo-ECE",3,1,2,1,2,2,0};  collegeBranchToNumber["IITRoo-ECE"] = 35;
    josaa[36] = {"IITGuw-CSE",4,2,2,1,1,2,0};  collegeBranchToNumber["IITGuw-CSE"] = 36;
    josaa[37] = {"IITGuw-MNC",4,1,2,1,1,1,0};  collegeBranchToNumber["IITGuw-MNC"] = 37;
    josaa[38] = {"IITGuw-DSAI",5,2,1,0,1,1,0}; collegeBranchToNumber["IITGuw-DSAI"] = 38;
    josaa[39] = {"IITGuw-ECE",5,1,1,0,1,1,0};  collegeBranchToNumber["IITGuw-ECE"] = 39;
    josaa[40] = {"IITGuw-EEE",4,2,2,0,1,1,0};  collegeBranchToNumber["IITGuw-EEE"] = 40;
    josaa[41] = {"IITGuw-MECH",3,1,2,1,2,2,0}; collegeBranchToNumber["IITGuw-MECH"] = 41;
    josaa[42] = {"IITGuw-CHEM",5,2,1,2,2,1,0}; collegeBranchToNumber["IITGuw-CHEM"] = 42;
    josaa[43] = {"IITGuw-EE",4,1,1,1,2,1,0};   collegeBranchToNumber["IITGuw-EE"] = 43;
    josaa[44] = {"IITHyd-CSE",4,2,2,1,1,2,0};  collegeBranchToNumber["IITHyd-CSE"] = 44;
    josaa[45] = {"IITHyd-AI",4,1,2,1,1,1,0};   collegeBranchToNumber["IITHyd-AI"] = 45;
    josaa[46] = {"IITHyd-MNC",5,2,1,0,1,1,0};  collegeBranchToNumber["IITHyd-MNC"] = 46;
    josaa[47] = {"IITHyd-EEE",5,1,1,0,1,1,0};  collegeBranchToNumber["IITHyd-EEE"] = 47;
    josaa[48] = {"IITHyd-CIV",4,2,2,0,1,1,0};  collegeBranchToNumber["IITHyd-CIV"] = 48;
    josaa[49] = {"IITHyd-CE",3,1,2,1,2,2,0};   collegeBranchToNumber["IITHyd-CE"] = 49;
    josaa[50] = {"IITHyd-BTBI",3,1,2,1,1,1,0}; collegeBranchToNumber["IITHyd-BTBI"] = 50;

    cout << "Enter total number of students - ";
    int total;
    cin >> total;
    student* store = new student[total];      // Array to store student information

    int i,j;

    // Taking inputs from students
    int continuee = 1;
    do
    {
        cout << "ENTER YOUR RANK,NAME & CATEGORY" << endl;
        int rank;
        string name,category;
        cin >> store[i].rank >> store[i].name >> store[i].category;
        
        cout << "START ENTERING PRIORITIES" << endl;
        char next = 'Y';
        do
        {
            int priority_num;
            string collegeAndbranch;
            cin >> priority_num >> collegeAndbranch;
            store[i].priorities.push_back(make_pair(priority_num,collegeAndbranch));
            cout << "Press 'Y' to enter the next priority, or 'N' to stop: ";
            cin >> next;
        } while (next=='Y' || next == 'y');
        cout << "\nType 1 to enter details of next person, or 0 to end " << endl;
        i++;
        cin >> continuee;
    } while(continuee==1);

    //For demonstration purposes, using predefined student data
    // store[0] = {1,"aa","sc",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[1] = {2,"bb","gen",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[2] = {3,"cc","gen",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[3] = {4,"dd","obc",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[4] = {5,"ee","gen",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[5] = {6,"ff","gen",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[6] = {7,"gg","gen",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[7] = {8,"hh","gen",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[8] = {9,"ii","girl",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[9] = {10,"jj","girl",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[10] = {11,"kk","girl",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};
    // store[11] = {12,"ll","girl",{{1,"IITBom-CSE"},{2,"IITDel-CSE"}},"1"};

    sort(store, store + total, compareStudents);        // Sorting students based on rank

    give_admission(store,total,josaa,collegeBranchToNumber);
    traverseStudents(store,total);
    // priority_list_through_rank(store,5,total);
    // know_your_classmates_by_colbra(store,"IITBom-CSE",total);
    // know_your_colBraCat_by_name(store,"ff",total);
    // know_your_colBraCat_by_rank(store,6,total);
    // number_of_classmates(josaa,"IITBom-CSE");
    // branch_opener(josaa,"IITDel-CSE",collegeBranchToNumber);

    delete[] josaa;
    delete[] store;
}