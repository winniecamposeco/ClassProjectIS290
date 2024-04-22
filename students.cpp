//Database Management Systems

#include <iostream>
/*conio.h is for getch and gotxy functions. Allows reading one character at a time without having to
press the Enter key and also allows placing the cursor at a specific location in the terminal*/
#include <conio.h>
//to work with chains
#include <string.h>
//to work with text archives
#include <fstream>
//so the code for clear the screen works
#include <stdlib.h>
#include <cstdlib>

//to clear the screen. If we have an error, it will clean the screen.
#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix) ||defined(__unix__) ||defined(__unix)||defined(__APPLE__) ||defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO is not supported to clean screen"
#endif

//This function helps us to not write std::cout every time.
using namespace std;

//With this, we created a class
class menu

{
private:
    //the guy uses char in the video and string in the written code on github
    string name;
    string address;
    string cellphone;
    string studentID;
    string dateofbirth;

 public:
    void enterStudent();
    void detailStudent();
    void listStudents();
    void searchStudent();
    void deleteStudent();
    void modifyStudent();
    void mainMenu();
    void showRegistration(string code);
};

//to pause and continue the program, I think
void pause();
//to show error messages
void error();
void chanceArchive();

void menu::mainMenu()
{
    int option;
    do
    {
        /* code and what will be showing on the screen */
        std::cout<<"\t\t\t\t***Registration of Student***\t\t\t\t\n\n";
        std::cout<<"1. Register new student\n\n";
        std::cout<<"2. Show details of a student\n\n";
        std::cout<<"3. List of all students\n\n";
        std::cout<<"4. Search for a student\n\n";
        std::cout<<"5. Delete student\n\n";
        std::cout<<"6. Modify student information\n\n";
        std::cout<<"7. Exit\n\n";
        std::cout<<"Option: ";
        cin>>option;
        system(CLEAR);
        switch(option)
        {
        default:
            std::cout<<"You have entered an invalid option!\n\n";
            break;

        case 1:
            enterStudent();
            break;

        case 2:
            detailStudent();
            break;

        case 3:
            listStudents();
            break;
        
        case 4:
            searchStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            modifyStudent();
            break;
        //if we enter 7, it will go to the next thing we programmed, that it is nothing, so it will close the program.
        case 7:
            break;
        }
    } 
    while (option!=7);
    
}

void menu::enterStudent()
{
    /*this is a pointer, a data type, it allow us to send the data from the RAM to the text file. Any information entered in the program,
    will be saved in the RAM temporarely, and then sent to the file text. Structure mode*/ 
    ofstream writting;
    //reading mode. It will verify if there are repeated codes
    ifstream verificator;
    //local variable used to compare if the code was repeated or not.
    string auxCode;
    bool coincidence=false;
    //for now, it should be where the surse code is and not in a folder. In: input from textfile to ram
    verificator.open("students.txt",ios::in);
    //app is to overwrite a file, if it doesn't exist, it will create it, and will keep the info safe and able to be overwritten
    writting.open("students.txt",ios::app);
    if(writting.is_open()&&verificator.is_open())
    {
        std::cout<<"\t\t\t\t***Enter a new student***\t\t\t\t\n\n";
        //cleans the keyboard of extra characters
        fflush(stdin);
        std::cout<<"Enter student ID number: ";
        //scan all the line, even if there are spaces, until user press Enter
        std::getline(cin,auxCode);
        //this compares chains
        if(auxCode=="")
            do
            {
                std::cout<<"Invalid student ID number, try again: ";
                std::getline(cin,auxCode);
            }
            while (auxCode=="");
            //another control structure
            do
            {
            //0 is the position of the pointer
            verificator.seekg(0);
            verificator>>studentID;
            //eof=end of file. It a function that after reading the file, it returns a True because there is no more to read.
            while (!verificator.eof())
            {
                //It will continue to verify the rest of the information of the student
                verificator>>name>>address>>cellphone>>dateofbirth;
                
                //it will compare the code entered by the user with IDs saved in the file, if they are repeated, it will activate the next block
                 if(studentID==auxCode)
                {
                
                        coincidence=true;
                        std::cout<<"\n\nThis ID number is already in use!\n\n";
                        std::cout<<"The student with this ID number is: " <<name<<"\n\n";
                        std::cout<<"Enter a valid ID number!: ";
                        std::getline(cin,auxCode);
                        if(auxCode=="")
                        do
                        {
                            std::cout<<"Invalid student ID number, try again: ";
                            std::getline(std::cin, auxCode);
                        } 
                        while (auxCode=="");
                    
                    break;                
                }
                
                verificator>>studentID;
            }
        
            if(verificator.eof()&&(auxCode!=studentID))
            coincidence=false;
        }
        while (coincidence==true);
        system(CLEAR);
        studentID= auxCode;
        std::cout<<"\t\t\t\t***Register a new Student***\t\t\t\t\n\n";
        std::cout<<"Enter student ID number: ";
        std::getline(cin,studentID);
        std::cout<<"\n\n";
        fflush(stdin);
        std::cout<<"Enter student name: ";
        std::cin>>name;
        std::cout<<"\n\n";
        std::cout<<"Enter student address: ";
        std::getline(cin, address);
        std::cout<<"\n\n";
        fflush(stdin);
        std::cout<<"Enter student cellphone: ";
        std::getline(cin,cellphone);
        std::cout<<"\n\n";
        fflush(stdin);
        std::cout<<"Enter student Date of Birth: ";
        std::getline(cin, dateofbirth);
        std::cout<<"\n\n";

        writting<<studentID<<"\n\n"<<name<<"\n\n"<<address<<"\n\n"<<cellphone<<"\n\n"<<dateofbirth<<"\n\n";

        std::cout<<"Registration completed succesful ly.\n\n";
    }
           
    //
    else
    {
        error();
    }

    writting.close();
    verificator.close();
    pause();
}

