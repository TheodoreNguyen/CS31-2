//
//  main.cpp
//

#include <iostream>
#include <cmath>
#include <iomanip>
//DO NOT INCLUDE ANYTHING ELSE!!
using namespace std;

typedef double DataType;//Alias for double type
typedef unsigned int UIntType;//Alias for unsigned int type

class DataVector
{
private:
	DataType *m_data;//Pointer to dynamically allocated memory that holds all items
	UIntType m_size;//Size of the m_data array

public:

	DataVector()
	{
		m_data = new DataType[10];

		for (int i = 0; i < 10; i++)
		{
			m_data[i] = 0;
		}

		m_size = 10;
	}

	DataVector(UIntType initSize, DataType initValue)

	{
		m_data = new DataType[initSize];
		for (UIntType i = 0; i < initSize; i++)
		{
			m_data[i] = initValue;
		}
		m_size = initSize;
	}

	~DataVector()
	{
		delete [] m_data;
		m_data = NULL;
	}

	UIntType GetSize()
	{
		return m_size;
	}

	void Reserve(UIntType newSize)
	{
		DataType *newptr = new DataType[newSize];
		for (UIntType i = 0; i < newSize && i < m_size; i++)
			newptr[i] = m_data[i];
		delete [] m_data;
		m_data = newptr;
		m_size = newSize;
	}

	DataType GetItemAt(UIntType index)
	{
		return m_data[index];
	}

	void SetItemAt(UIntType index, DataType val)
	{
		m_data[index] = val;
	}


	DataType GetSum()
	{
		double sum = 0;
		for (int i = 0; i != m_size; i++)
			sum += m_data[i];
		return sum;
	}

	void PrintItems()
	{
		for (UIntType i = 0; i < m_size; i++)
		{
			cout << m_data[i] << " ";
		}
		cout << endl;
	}
};

class GradeManager
{
private:
	DataVector *m_student;//m_student[0], m_student[1], etc correspond to sID 0, 1, etc respectively
	UIntType m_nStudents;//Number of students

public:
	GradeManager(UIntType nStudents, UIntType nHWs)
	{
		m_student = new DataVector[nStudents];
		DataVector *traverser = m_student;
		for (int i = 0; i != nStudents; i++)
		{
			traverser->Reserve(nHWs);
			traverser++;
		}
		m_nStudents = nStudents;
	}

	~GradeManager()
	{
		delete[] m_student;
		m_student = NULL;
	}

	UIntType GetClassSize()
	{
		return m_nStudents;
	}

	UIntType GetHWCount()
	{
		return m_student[0].GetSize();
	}

	void SetGrade(UIntType sID, UIntType hwID, DataType val)
	{
		m_student[sID].SetItemAt(hwID, val);
	}

	DataType GetGrade(UIntType sID, UIntType hwID)
	{
		return m_student[sID].GetItemAt(hwID);
	}

	DataType GetTotalScoreForStudent(UIntType sID)
	{
		return m_student[sID].GetSum();
	}

	DataType GetTotalScoreForStudentWithDrop2Least(UIntType sID)
	{
		DataType priorTotal = GetTotalScoreForStudent(sID);
		DataType firstSmall = GetGrade(sID, 0);
		DataType largest = GetGrade(sID, 0);
		int pos1 = 0;
		for (int i = 1; i != GetHWCount(); i++)
			if (firstSmall > GetGrade(sID, i))
			{
				firstSmall = GetGrade(sID, i);
				pos1 = i;
			}
		
		for (int i = 1; i != GetHWCount(); i++)
			if (largest < GetGrade(sID, i))
			{
				largest = GetGrade(sID, i);
			}

		DataType secondSmall = largest + 1;
		for (int i = 0; i != GetHWCount(); i++)
			if (secondSmall > GetGrade(sID, i) && i != pos1)
				secondSmall = GetGrade(sID, i);

		return priorTotal - (firstSmall + secondSmall);
	}

	UIntType GetBestStudent()
	{
		UIntType posBestStudent = 0;
		for (int i = 1; i != m_nStudents; i++)
		{
			if (GetTotalScoreForStudentWithDrop2Least(posBestStudent) < GetTotalScoreForStudentWithDrop2Least(i))
				posBestStudent = i;
		}
		return posBestStudent;
	}

