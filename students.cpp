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
    string name[30];
    string address[60];
    //we are going to use char to reduce errors with mistakes
    string cellphone[20];
    string studentID[30];
    string staffID[30];
    string dateofbirth[10];

 public:
    void enterStudent();
    void deleteStudent();
    void modifyStudent();
    void listStudents();
    void mainMenu();
    void detailStudent();
    void showRegistration(string code [30]);
    void searchStudent();
};

//to pause and continue the program, I think
void pause();
//to show error messages
void error();
void checkArchive();

void menu::mainMenu()
{
    int option;
    do
    {
        /* code and what will be showing on the screen */
        cout<<"\t\t\t\t***Registration of Student and Staff of BT Building***\t\t\t\t\n\n";
        cout<<"1. Register new student\n\n";
        std::cout<<"2. Show details of a student\n\n";
        cout<<"3. List of all students\n\n";
        cout<<"4. Search for a student\n\n"; //I have doubts about this option
        cout<<"5. Delete student\n\n";
        cout<<"6. Modify student information\n\n";
        cout<<"7. Exit\n\n";
        cout<<"Option: ";
        cin>>option;
        system("cls");
        switch(option)
        {
        default:
            cout<<"You have entered an invalid option!\n\n";
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
            searchStudent(); //again, I think we can delete this option
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
        cout<<"\t\t\t\t***Enter a new student***\t\t\t\t\n\n";
        //cleans the keyboard of extra characters
        fflush(stdin);
        cout<<"Enter student ID number: ";
        //scan all the line, even if there are spaces, until user press Enter
        getline(cin, auxCode,30);
        //this compares chains
        if(strcmp(auxCode,"")==0)
            do
            {
                cout<<"Invalid student ID number, try again: ";
                getline(cin,auxCode,30);
            }
            while (strcmp(auxCode,"")==0);
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
                if(strcmp(studentID,auxCode)==0)
                {
                
                    coincidence=true;
                    cout<<"\n\nThis ID number is already in use!\n\n";
                    cout<<"The student with this ID number is: " <<name<<"\n\n";
                    cout<<"Enter a valid ID number!: ";
                    cin.getline(auxCode,30);
                    if(strcmp(auxCode,"")==0)
                        do
                        {
                            cout<<"Invalid student ID number, try again: ";
                            cin.getline(auxCode,30);
                        } 
                        while (strcmp(auxCode,"")==0);
                    
                    break;                
                }
                
                verificator>>studentID;
            }
        
            if(verificator.eof()&&strcmp(auxCode,studentID)!=0)
            coincidence=false;
        }
        while (coincidence==true);
        system(CLEAR);
        strcpy(studentID,auxCode);
        cout<<"\t\t\t\t***Register a new Student***\t\t\t\t\n\n";
        cout<<"Enter student ID number: ";
        cout<<studentID;
        cout<<"\n\n";
        fflush(stdin);
        cout<<"Enter student name: ";
        cin.getline(name,30);
        cout<<"\n\n";
        fflush(stdin);
        cout<<"Enter student address: ";
        cin.getline(address,60);
        cout<<"\n\n";
        fflush(stdin);
        cout<<"Enter student cellphone: ";
        cin.getline(cellphone,20);
        cout<<"\n\n";
        fflush(stdin);
        cout<<"Enter student Date of Birth: ";
        cin.getline(dateofbirth,10);
        cout<<"\n\n";

        writting<<studentID<<"\n\n"<<name<<"\n\n"<<address<<"\n\n"<<cellphone<<"\n\n"<<dateofbirth<<"\n\n";

        cout<<"Registration completed succesful ly.\n\n";
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
    char auxCode [30];
    ifstream show;
    bool found=false;
    show.open("students.txt",ios::in);
    if(show.is_open())
    {
        fflush(stdin); //this time he had this line before the title of the page
        cout<<"\t\t\t\t***Consult details of Student***\t\t\t\t\n\n";
        cout<<"Enter student ID number to get details: ";
        cin.getline(auxCode,30);
        show>>studentID;
        
        while(!show.eof())
        {
            show>>name>>address>>cellphone>>dateofbirth;
            if(strcmp(auxCode,studentID)==0)
            {
                show=true;
                cout<<"\n\nInformation of Student\n\n"; //I am not sure of this. Let's change it latter
                cout<<"Student ID number: "<<student ID<<endl;
                cout<<"Name: "<<name<<endl;
                cout<<"Address: "<<address<<endl;
                cout<<"Phone number: "<<cellphone<<endl;
                cout<<"Date of Birth: "<<dateofbirth<<endl;
                cout"\n\n";
            }

            show>>studentID;
        }
        //video code says "show", github code says "found"
        if(show==false)
        {
            cout<<"\n\nStudent details not found registered: "<<auxCode<<"\n\n";
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
    char auxCode[30];
    char answer[5];
    lecture.open("students.txt",ios::in);
    auxiliar.open("auxiliar.txt",ios::out);//creates the file if it doesn't exist or rewrite it
    cout<<"\t\t\t\t***Delete a Student***\t\t\t\t\n\n";
    if(lecture.is_open()&&auxiliar.is_open )
    {
        fflush(stdin);
        cout<<"Enter the ID number of the student you wish to delete: ";
        cin.getline(auxCode,30);
        lecture>>studentID;
        while(!lecture.eof())
        {
            lecture>>name>>address>>cellphone>>dateofbirth;
            if(strcmp(auxCode,studentID)==0)
            {
                found=true;
                cout<<"\n\nRegister found\n\n";
                cout<<"Student ID number: ">>studentID<<endl;
                cout<<"Name: "<<name<<endl;
                cout<<"Address: "<<address<<endl;
                cout<<"Phone number: "<<cellphone<<endl;
                cout<<"Date of Birth: "<<dateofbirth<<endl;
                cout<<"\n\n";
                cout<<"Do you really wish to delete: "<<name<<" (s/n)?: ";
                cin.getline(answer,5);//number of the variable. Maybe it needs to be a higher number
                if(answer=="y"||answer=="Y"||answer=="yes"||answer=="YES"||
                        answer=="Yes"||answer=="yES"||answer=="yeS"||answer=="YEs"
                        ||answer=="ye"||answer=="YE")
                {
                    cout<<"\n\nStudent has been deleted succesfully\n\n";
                }

                else
                {   
                    cout<<"\n\nStudent information still conserved\n\n";
                    auxliar<<studentID<<endl<<name<<endl<<address<<endl<<cellphone<<endl<<dateofbirth<<endl;
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
    char auxCode[30];
    char codeModify[30];
    char auxName[30];
    char auxAddress[60];
    char auxCellphone[20];
    char auxDateofbirth[20];
    bool found=false;
    bool coincidence=false;
    bool sameCode=false;
    lecture.open("students.txt",ios::in);
    verificador.open("students.txt",ios::in);
    auxiliar.open("auxiliar.txt",ios::out);
    cout<<"\t\t\t\t***Modify information of a student***\t\t\t\t\n\n";
    if(lecture.is_open()&&verificator.is_open()&&auxiliar.is_open())
    {
        fflush(stdin);
        cout<<"Enter student ID number that you wish to modify: ";
        cin.getline(auxCode,30);
        
        if(strcmp(auxCode,"")==0)
        {
            do
            {
                cout<<"Student ID not valid!, try again: ";
                cin.getline(auxCode,30);
            }
            while(strcmp(auxCode,"")==0);
        }

        strcpy(codeModify,auxCode);//this work if it is not found. strcpy means it copies one chain to other

        lecture>>studentID;
        while(!lectura.eof())
        {
            getline(lecture,name);
            getline(lecture,address);
            getline(lecture,cellphone);
            getline(lecture,dateofbirth);
            if(strcmp(auxCode,studentID)==0)
            {
                found=true;
                showInfo(codeModify);

                cout<<"**********************************************";
                cout<<"\n\n";
                cout<<"Enter new information for the student\n\n";
                fflush(stdin);
                cout<<"Enter student ID number: ";
                cin.getline(auxCode,30);
                if(strcmp(auxCode,codeModify)==0)//this will check if the new id is the same as the old one and keep it if it is true
                {
                    sameCode=true;
                }
                if(sameCode==false)//if the new ID is not the same as the old one then it will follow this code
                {
                    do
                    {
                        verificator.seekg(0);
                        verificator>>studentID;
                        while(!verificador.eof())
                        {
                            verificador>>name>>address>>cellphone>>dateofbirth;

                            if(strcmp(studentID,auxCode)==0)
                            {
                                coincidence=true;
                                cout<<"\n\nThere is an existing student with this ID number!\n\n";
                                cout<<"The student with this ID number is: "<<name<<"\n\n";
                                cout<<"Enter a valid ID number!: ";
                                cin.getline(auxCode,30);
                                if(strcmp(auxCode,codeModify)==0)
                                {
                                    coincidence=false;
                                    break;
                                }
                                if(strcmp(auxCode,"")==0)//if the user press enter it will recognize the ID as invalid
                                {
                                    do
                                    {
                                        cout<<"\nStudent ID number not valid!, ";
                                        cout<<"Try again: ";
                                        cin.getline(auxCode,30);
                                    }
                                    while(strcmp(auxCode,"")==0);
                                }
                                break;
                            }

                            verificador>>studentID;
                        }

                        if(verificador.eof()&&strcmp(auxCode,studentID)!=0)
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
                showInfo(codeModify);
                cout<<"**********************************************";
                cout<<"\n\n";
                cout<<"Enter new information for the student\n\n";
                cout<<"Enter new student ID number: ";
                cout<<auxCode;
                cout<<"\n\n";
                fflush(stdin);
                cout<<"Enter student new name: ";
                cin.getline(auxName,40);
                fflush(stdin);
                cout<<"\n\n";
                cout<<"Enter student new address: ";
                cin.getline(auxAddress,60);
                cout<<"\n\n";
                fflush(stdin);
                cout<<"Enter student new cellphone: ";
                cin.getline(auxCellphone,20);
                cout<<"\n\n";
                fflush(stdin);
                cout<<"Enter student new date of birth: ";
                cin.getline(auxDateofbirth,30);
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

            lectura>>studentID;
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
    pausa();
}

void pause()
{
    cout<<"Press Enter to continue...";
    getch();
    system(CLEAR);
}

//this will close the program if the the option chosen is invalid. The f0 color is white background and black letters   
int main ()
{
    system (*color f0*);
    //we creat an object called start
    menu start;
    //this object start will be a function. All the program runs on this function, main menu
    start.mainMenu();
    //when the person enter 7, the program will end
    return 0;
}

void error()
{
    cout<<"File could not been open, make sure the file is in\n";
    cout<<"the same place as the program, or that the text file is called: \n";
    cout<<"students.txt, if the file has another name, remember to mention it\n\n";
}

void menu::showRegistration(char code[30])
{

    ifstream show;
    show.open("student.txt",ios::in);
    show>>studentID;
    while(!show.eof())
    {
        show>>name>>address>>cellphone>>dateofbirth;
        if(strcmp(code,studentID)==0)
    }
}