void menu::detailStudent()
{
    string auxCode;
    ifstream show;
    bool found=false;
    show.open("students.txt",ios::in);
    if(show.is_open())
    {
        fflush(stdin); //this time he had this line before the title of the page
        cout<<"\t\t\t\t***Consult details of Student***\t\t\t\t\n\n";
        
        getline(cin, auxCode);
        
        if(!show.eof())
        {
            cout<<"There are students registered yet.";
        }

        else
        {
            show.seekg(0);
            cout<<"Enter student ID number to get details: ";
            getline(cin, auxCode);
            getline(show, studentID);
            while(!show.eof())
            {
                getline(show, name);
                getline(show, address);
                getline(show, cellphone);
                getline(show, dateofbirth);
                if(auxCode==studentID)
                {
                    found=true;
                    cout<<"\n\nInformation of Student found:\n\n";
                    cout<<"Student ID number: "<<studentID <<endl;
                    cout<<"Name: "<<name<<endl;
                    cout<<"Address: "<<address<<endl;
                    cout<<"Phone number: "<<cellphone<<endl;
                    cout<<"Date of Birth: "<<dateofbirth<<endl;
                    cout<<"\n\n";
                }
                getline(show, studentID);
            }
        
            if(found==false)
            {
                cout<<"\n\nStudent details not found registered: "<<auxCode<<"\n\n";
            }
        }
    }

    else
    {
        error();
    }

    show.close();
    pause();
}

void menu::listStudents()
{
    int i=0;
    ifstream lecture;
    lecture.open("students.txt",ios::in);
    if(lecture.is_open())
    {
        cout<<"\t\t\t\t***List of all students***\t\t\t\t\n\n";
        getline(lecture,studentID); //lecture>>studentID;
        while(!lecture.eof())//this will repeat until the end of the file is different
        {
            i++;
            lecture>>name>>address>>cellphone>>dateofbirth;
            cout<<"Student ID number: "<<studentID<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"Address: "<<address<<endl;
            cout<<"Phone number: "<<cellphone<<endl;
            cout<<"Date of Birth: "<<dateofbirth<<endl;
            cout<<"\n\n";
            lecture>>studentID;
        }

        if(i==1) //the other option can bie i==0. The video code eliminated the {}, I am not sure if they are important or not
            cout<<"There is no student regtistered in this database\n\n";
        //}
        else if(i==1)
        //{
            cout<<"There is one student registered\n\n";
        //}

        else if(i>1)
        {

            cout<<"There are "<<i<<" students registered in this database\n\n";
        }
    }
    else
    {
        error();
    }
    lecture.close();
    pause();
}