	UIntType GetNumStudentsInRange(DataType low, DataType high)
	{
		UIntType inrange = 0;
		for (int i = 0; i != m_nStudents; i++)
		if (GetTotalScoreForStudentWithDrop2Least(i) >= low && GetTotalScoreForStudentWithDrop2Least(i) < high)
			inrange++;
		return inrange;
	}

	DataType GetClassAverage()
	{
		DataType classtotal = 0;
		for (int i = 0; i != m_nStudents; i++)
			classtotal += GetTotalScoreForStudentWithDrop2Least(i);
		return classtotal/m_nStudents;
	}

	DataType GetClassSTD()
	{
		DataType STD;
		DataType preDivideRootTotal = 0;
		for (int i = 0; i != m_nStudents; i++)
			preDivideRootTotal += pow((GetTotalScoreForStudentWithDrop2Least(i) - GetClassAverage()), 2);
		STD = sqrt(preDivideRootTotal / m_nStudents);
		return STD;
	}

	void PrintGrades()
	{
		for (int i = 0; i != m_nStudents; i++)
		{
			m_student[i].PrintItems();
		}
	}
};

//---------------------------------------------------------------------------------------------------------------------
// IT IS RECOMMENDED NOT TO MODIFY ANYTHING BEYOND THIS POINT!!
// WARNING - ENTER AT YOUR OWN RISK!
// DO NOT REMOVE THE BLOCK_START and BLOCK_END TAGS ESPECIALLY!
//---------------------------------------------------------------------------------------------------------------------

//BLOCK_START

void CheckMemory();
void TestDataVector();
void TestGradeManager();

int main()
{
	cout << std::fixed << setprecision(2); //Setting cout precision for float/double values to be 2
	TestDataVector();
	TestGradeManager();
	return 0;
}

void TestDataVector()
{
	//Test 1
	{
		cout << "DataTest 1\n";
		DataVector d1;
		d1.PrintItems();
	}
	CheckMemory();

	//Test 2
	{
		cout << "\nDataTest 2\n";
		DataVector d1(14, 3.56);
		d1.PrintItems();
	}
	CheckMemory();

	//Test 3
	{
		cout << "\nDataTest 3\n";
		DataVector d1(130, 3.56);
		cout << d1.GetSize() << endl;
	}
	CheckMemory();

	//Test 4
	{
		cout << "\nDataTest 4\n";
		DataVector d1(13, 3.56);
		d1.Reserve(17);
		cout << d1.GetSize() << endl;
		d1.Reserve(5);
		cout << d1.GetSize() << endl;
		d1.PrintItems();
	}
	CheckMemory();

	//Test 5
	{
		cout << "\nDataTest 5\n";
		DataVector d1(13, 3.56);
		d1.Reserve(15);
		d1.SetItemAt(13, 3.99);
		d1.SetItemAt(14, 5.66);
		d1.SetItemAt(5, 1.11);
		d1.PrintItems();
	}
	CheckMemory();

	//Test 6
	{
		cout << "\nDataTest 6\n";
		DataVector d1(23, 3.5);
		d1.SetItemAt(22, 5);
		d1.SetItemAt(10, d1.GetItemAt(22) + 5);
		cout << d1.GetSum() << endl;
	}
	CheckMemory();
}

