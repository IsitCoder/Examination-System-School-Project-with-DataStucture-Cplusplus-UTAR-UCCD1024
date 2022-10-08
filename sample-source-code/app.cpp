#define _CRT_SECURE_NO_WARNINGS
#include	<iostream>
#include	<fstream>
#include	"List.h"
#include	"Student.h"
#include	<cstring>
#include	<sstream>

using namespace std;
int menu();
bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool DisplayStudent(List, int);
bool AddExamResult(const char*, List*);
bool FilterStudent(List, List *, char *, int, int);
double ReviseGradePoint(double);
const char* getRevisedGrade(double);
bool recalculateResult(List, char *);
bool checkEligibleFYP(List, char *);
bool ClearFilterList(List *);




using namespace std;

#define MAXLEN 30



int main() {

	menu();

	return 0;
}


int menu()
{
	List StudentList;
	List FilterList;
	ifstream in;
	//const char* filename = "student.txt";
	char ID[12];
	char course[3];
	char year[5];
	char totalcredithours[4];
	int yr, totalch;
	//char ID[] = "1300899";
	//char id[] = "1200233";
	//char course[] = "IB";

	
	
	int quit = 0;
	string action;
	char source;
	int src;

	while (!quit)
	{
		cout << "\n\t\t******************************************";
		cout << "\n\t\t\t**\tMenu\t\t\t**";
		cout << "\n\t\t******************************************\n\n";
		cout << "\t\t1. Create student list\n";
		cout << "\t\t2. Delete student\n";
		cout << "\t\t3. Display student list\n";
		cout << "\t\t4. Add exam result\n";
		cout << "\t\t5. Recalculate Result\n";
		cout << "\t\t6. Filter Student\n";
		cout << "\t\t7. Check Eligible FYP Student\n";
		cout << "\t\t8. Clear Filter List\n";
		cout << "\t\t9. Exit.\n";
		cout << "\tPlease enter your option: ";
		cin >> action;
		cout << "\n\n";

		switch (action[0])
		{
		case '1': 
		
			if (CreateStuList("student.txt", &StudentList))
			cout << "\n\nCreate Student List Completed\n\n";
				else
			cout << "\n\nFailed to Create Student List\n\n"; 
		
			break;

		case '2':
		
			cout << "\n\nPlease Enter Student ID to delete : ";
			cin >> ID;
			


			if (DeleteStudent(&StudentList, ID))
				cout << "\n\nDelete Completed\n\n";
			else
				cout << "\n\nDelete Failed\n\n";
		
		break;

		case '3':
		
			cout << "(screen(source = 1) or file(source = 2).\n"
				<< "Please enter source to display: ";
			cin >> source;

			switch (source)
			{
				case '1':
				case '2':
				{
					src = (int)source-'0'; //convert char to int
					DisplayStudent(StudentList, src);
				}
				break;

				default:
				cout << "\n\nWrong input selection, Please use 1 or 2 for input\n\n";
				break;
			}
			
		
		break;

		case '4':	
		
			if (AddExamResult("exam.txt", &StudentList))
				cout << "\n\nExam Records Added Completed\n\n";
			else
				cout << "\n\nFailed to Add Exam Records\n\n";
		
		break;

		case '5':
		
			cout << "\n\nPlease Enter Student ID for revised : ";
			cin >> ID;

			if (recalculateResult(StudentList, ID))
				cout << "\n\nResult Recalculate Completed\n\n";
			else
				cout << "\n\nFailed to recalulate the result of student\n\n";
			
		
		break;

		case '6':
		
			cout << "\nPlease Enter Course, and Total Credit Hour for filtering\n";
			cout << "Course: ";
			cin >> course;
			cout << "\nYear: ";
			cin >> year;
			cout << "\nTotal Credit Hours: ";
			cin >> totalcredithours;
			

			yr = stoi(year);
			totalch = stoi(totalcredithours);
			

			if (FilterStudent(StudentList, &FilterList, course, yr, totalch))
			{
				DisplayStudent(FilterList, 1);
				cout << "\n\nFilter and Display the List Completed\n\n";
			}
			else
				cout << "\n\nFailed to filter the StudentList\n\n";
		
		break;

		case '7':
		
			cout << "\n\nPlease Enter Student ID for revised : ";
			cin >> ID;
			if (strlen(ID) == 0)
			{
				cout << "\n\nWrong input, Please enter again\n\n";
				break;
			}

			if (checkEligibleFYP(StudentList, ID))
				cout << "\n\nCheck Eligible Student for FYP Completed\n\n";
			else
				cout << "\n\nFailed To Check Eligible FYP For Student\n\n";
				
		
		break;

		case '8':	
			if (ClearFilterList(&FilterList))
				cout << "\nClear Filter List Completed\n\n";
			else
				cout << "\nFailed to Clear Filter List\n\n";
			break;

		case '9':	quit = 1;
			break;

		default:	cout << "\tWrong selection. Please input again\n";
			break;
		}
	}
	cout << "\n\nExiting the program!!!";
	return 0;
}