void menu::deleteStudent()
{
    ifstream lecture;
    ofstream auxiliar;
    bool found=false;
    string auxCode;
    string answer;
    lecture.open("students.txt",ios::in);
    auxiliar.open("auxiliar.txt",ios::out);//creates the file if it doesn't exist or rewrite it
    cout<<"\t\t\t\t***Delete a Student***\t\t\t\t\n\n";
    if(lecture.is_open()&&auxiliar.is_open() )
    {
        fflush(stdin);
        cout<<"Enter the ID number of the student you wish to delete: ";
        getline(cin, auxCode);
        lecture>>studentID;
        while(!lecture.eof())
        {
            lecture>>name>>address>>cellphone>>dateofbirth;
            if(auxCode==studentID)
            {
                found=true;
                cout<<"\n\nRegister found\n\n";
                cout<<"Student ID number: "<<studentID<<endl;
                cout<<"Name: "<<name<<endl;
                cout<<"Address: "<<address<<endl;
                cout<<"Phone number: "<<cellphone<<endl;
                cout<<"Date of Birth: "<<dateofbirth<<endl;
                cout<<"\n\n";
                cout<<"Do you really wish to delete: "<<name<<" (s/n)?: ";
                getline(cin, answer);//number of the variable. Maybe it needs to be a higher number
                if(answer=="y"||answer=="Y"||answer=="yes"||answer=="YES"||
                        answer=="Yes"||answer=="yES"||answer=="yeS"||answer=="YEs"
                        ||answer=="ye"||answer=="YE")
                {
                    cout<<"\n\nStudent has been deleted succesfully\n\n";
                }

                else
                {   
                    cout<<"\n\nStudent information still conserved\n\n";
                    auxiliar<<studentID<<endl<<name<<endl<<address<<endl<<cellphone<<endl<<dateofbirth<<endl;
                }//Voy por aquí, 6:27pm, 2/29/2024 video min. 13.10
            }
            else
            {
                auxiliar<<studentID<<"\n\n"<<name<<"\n\n"<<address<<"\n\n"<<cellphone<<"\n\n"<<dateofbirth<<"\n\n";
            }
            lecture>>studentID;//to end the block
        }
        if(found==false)
        {
            cout<<"\n\nRegistration of this student was not found: "<<auxCode<<"\n\n";
        }
        
    }
    else
    {
        error();
    }
    lecture.close();
    auxiliar.close();
    remove("students.txt");//it will delete the students file along with the info of the student we want to eliminate. The other information will be copied to a new file called auxiliar
    rename("auxiliar.txt","students.txt");//It is going to rename the auxiliar file to students again
    pause();
}

void menu::modifyStudent()
{
    ifstream lecture;
    ifstream verificator;
    ofstream auxiliar;
    string auxCode;
    string codeModify;
    string auxName;
    string auxAddress;
    string auxCellphone;
    string auxDateofbirth;
    bool found=false;
    bool coincidence=false;
    bool sameCode=false;
    lecture.open("students.txt",ios::in);
    verificator.open("students.txt",ios::in);
    auxiliar.open("auxiliar.txt",ios::out);
    cout<<"\t\t\t\t***Modify information of a student***\t\t\t\t\n\n";
    if(lecture.is_open()&&verificator.is_open()&&auxiliar.is_open())
    {
        fflush(stdin);
        cout<<"Enter student ID number that you wish to modify: ";
        cin>>auxCode;
        
        if(auxCode=="")
        {
            do
            {
                cout<<"Student ID not valid!, try again: ";
                getline(cin,auxCode);
            }
            while(auxCode=="");
        }

        codeModify=auxCode;//this work if it is not found. strcpy means it copies one chain to other

        lecture>>studentID;
        while(!lecture.eof())
        {
            getline(lecture,name);
            getline(lecture,address);
            getline(lecture,cellphone);
            getline(lecture,dateofbirth);
            if(auxCode==studentID)
            {
                found=true;
                showRegistration(codeModify);

                cout<<"**********************************************";
                cout<<"\n\n";
                cout<<"Enter new information for the student\n\n";
                fflush(stdin);
                cout<<"Enter student ID number: ";
                getline(cin, auxCode);
                if(auxCode==codeModify)//this will check if the new id is the same as the old one and keep it if it is true
                {
                    sameCode=true;
                }
                if(sameCode==false)//if the new ID is not the same as the old one then it will follow this code
                {
                    do
                    {
                        verificator.seekg(0);
                        verificator>>studentID;
                        while(!verificator.eof())
                        {
                            verificator>>name>>address>>cellphone>>dateofbirth;

                            if(studentID==auxCode)
                            {
                                coincidence=true;
                                cout<<"\n\nThere is an existing student with this ID number!\n\n";
                                cout<<"The student with this ID number is: "<<name<<"\n\n";
                                cout<<"Enter a valid ID number!: ";
                                getline( cin,auxCode);
                                if(auxCode==codeModify)
                                {
                                    coincidence=false;
                                    break;
                                }
                                if(auxCode=="")//if the user press enter it will recognize the ID as invalid
                                {
                                    do
                                    {
                                        cout<<"\nStudent ID number not valid!, ";
                                        cout<<"Try again: ";
                                        getline(cin, auxCode);
                                    }
                                    while(auxCode=="");
                                }
                                break;
                            }

                            verificator>>studentID;
                        }

                        if(verificator.eof()&&(auxCode!=studentID))
                        {
                            coincidence=false;
                        }

                    }
                    while(coincidence==true);
                }
                system(CLEAR);//clear the screen from all the errors we have got
                cout<<"***Modify information of a student***\n\n";
                cout<<"Enter ID number of the student that you wish to modify: ";
                cout<<codeModify;
                showRegistration(codeModify);
                cout<<"**********************************************";
                cout<<"\n\n";
                cout<<"Enter new information for the student\n\n";
                cout<<"Enter new student ID number: ";
                cout<<auxCode;
                cout<<"\n\n";
                fflush(stdin);
                cout<<"Enter student new name: ";
                getline(cin, auxName);
                fflush(stdin);
                cout<<"\n\n";
                cout<<"Enter student new address: ";
                getline(cin, auxAddress);
                cout<<"\n\n";
                fflush(stdin);
                cout<<"Enter student new cellphone: ";
                getline(cin, auxCellphone);
                cout<<"\n\n";
                fflush(stdin);
                cout<<"Enter student new date of birth: ";
                getline(cin, auxDateofbirth);
                cout<<"\n\n";
                auxiliar<<auxCode<<endl<<auxName<<endl<<auxAddress<<endl<<auxCellphone
                            <<endl<<auxDateofbirth<<endl;
                cout<<"Student information has been modified correctly.\n\n";
            }


            else
            {
            
                   auxiliar<<studentID<<endl<<name<<endl<<address<<endl<<cellphone
                            <<endl<<dateofbirth<<endl;
            }

            lecture>>studentID;
        }
    
    }
    else
    {
        error();
    }

    if(found==false)
    {
        cout<<"\n\nThere is not resgistration of this student ID number!\n\n";
    }
        
    lecture.close();
    verificator.close();
    auxiliar.close();
    remove("students.txt");
    rename("auxiliar.txt","students.txt");
    pause();
}