void TestGradeManager()
{
	//Test 1
	{
		cout << "\nGradeTest 1\n";
		GradeManager gm(10, 9);
		cout << gm.GetClassSize() << " " << gm.GetHWCount() << endl;
	}
	CheckMemory();

	//Test 2
	{
		cout << "\nGradeTest 2\n";
		GradeManager gm(10, 9);
		gm.PrintGrades();
	}
	CheckMemory();

	//Test 3
	{
		cout << "\nGradeTest 3\n";
		DataType student[5][5] = { { 67., 34., 56., 64., 87. },//student 0
		{ 78., 66., 91., 79., 90. },  //student 1
		{ 45., 59., 91., 99., 100. }, //student 2
		{ 70., 73., 54., 89., 33. },  //student 3
		{ 89., 81., 67., 95., 98. } }; //student 4
		GradeManager gm(5, 5);
		for (UIntType s = 0; s < 5; ++s) {
			for (UIntType h = 0; h < 5; ++h) {
				gm.SetGrade(s, h, student[s][h]);
			}
		}
		gm.PrintGrades();
	}
	CheckMemory();

	//Test 4
	{
		cout << "\nGradeTest 4\n";
		DataType student[5][5] = { { 67., 34., 56., 64., 87. },//student 0
		{ 78., 66., 91., 79., 90. },  //student 1
		{ 45., 59., 91., 99., 100. }, //student 2
		{ 70., 73., 54., 89., 33. },  //student 3
		{ 89., 81., 67., 95., 98. } }; //student 4
		GradeManager gm(5, 5);
		for (UIntType s = 0; s < 5; ++s) {
			for (UIntType h = 0; h < 5; ++h) {
				gm.SetGrade(s, h, student[s][h]);
			}
		}
		for (UIntType s = 0; s < 5; ++s) {
			for (UIntType h = 0; h < 5; ++h) {
				cout << gm.GetGrade(s, h) << " ";
			}
			cout << endl;
		}
	}

	//Test 5
	{
		cout << "\nGradeTest 5\n";
		DataType student[5][5] = { { 67., 34., 56., 64., 87. },  //student 0
		{ 78., 66., 91., 79., 90. },  //student 1
		{ 45., 59., 91., 99., 100. }, //student 2
		{ 70., 73., 54., 89., 33. },  //student 3
		{ 89., 81., 67., 95., 98. } }; //student 4
		GradeManager gm(5, 5);
		for (UIntType s = 0; s < 5; ++s) {
			for (UIntType h = 0; h < 5; ++h) {
				gm.SetGrade(s, h, student[s][h]);
			}
		}

		for (UIntType s = 0; s < 5; ++s) {
			cout << gm.GetTotalScoreForStudent(s) << " " << gm.GetTotalScoreForStudentWithDrop2Least(s) << endl;
		}
		cout << gm.GetBestStudent() << endl;
	}
	CheckMemory();

	//Test 6
	{
		cout << "\nGradeTest 6\n";
		DataType student[5][5] = { { 37., 34., 26., 24., 57. },  //student 0
		{ 78., 66., 91., 79., 90. },  //student 1
		{ 45., 59., 41., 59., 10. }, //student 2
		{ 70., 73., 54., 89., 33. },  //student 3
		{ 99., 98., 97., 95., 98. } }; //student 4
		GradeManager gm(5, 5);
		for (UIntType s = 0; s < 5; ++s) {
			for (UIntType h = 0; h < 5; ++h) {
				gm.SetGrade(s, h, student[s][h]);
			}
		}

		for (DataType r = 0; r < 300; r += 50) {
			cout << "[" << r << "," << r + 50 << "] - " << gm.GetNumStudentsInRange(r, r + 50) << endl;
		}
	}
	CheckMemory();

	//Test 7
	{
		cout << "\nGradeTest 7\n";
		DataType student[6][5] = { { 67., 34., 56., 64., 87. },  //student 0
		{ 78., 66., 81., 79., 80. },  //student 1
		{ 45., 59., 91.7, 99., 78. }, //student 2
		{ 70., 73., 54., 89.5, 33. },  //student 3
		{ 89., 81., 67., 95., 98. },  //student 4
		{ 69., 80., 57., 92., 71.5 } };  //student 5
		GradeManager gm(6, 5);
		for (UIntType s = 0; s < 6; ++s) {
			for (UIntType h = 0; h < 5; ++h) {
				gm.SetGrade(s, h, student[s][h]);
			}
		}
		cout << gm.GetBestStudent() << endl;
		cout << gm.GetClassAverage() << endl;
		cout << gm.GetClassSTD() << endl;
	}
	CheckMemory();
}

void CheckMemory()
{
	const UIntType AllocCount = 5;
	UIntType allocSizes[AllocCount] = { 1000, 200000, 30000, 25000, 30 };
	DataType *array[AllocCount];
	for (UIntType i = 0; i < AllocCount; ++i) {
		array[i] = new DataType[allocSizes[i]];
	}

	for (UIntType i = 0; i < AllocCount; ++i) {
		for (UIntType j = 0; j < allocSizes[i]; ++j) {
			array[i][j] = j;
		}
	}

	for (UIntType i = 0; i < AllocCount; ++i) {
		delete[]array[i];
	}
}

//BLOCK_END