/*--------------Create Student List by read txt file--------------
1)Check in stream and input file
1)Read records from text file
2)Check if empty list then insert and record
3)Check if no empty then check duplicate before insert, if duplicate then display error msg
4)Check if no duplicate then insert record into list
5)Continue record the next record until the End Of File
*/

bool CreateStuList(const char* filename, List* list)
{
	ifstream in;
	char s[256];
	Student stu[MAXLEN];
	bool duplicate = false;

	/*Check for input file*/

	in.open(filename);
	if (!in)
	{
		cout << "Unable to open file:" << filename << "\n";
		return false;
	}
	else
	{
		int count = 0;



		while (!in.eof())//read and print record
		{
			duplicate = false;
			cout << "Inserting Record..." << '\t';

			for (int i = 1; i <= 4; i++)
				in >> stu[count].id;
			cout << stu[count].id << '\t';


			for (int i = 1; i <= 3; i++)
				in >> stu[count].name;
			in.getline(s, 30);
			strcat_s(stu[count].name, s);
			cout << stu[count].name << '\t';


			for (int i = 1; i <= 3; i++)
				in >> stu[count].course;
			cout << stu[count].course << '\t';

			for (int i = 1; i <= 4; i++)
				in >> stu[count].phone_no;
			cout << stu[count].phone_no << "\n\n";



			if (!list->empty()) //check IF list is not empty then check record duplicate
			{

				Node* cur;

				cur = list->head;

				while (cur != NULL)
				{
					if (cur->item.compareID(stu[count]))
					{
						cout << "WARNING: Duplicate record for student with ID: " << stu[count].id << "\n\n";
						duplicate = true;
						break;
					}
					cur = cur->next;
				}

			}


			if (!duplicate) //no duplicate then insert student record to the list
			{
				list->insert(stu[count]);
				count++;
			}


		}
		// Return List Created Successfully Msg
		cout << "Total " << count << " student inserted successfully in Student List\n\n";
		return true;
	}
	in.close();
}


/*--------------Delete Student in list with ID--------------
1)Check list empty
2)Find and match Id in the list
3)call list.remove function to delete student in list
4)ID was not founded in the List, return error msg
*/

bool DeleteStudent(List* list, char* id)
{
	/*Check for empty list*/
	if (list->empty())
	{
		cout << "The list was empty, No record founded\n\n";
		return false;
	}

	Node* cur;
	cur = list->head;
	int i = 1;

	/*Match the Student ID in list
	then remove the student from list*/

	while (cur != NULL)
	{
		if (strcmp(cur->item.id, id) == 0) {
			if (list->remove(i))
			{
				cout << "\n\nStudent record with ID : " << id << " was delete successfully!\n\n";
				return true;
				//delete successfully return to menu
			}
			else
			{
				cout << "\n\nWarning: Failed to student record with ID: " << id << " !!\n\n";
				return false;
				//Failed to process delete function, return to menu
			}

		}
		cur = cur->next;
		i++;
	}

	//ID was not founded in the List 
	cout << "Student records : " << id << " was not founded\n\n";
	return false;
}


/*--------------Display student in list on screen or in Txt file--------------
1)Check list empty
2)check and validate user input
3)if input '1' display on screen
4)if input '2' write in student_result.txt
*/


