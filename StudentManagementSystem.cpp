// including all necessary libraries
#include <iostream>
#include <fstream>
#include <string>

//this will be mostly used for the testing purposes
using std::cin; using std::cout; using std::endl; using std::ios;

int main()
{
    //the main reason why we use the char without the pointer or not as a string is so that we can even it out when the length is not 100
    //makes our work look neat and it is just my style of doing it you can always choose a C++ string or a cosnt char pointer that
    //both write to the read only data segment
    char data[25];
    int n = 0, option = 0, count_n = 0;

    std::string empty = "00", proctor = "";

    //name of the file to store the db
    //this helps in the case where you had already written to the file before
    //open the file in read mode
    std::ifstream f("Database.txt");
    std::string line;

    //loop to count the total number of lines in the file
    for(int i{ 0 }; std::getline(f, line); ++i)
    {
        count_n++;
    }
    while(option != 6)
    {
        std::cout << "Here is a list of the available options" << std::endl;
        std::cout << "Option 1: Add a new student" << std::endl;
        std::cout << "Option 2: Student Login, Please insert your Credentials" << std::endl;
        std::cout << "Option 3: Faculty Login, Please insert your Credentials" << std::endl;
        std::cout << "Option 4: Proctor Login, Please insert your Credentials" << std::endl;
        std::cout << "Option 5: Here is the Admin View" << std::endl;
        std::cout << "Option 6: Exit" << std::endl;
        std::cout << "-----------" << std::endl;
        std::cout << "Please enter your desired option" << std::endl;
        std::cin >> option;
        if (option == 1) 
        {
            std::fstream readwritefile;
            readwritefile.open("Database.txt", std::ios::app | std::ios::in);
            char RegVerifier[25];
            std::cout << "Enter the number of new students" << std::endl;
            std::cin >> n;
            //reviewing the details in the Database.txt
            count_n += n;
            for (int i{ 0 }; i < n; i++) 
            {
                //writing the entire data of the new students to the database.txt line by line in append mode so that the data is just added
                //at the end of the existing data without overwriting any data on the file
                std::cout << "Enter the details of the: " << (i + 1) << " student" << std::endl;
                std::cout << "Enter your Registration Number" << std::endl;
                std::cout << "Registration Number format, for example, Electrical Engineering should \n have the following EEEIXXXX2015" << std::endl;
                std::cin >> data;

                //verifying that the regno does not already exist in the db
                while (readwritefile >> RegVerifier)
                {
                    if (strcmp(data, RegVerifier) == 0)
                    {
                        std::cout << "\nRegistration Number: " << data << "already exists, please check with the faculty" << std::endl;
                        break;
                    }
                    else if (strcmp(data, RegVerifier) != 0)
                    {
                        //writing on the file 
                        readwritefile << data << "\t";
                        std::cout << "Please enter your name" << std::endl;
                        std::cin >> data;
                        //evening out the names so that the work looks decent
                        int len = strlen(data);
                        while (len < 25)
                        {
                            data[len] = ' ';
                            len += 1;
                        }
                        readwritefile << data << "\t";
                        //inserting two empty fields that represent the subject scores
                        outfile << empty << "\t";
                        outfile << empty << "\t";

                        std::cout << "Enter your proctor's ID" << "\n";
                        std::cin >> proctor;
                        outfile << proctor << "\n";
                        //the below code is to give time before the entry of another batch of student is entered
                        for (int x = 0; x < 1000; x++);
                    }
                }
                
            }
            readwritefile.close();
        }

        else if (option == 2) 
        {
            char RegNo[25];
            std::cout << "Enter your Registration Number" << std::endl;
            cin >> RegNo;
            std::ifstream infile;
            //int check = 0;
            //open the file in read mode and use the strcmp to compare the strings in a lexicographical manner till it hits a nptr
            //or until they are not equal, when they are not equal the strcmp returns which value is greater the left or right
            infile.open("Database.txt", ios::in);
            while (infile >> data)
            {
                if (strcmp(data, RegNo) == 0) 
                {
                    std::cout << "\nRegistration Number: " << data << std::endl;
                    infile >> data;
                    std::cout << "Name: " << data << std::endl;
                    infile >> data;
                    std::cout << "GR001: " << data << std::endl;
                    infile >> data;
                    std::cout << "MA123: " << data << std::endl;
                    infile >> data;
                    std::cout << "Proctor Id: " << data << endl;
                    infile.close();
                }
                else if(strcmp(data, RegNo) != 0)
                {
                    std::cout << "You have not Registered, please use option 1 for this" << std::endl;
                    infile.close();
                }
            }
            //return 0;
        }
        //this next option is used to view a specific subject marks
        else if (option == 3) 
        {
            char subcode[7];
            std::cout << "Enter the subject code" << std::endl;
            std::cin >> subcode;
            std::string code1 = "GR001", code2 = "MA123", mark = "";
            std::ifstream infile;
            int check = 0;
            std::cout << "There are two available options: \nOption 1: Add data about marks\n" << std::endl;
            std::cout << "View the data" << std::endl;
            std::cout << "Please enter the option that you desire" << std::endl;
            std::cin >> option;
            if (option == 1) 
            {
                std::cout << "Warning! You will need to enter the details of all the students" << std::endl;
                for (int i{ 0 }; i < count_n; i++) 
                {
                    std::fstream file("Database.txt");
                    if (strcmp(subcode, code1.c_str()) == 0) 
                    {
                        file.seekp(26 + 37 * i, std::ios_base::beg);
                        std::cout << "Enter the marks of the Students" << (i + 1) << " : ";
                        std::cin >> mark;
                        //the c_str() returns a char* that contains a null terminated string
                        //it is useful when you want to pass the contents of an std::string to a function that expects to work with C_style strings
                        //std::size_t pos1 = string.find_first_of('w'); I just thought this would be very fun to have and use
                        file.write(mark.c_str(), 2);
                    }
                }
            }
            else if (option == 2) 
            {
                //this is a read only operation since we are only going to view
                infile.open("Database.txt", ios::in);
                if (strcmp(subcode, code1.c_str()) == 0) 
                {
                    std::cout << "Registration Number -Marks" << std::endl;
                    while (infile >> data) 
                    {
                        std::cout << data;
                        infile >> data;
                        infile >> data;
                        std::cout << " - " << data << std::endl;
                        infile >> data;
                        infile >> data;
                        check = 1;
                    }
                }
                infile.close();
                infile.open("Database.txt", ios::in);
                if (strcmp(subcode, code2.c_str()) == 0) 
                {
                    std::cout << "Registration Number - Marks" << std::endl;
                    while (infile >> data) 
                    {
                        std::cout << data;
                        infile >> data;
                        infile >> data;
                        infile >> data;
                        std::cout << " - " << data << std::endl;
                        infile >> data;
                        check = 1;
                    }
                }
            }
            infile.close();
            if (check == 0) 
            {
                std::cout << "No such subject code exists" << std::endl;
            }
            //return 0;
        }
        else if (option == 4)
        {
        char procid [7];
        std::cout << "Please enter the proctor id" << std::endl;
        std::cin >> procid;
        int check = 0;
        char temp1[100], temp2[100], temp3[100], temp4[100], id[100];
        //we are going to be doing a read and so we use the std::ifstream
        std::ifstream infile;
        infile.open("Database.txt", ios::in);
        while (infile >> temp1) 
        {
            infile >> temp2;
            infile >> temp3;
            infile >> temp4;
            infile >> id;
            if (strcmp(id, procid) == 0) 
            {
                std::cout << "Registration Number: " << temp1 << std::endl;
                std::cout << "Name: " << temp2 << std::endl;
                std::cout << "Name: " << temp2 << std::endl;
                std::cout << "GR001 Mark " << temp3 << std::endl;
                std::cout << "MA123 Mark " << temp4 << std::endl;
                check = 1;

            }
        }
        if (check == 0) 
        {
            std::cout << "No records of such a procid found " << std::endl;
        }
        //return 0;
        }
        else if (option = 5) 
            {
            char password [25];
            std::cout << "Please enter the Admin Password" << std::endl;
            std::cin >> password;
            std::string admin_password {"Adm$n1#j*7_"};
            if (strcmp(password, admin_password.c_str()) == 0) 
            {
                std::cout << "Registration Number\tName\nGR001 Mark\nMA123 Mark\nproctorId" << std::endl;
                std::ifstream infile;
                infile.open("Database.txt", ios::in);
                char data[20];
                while (infile >> data) 
                {
                    std::cout << data << "\t";
                    infile >> data;
                    std::cout << data << "\t";
                    infile >> data;
                    std::cout << data << "\t";
                    infile >> data;
                    std::cout << data << "\t";
                    infile >> data;
                    std::cout << data << "\t";
                }
            }
            }
    };
    return 0;
}
