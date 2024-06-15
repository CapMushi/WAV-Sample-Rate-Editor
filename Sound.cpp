#include <iostream>
#include "wavfile.h"
using namespace std;

void allocateArray(unsigned char *& arr, int size)
{
	arr = new unsigned char[size];
}

void deallocateArray(unsigned char*& arr)
{
	delete[]arr;
	arr = NULL;
}

void printArray(unsigned char* arr, int size)
{
	cout << endl;
	for (int i = 0;i < size;i++)
	{
		cout << "Value at index " << i << "= " << *(arr + i) << endl;
	}
}

unsigned char* doubleArray(unsigned char* orgarr, int size1, int& s2)
{
	s2 = (2 * size1);//size of second array
	unsigned char* newarr;int key, index = 0, addi = 0;
	allocateArray(newarr, s2);
	for (int i = 0;i < size1;i++)
	{
		key = *(orgarr + i);
		for (int j = i;(*(orgarr + j) == key) && (j < s2);j++)
		{
			addi++;
		}
		i = i + addi - 1;                //-1 as i also incremented be 1 in loop
		addi = 2 * addi;

		for (int j = 0;j < addi;j++)
		{
			newarr[index] = key;
			index++;
		}
		addi = 0;
	}
	return newarr;
}

unsigned char* shrinkArray(unsigned char* arr, int size, int& s2)
{
	if (size % 2 == 0)
		s2 = size / 2;
	else
		s2 = size / 2 + 1;
	unsigned char* newarr2;
	allocateArray(newarr2, s2);
	int index = 0;
	for (int i = 0;i < size;i = i + 2)             //crossing one element
	{
		newarr2[index] = *(arr + i);
		index++;
	}
	return newarr2;
}
unsigned char* makecopy(unsigned char* arr, int size, int& s2)
{
	s2 = size;
	unsigned char* newarr2;
	allocateArray(newarr2, s2);
	for (int i = 0;i < size;i++)
	{
		newarr2[i] = *(arr + i);
	}
	return newarr2;
}

void FillWithMean(unsigned char in[], unsigned char out[], int size, int N)
{
	float tno, sum;
	for (int i = 0;i < size;i++)
	{
		tno = 0;sum = 0;
		for (int j = i;(j >= i - N) && (j >= 0);j--)
		{
			tno++;
			sum = sum + in[j];
		}
		for (int j = i + 1;(j <= i + N) && (j < size);j++)
		{
			tno++;
			sum = sum + in[j];
		}
		out[i] = sum / tno;

	}
}

unsigned char* CombineArray(unsigned char* arr1, unsigned char* arr2, int& s3)
{
	int s1 = 0, s2 = 0;
	for (int i = 0;*(arr1 + i) != 0;i++)
		s1++;
	for (int i = 0;*(arr2 + i) != 0;i++)
		s2++;
	s3 = s2 + s1;
	unsigned char* newarr3;
	allocateArray(newarr3, s3);
	int index1 = 0, index2 = 0, i = 0; //i for general counting which array element should be stored
	while ((*(arr1 + index1) != 0) && (*(arr1 + index2) != 0))
	{
		if (i % 2 == 0)
		{
			*(newarr3 + i) = *(arr1 + index1);
			index1++;
		}
		else
		{
			*(newarr3 + i) = *(arr2 + index2);
			index2++;
		}
		i++;
	}
	while (*(arr1 + index1) != 0)               //only one of them will work
	{
		*(newarr3 + i) = *(arr1 + index1);
		index1++;
    }
	while (*(arr2 + index2) != 0)
	{
		*(newarr3 + i) = *(arr2 + index2);
		index2++;
	}
	return newarr3;
}



void playfile(char* str) {
	if (playWavFile(str) == 0)
		cout << "Error: File not found!" << endl;
}