bool DisplayStudent(List list, int source) {

	/*Check for empty list*/
	if (list.empty())
	{
		cout << "\n\n there are no records in the Student list\n\n";
		return false;
	}

	/*Validate user input*/
	switch (source)
	{
	case 1: //Display Student List on screen
	{
		Node* cur;
		cur = list.head;
		int studcount = 1;
		while (cur != NULL)
		{
			cout << "\n\n***********************************STUDENT " << studcount << "****************************************\n\n";
			cur->item.print(cout);
			if (cur->item.exam_cnt == 0)
			{
				cout << "\n\n!!! THIS STUDENT HAVEN'T TAKEN ANY EXAM YET !!!";
			}
			else
			{
				for (int i = 0; i < cur->item.exam_cnt; i++)
				{
					cout << "\n\n---------------------------------------PAST EXAM RESULT------------------------------------------\n\n";
					cur->item.exam[i].print(cout);

				}
			}

			cout << "\n\n***********************************STUDENT " << studcount << "****************************************\n\n";
			cur = cur->next;
			studcount++;

		}
		cout << "\n\nTotal " << studcount - 1 << " students record have been displayed!\n\n";
		return true;


	}break;
	case 2: //Display Student List in student_result.txt
	{
		Node* cur;
		cur = list.head;
		int studcount = 1;
		ofstream out;
		out.open("student_result.txt");

		if (!out)
		{
			cout << "\n\nFailed to write Student info at student_result.txt file\n\n";
			return false;
		}

		while (cur != NULL)
		{
			out << "\n\n***********************************STUDENT " << studcount << "****************************************\n\n";
			cur->item.print(out);
			if (cur->item.exam_cnt == 0)
			{
				out << "\n\n!!! THIS STUDENT HAVEN'T TAKEN ANY EXAM YET !!!";
			}
			else
			{
				for (int i = 0; i < cur->item.exam_cnt; i++)
				{
					out << "\n\n---------------------------------------PAST EXAM RESULT------------------------------------------\n\n";
					cur->item.exam[i].print(out);

				}
			}

			out << "\n\n***********************************STUDENT " << studcount << "****************************************\n\n";
			cur = cur->next;
			studcount++;

		}
		cout << "\n\nTotal " << studcount - 1 << " students record have been written to student_result.txt!\n";
		out.close();
		return true;
	}
	break;
	default:
	{
		cout << "\n\nUser key in wrong input\n\n";
		return false;
	}

	}
}



/* -------------Add and link the exam record with the students in Student List--------------
1)Check list empty
2)Check in stream and input file
3)Find and match the record with student ID
4)Check for duplicate exam records between exam.txt and Student List with trimester and year
5)If duplicate exam record founded in list, ignore it and read next records
6)Insert the subjects and exam records to student in the list
7)Add count exam_cnt in Student
8)If student ID not founded in List, return error msg
*/

bool AddExamResult(const char* filename, List* list)
{
	ifstream in;
	char studentid[12];


	/*Check for empty list*/
	if (list->empty())
	{
		cout << "\n\nNo Records Founded In Student List!!!\n";
		cout << "\n\n*Please enter student records into list first\n";
		return false;
	}

	/*Check for input file*/
	in.open(filename);
	if (!in)
	{
		cout << "Unable to open file:" << filename << "\n";
		return false;
	}
	else
	{
		int recordcount = 0;
		int examnum;
		bool studentidfounded = false;
		bool s_duplicate = false;
		Node* cur;


		while (!in.eof())
		{
			studentidfounded = false;
			s_duplicate = false;
			cur = list->head;
			Exam examcheck;
			Exam NotFound;

			in >> studentid;


			while (cur != NULL)
			{

			

				/*Check the record and matching with student ID before insert to list*/

				if (strcmp(cur->item.id, studentid) == 0)
				{

					examnum = cur->item.exam_cnt;
					in >> examcheck.trimester;
					in >> examcheck.year;


					//Check for duplicate exam records between exam.txt and Student List with trimester and year		

					for (int i = 0; i < examnum; i++)
					{
						if ((cur->item.exam[i].trimester == examcheck.trimester)
							&& (cur->item.exam[i].year == examcheck.year))
						{
							cout << "\n\nDUPLICATE WARINING: Exam record (Year "
								<< examcheck.year
								<< " Semester " << examcheck.printTrimester()
								<< ") on Student ID: " << cur->item.id
								<< " have been recorded in the list !!! ";

							/*
							If duplicate record founded before insert,
							-read through the remaining duplicate records until next new record start
							(read through until next Student ID appear)
							*/

							in >> examcheck.numOfSubjects;

							for (int b = 0; b < examcheck.numOfSubjects; b++)
							{
								in >> examcheck.sub[b].subject_code;
								in >> examcheck.sub[b].subject_name;
								in >> examcheck.sub[b].credit_hours;
								in >> examcheck.sub[b].marks;
							}
							s_duplicate = true;
							break;
						}
					}

					/*
					If NON duplicate record founded then:
					-insert the record to the Student List
					-Calulate the exam GPA and student CGPA
					-Add count exam_cnt in Student
					*/


					if (!s_duplicate)
					{
						//insert the record to the Student List
						cur->item.exam[examnum].trimester = examcheck.trimester;
						cur->item.exam[examnum].year = examcheck.year;

						in >> cur->item.exam[examnum].numOfSubjects;

						for (int b = 0; b < cur->item.exam[examnum].numOfSubjects; b++)
						{
							in >> cur->item.exam[examnum].sub[b].subject_code;
							in >> cur->item.exam[examnum].sub[b].subject_name;
							in >> cur->item.exam[examnum].sub[b].credit_hours;
							in >> cur->item.exam[examnum].sub[b].marks;

						}

						//Calulate the exam GPA and student CGPA, add count to exam_count in Student
						++cur->item.exam_cnt;
						cur->item.exam[examnum].calculateGPA();
						cur->item.calculateCurrentCGPA();
						

						recordcount++;
						studentidfounded = true;
						break;
					}
				}
				cur = cur->next;
			}

			/*
			if student ID not founded in List and no duplicate case
			-Read through remaining record and do nothing
			-continue read new exam records
			*/

			if (!studentidfounded && !s_duplicate)
			{

				cout << "\n\nStudent ID: " << studentid << " was not founded in the list\n\n";
				in >> NotFound.trimester;
				in >> NotFound.year;
				in >> NotFound.numOfSubjects;





				for (int j = 0; j < NotFound.numOfSubjects; j++)
				{
					in >> NotFound.sub[j].subject_code;
					in >> NotFound.sub[j].subject_name;
					in >> NotFound.sub[j].credit_hours;
					in >> NotFound.sub[j].marks;
				}
			}

			// continue read the next exam records


		}

		//show total how many record added
		cout << "\n\nTotal " << recordcount << " exam records added in StudentList\n\n";
		return true;
	}
	in.close();
}