void menu::searchStudent()
{
    ifstream lecture;
    lecture.open("students.txt",ios::in);
    int found;
    string searchName;

    std:;cout<<"***Search Student***"<<endl<<endl;
    if(lecture.is_open())
    {
        std::cout<<"Enter name of student: ";
        fflush(stdin);
        std::getline(cin, searchName);
        found=0;
        std::cout<<endl;

        std::getline(lecture, studentID);
        while(!lecture.eof())
        {
            std::getline(lecture,name);
            std::getline(lecture,address);
            std::getline(lecture,cellphone);
            std::getline(lecture,dateofbirth);
            if(name.find(searchName)!=string::npos)
            {
                cout<< "Student ID: "<<studentID<<endl;
                cout<< "Name: "<<name<<endl;
                cout<< "Address: "<<address<<endl;
                cout<< "Cellphone: "<<cellphone<<endl;
                cout<< "Date of Birth: "<<dateofbirth<<endl;
                cout<< "\n\n";
                found++;
            }

            getline(lecture, studentID);
        }
        if(found)
        {
            cout<<"We have found "<<found<<" in our records with the word you provided"<<endl;
        }
        else
        {
            cout<<"We could not find any records of the word you provided."<<endl;
        }
    }
    else{
        cout<<endl<<"The file cannot be open!";
    }
    lecture.close();
    pause();
}

void pause()
{
    std::cout<<"Press Enter to continue...";
    getch();
    system(CLEAR);
}

//this will close the program if the the option chosen is invalid. The f0 color is white background and black letters   


void error()
{
    std::cout<<"File could not been open, make sure the file is in\n";
    std::cout<<"the same place as the program, or that the text file is called: \n";
    std::cout<<"students.txt, if the file has another name, remember to mention it\n\n";
}

int main ()
{
    //we creat an object called start
    menu start;
    //this object start will be a function. All the program runs on this function, main menu
    chanceArchive();
    start.mainMenu();
    //when the person enter 7, the program will end
    return 0;
}

void chanceArchive()
{
    ifstream archive;
    archive.open("students.txt",ios::in);
    if(!archive.is_open())
    {
        std::cout<<"The file of records could not be open or there are not students registered yet!";
        std::cout<<"\n\n";
        std::cout<<"To create a file of records select the 'Register New Student' option.\n\n";
        pause();
        system(CLEAR);
    }
}

void menu::showRegistration(string code)
{

    ifstream show;
    show.open("students.txt",ios::in);
    show>>studentID;
    while(!show.eof())
    {
        show>>name>>address>>cellphone>>dateofbirth;
        if(code==studentID)
        {
            std::cout<< "\n\nInformation of student found\n\n";
            std::cout<< "Student ID: "<<studentID<<endl;
            std::cout<< "Name: "<<name<<endl;
            std::cout<< "Address: "<<address<<endl;
            std::cout<< "Cellphone: "<<cellphone<<endl;
            std::cout<< "Date of Birth: "<<dateofbirth<<endl;
            std::cout<< "\n\n";
            break;
        }
        show>>studentID;
    }
    show.close();
}