//Sample function for reading and storing sound data
unsigned char * read_data(char* str, int &size, int &sampleRate) {
	unsigned char* ptr = new unsigned char[size];
	readWavFile(str, ptr, size, sampleRate);

	return ptr;
	
}

void upSampleAudio(unsigned char *old, int size, int sampleRate)
{
	int newsize = 0;
	cout << "doubling array\n";
	unsigned char* n = doubleArray(old, size, newsize);
	cout << "doubled array\n";
	char name[50] = "up.wav";
	writeWavFile(name, n, newsize, sampleRate);
	cout << "wrote array\n";
	deallocateArray(n);

}
void downSampleAudio(unsigned char* old, int size, int sampleRate)
{
	int newsize = 0;
	cout << "halfing array\n";
	unsigned char* n = shrinkArray(old, size, newsize);
	cout << "halved array\n";
	char name[50] = "down.wav";
	writeWavFile(name, n, newsize, sampleRate);
	cout << "wrote array\n";
	deallocateArray(n);

}

void movingAverageFilter(unsigned char* old, int size, int sampleRate)
{
	int newsize = 0;
	unsigned char* n = makecopy(old, size, newsize);
	FillWithMean(old, n, size, 2);                             // you can change n right now it is 2 tested with all values
	cout << "Filling with mean\n";
	char name[50] = "copy.wav";
	writeWavFile(name, n, newsize, sampleRate);
	cout << "wrote array\n";
	deallocateArray(n);

}


void mergeArray(unsigned char* old1,unsigned char* old2, int sampleRate1, int sampleRate2)
{
	int newsize = 0;
	unsigned char* n = CombineArray(old1, old2, newsize);
	char name1[50] = "combine1.wav";
	cout << "files combined\n";
	writeWavFile(name1, n, newsize, sampleRate1);
	char name2[50] = "combine2.wav";
	cout << "wrote array with first sample rate \n";
	writeWavFile(name2, n, newsize, sampleRate2);
	cout << "wrote array with second sample rate \n";
	deallocateArray(n);

}



int main(){
	char str1[50] = "",str2[50]="";int option = 0, size1 = 1000000, size2 = 1000000, sampleRate1 = 0, sampleRate2 = 0;
	unsigned char* p1=NULL;unsigned char* p2=NULL;
	cout << "ENTER FILE NAME: " << endl;
	cin >> str1;
	p1 = read_data(str1, size1, sampleRate1);
	bool flag = true;
	while (flag) {
		cout << "ENTER 1 TO PLAY."<<endl;
		cout << "ENTER 2 TO DOUBLE THE SAMPLE RATE OF FILE." << endl;
		cout << "ENTER 3 TO REDUCE THE SAMPLE RATE OF FILE." << endl;
		cout << "ENTER 4 TO APPLY AVERAGE FILTER TO FILE." << endl;
		cout << "ENTER 5 MERGE AUDIO FILES." << endl;
		cout << "ENTER ANY OTHER NUMBER TO EXIT PROGRAMME." << endl;
		cin >> option;
		if (option == 1)
		{
			cout << "ENTER FILE NAME: " << endl;
			cin >> str1;
			if (strcmp(str1, "exit") != 0)
			{
				playfile(str1);
			}	
			
		}
		else if (option == 2)
		{
			upSampleAudio(p1, size1, sampleRate1);


		}
		else if (option == 3)
		{
			downSampleAudio(p1, size1, sampleRate1);

		}
		else if (option == 4)
		{
			movingAverageFilter(p1, size1, sampleRate1);

		}
		else if (option == 5)
		{
			cout << "ENTER SECOND FILE NAME: " << endl;
			cin >> str2;
			int size2 = 1000000, sampleRate2 = 0;
			p2 = read_data(str2, size2, sampleRate2);
			mergeArray(p1, p2, sampleRate1, sampleRate2);
			deallocateArray(p2);

		}
		
		else
		{
			deallocateArray(p1);
			flag = false;
		}
		
	}

	return 0;
}