/* Function to Revised Point of student mark use for recalculateResult*/
double ReviseGradePoint(double marks)
{
	if (marks >= 0 && marks < 36)
		return 0.00;
	else if (marks >= 36 && marks < 41)
		return 1.00;
	else if (marks >= 41 && marks < 46)
		return 2.33;
	else if (marks >= 46 && marks < 56)
		return 1.33;
	else if (marks >= 56 && marks < 61)
		return 1.67;
	else if (marks >= 61 && marks < 66)
		return 2.30;
	else if (marks >= 66 && marks < 71)
		return 2.70;
	else if (marks >= 71 && marks <= 76) //cover A and A+
		return 3.00;
	else if (marks >= 76 && marks < 81)
		return 3.30;
	else if (marks >= 81 && marks < 86)
		return 3.70;
	else if (marks >= 86 && marks <= 100) //cover A and A+
		return 4.00;
	else
		return -1.0;
}

/* Function to Revised Grade of student mark, use for recalculateResult*/
const char* getRevisedGrade(double marks)
{


	if (marks >= 0 && marks < 36)
		return "F";
	else if (marks >= 36 && marks < 41)
		return "E";
	else if (marks >= 41 && marks < 46)
		return "D-";
	else if (marks >= 46 && marks < 56)
		return "D";
	else if (marks >= 56 && marks < 61)
		return "C";
	else if (marks >= 61 && marks < 66)
		return "C+";
	else if (marks >= 66 && marks < 71)
		return "B-";
	else if (marks >= 71 && marks <= 76) //cover A and A+
		return "B";
	else if (marks >= 76 && marks < 81)
		return "B+";
	else if (marks >= 81 && marks < 86)
		return "A-";
	else if (marks >= 86 && marks <= 100) //cover A and A+
		return "A";
	else
		return "N/A";
}


/*--------------Recalculate the result of student--------------
1)Check List Empty
2)Find and match ID in the list
3)Print Original Exam Result
4)Calulating for revised result
5)Print Revised Exam Result
6)ID was not found in the List, return error messsage
*/

bool recalculateResult(List list, char* id)
{
	if (list.empty())//Check List Empty
	{
		cout << "\n\nThere are no records in the Student list\n\n";
		return false;
	}

	Node* cur;
	cur = list.head;


	while (cur != NULL)
	{
		if (strcmp((cur->item.id), id) == 0)					//Find and match ID in the list
		{
			if (cur->item.exam_cnt == 0)						//No Exam record return info and back to menu
			{
				cout << "\n\nThis student have not taken any exam yet and cannot recalculate result!\n\n";
				return false;
			}


			cout << "\n\nRESULT OUTPUT BASED ON ORIGINAL GRADING:\n";
			cout << "_________________________________________";

			cur->item.print(cout);								//Print Student Info

			for (int j = 0; j < cur->item.exam_cnt; j++)	//Print Original Exam Result
			{
				cout << "\n\n-----------------------------------------------ORIGINAL GRADING EXAM RESULT:-------------------------------------------------\n\n";
				cur->item.exam[j].print(cout);

			}
			cout << "\n\n-----------------------------------------------ORIGINAL GRADING EXAM RESULT:-------------------------------------------------\n\n";

			cout << "\n\nRESULT OUTPUT BASED ON REVISED GRADING:\n";
			cout << "_________________________________________";


			Student revisedStudent;		// Assign Student to space for recalutation
			revisedStudent = cur->item;


			for (int k = 0; k < revisedStudent.exam_cnt; k++)
			{
				double sum = 0;										//Calulating for revised result
				int total_credit_hours = 0;

				for (int j = 0; j < revisedStudent.exam[k].numOfSubjects; j++)
				{

					sum = sum + ReviseGradePoint(revisedStudent.exam[k].sub[j].marks) * revisedStudent.exam[k].sub[j].credit_hours;
					total_credit_hours = total_credit_hours + revisedStudent.exam[k].sub[j].credit_hours;
				}
				revisedStudent.exam[k].gpa = sum / (double)total_credit_hours;


			}
			revisedStudent.calculateCurrentCGPA();
			revisedStudent.print(cout);

			//Print Revised Exam Result

			cout << "\n\n-----------------------------------------------REVISED GRADING EXAM RESULT:-------------------------------------------------\n\n";
			for (int m = 0; m < revisedStudent.exam_cnt; m++)
			{

				cout << "\n\n" << revisedStudent.exam[m].printTrimester() << " " << revisedStudent.exam[m].year << " Exam Results: " << endl;

				cout << "\n" << revisedStudent.exam[m].numOfSubjects << " subjects taken.";
				cout << "\n___________________________________________________________________________________________________________________________";
				cout << "\nSubject Code\t" << setw(70) << left << "Subject Name" << "Credit Hours" << "\tGrade " << "\tGrade Point";
				cout << "\n___________________________________________________________________________________________________________________________";
				for (int j = 0; j < revisedStudent.exam[m].numOfSubjects; j++)
				{
					cout << "\n";
					cout << revisedStudent.exam[m].sub[m].subject_code << "\t" << setw(70) << left << revisedStudent.exam[m].sub[j].subject_name << setw(7) << right << revisedStudent.exam[m].sub[j].credit_hours <<
						"\t" << setw(10) << left << " " << getRevisedGrade(revisedStudent.exam[m].sub[j].marks) << "\t  " << setprecision(5) << fixed << showpoint <<
						ReviseGradePoint(revisedStudent.exam[m].sub[j].marks);
				}



				cout << "\nGPA: " << revisedStudent.exam[m].gpa;

				cout << "\n\n";



			}
			cout << "\n\n-----------------------------------------------REVISED GRADING EXAM RESULT:-------------------------------------------------\n\n";
			cout << "\n\nResults recalulated successfully!!!\n\n";
			return true;
		}
		cur = cur->next;
	}

	//ID was not found in the List, return error messsage
	
		cout << "\nThere is no student records : " << id << " in the list\nCannot recalculate result!\n\n";
		return false;
	
}



/*--------------Filter Student with course,year and totalcredit and insert to FilterList--------------
1)Check list 1 empty (StudentList)
2)Check list 2 empty (FilterList)
3)Find and match Student from list with year,course and total credit
4)Insert matched record to student list
5)No records match with student in Student List
*/

bool FilterStudent(List list1, List* list2, char* course, int year, int totalcredit)
{
	if (list1.empty())//Check List1 was empty 
	{
		cout << "The source list was empty, No record founded\n\n";
		return false;
	}

	if (!list2->empty())//Check List2 was not empty
	{
		cout << "The desination list was not empty, Please clear it first or choose another list\n\n";
		return false;
	}


	Node* cur;
	cur = list1.head;
	int count = 0;

	//Find and match Student from list with year,course and total credit

	string tmp = std::to_string(year);
	char const* enrollyear = tmp.c_str();

	while (cur != NULL)
	{
		if ((cur->item.id[0] == enrollyear[2]) && (cur->item.id[1] == enrollyear[3])) {
			if ((strcmp(cur->item.course, course) == 0) && (cur->item.totalCreditsEarned >= totalcredit))
			{
				list2->insert(cur->item);		//insert matched records to FilterList
				count++;
			}

		}
		cur = cur->next;
	}

	if (count == 0) //No records match with the filter in the List 
	{

		cout << "\nNo Student Records Matched with Filter, Please Try Again\n\n";
		return false;
	}
	// Show total student records inserted to FilterList
	cout << "Total " << count << " student records added in FilterList\n\n";
	return true;

}



/* --------------Check for Eligible FYP Student with ID--------------
1)Check list empty
2)Find and match student record with ID
3)Check subject Proposal and grade
4)Check subject Mini Project and grade
5)If student eligible FYP ,then display student detail
6)If no eligible display, unqualify msg
7)If ID not match in list, display student no founded msg
*/
bool checkEligibleFYP(List list, char* id)
{
	if (list.empty()) //check list empty
	{
		cout << "\n\nThere are no records in the Student list\n\n";
		return false;
	}

	Node* cur;
	cur = list.head;
	int examnum = 0;
	char Proposal[10]="UCCD2502";
	char MiniProject[10]="UCCD2513";
	bool PassProposal;
	bool PassMiniProject;
	char ProposalGrade[3] ;
	char MiniProjectGrade[3];

	while (cur != NULL)
	{
		if (strcmp((cur->item.id), id) == 0)	//Find and match ID in the list
		{
			PassProposal = false;
			PassMiniProject = false;

			if (cur->item.totalCreditsEarned>29)  // check for at least taken 30 credit hours
			{
				for (int j = 0; j < cur->item.exam_cnt; j++)
				{
					for (int i = 0; i < cur->item.exam[j].numOfSubjects; i++)
					{
						if ((strcmp((cur->item.exam[j].sub[i].subject_code), Proposal) == 0) && //check subject Proposal and grade
							cur->item.exam[j].sub[i].marks > 49)
						{
							PassProposal = "True";
							strcpy(ProposalGrade, cur->item.exam[j].sub[i].getGrade());

						}
			

						if ((strcmp((cur->item.exam[j].sub[i].subject_code), MiniProject) == 0) &&//check subject Mini Project and grade
							cur->item.exam[j].sub[i].marks > 49)
						{
							PassMiniProject = "True";
							strcpy(MiniProjectGrade, cur->item.exam[j].sub[i].getGrade());
						}


					}
				}
			}

				if (PassProposal && PassMiniProject)	// If Eligible for FYP, display student detail
				{
					cout << "\n\nThis student is eligible to take FYP. Below are the details of the students:\n";
					cout << "\nName: " << cur->item.name;
					cout << "\nId : " << cur->item.id;
					cout << "\nCourse : " << cur->item.course;
					cout << "\nPhone No : " << cur->item.phone_no;
					cout << "\nCurrent CGPA : " << cur->item.current_cgpa;
					cout << "\nTotal Credits Earned : " << cur->item.totalCreditsEarned;

					cout << "\n\nGrade obtained for UCCD2502 Introduction to Inventive Problem Solving is " << ProposalGrade;
					cout << "\nGrade obtained for UCCD2513 Mini Project " << MiniProjectGrade << "\n\n";

					return true;
				}
				else		//No eligible for FYP, display unqualify msg
				{
			
					cout << "\n\nThis student " << cur->item.name << " is not eligible to take FYP yet.\n\n";
					return false;
					
				}
			
		}
		cur = cur->next;
	}

	//ID was not found in the List 
	cout << "\nThere is no student with id  : " << id << " in the list."
		<<"\nCannot check if student is eligible for FYP.\n";
	return false;
}

/*Function use to remove all students' records in FilterList*/
bool ClearFilterList(List* list)
{
	int c = 0;
	int totalinlist;
	
	if (list->empty())//check FilterList empty
	{
		cout << "\nThe FilterList was empty, nothing to clear\n";
		return false;
	}
	
	totalinlist = list->size();
	
	for (int i = totalinlist; list->count>0 ; i--)//remove all records in FilterList
	{
		if (list->remove(i))
		{
			c++;
		}
		else {
			cout<<"\n\nFailed to delete the item in Filter List\n\n";
			return false;
		}	
	}

		cout << "\n\nAll the student record in FilterList have been removed\n\n";
		cout << "Total "<< c <<" records have been removed\n\n";
		return true;
	
	
}