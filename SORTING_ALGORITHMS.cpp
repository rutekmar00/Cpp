#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cmath>
//#include <algorithm>

#define ROZMIAR 10000

using namespace std;

// przez scalanie, quicksort, introspektywne


void reverse(int arr[], int count){
   int temp;
   for(int i = 0; i < count/2; ++i){
      temp = arr[count-i-1];
      arr[count-i-1] = arr[i];
      arr[i] = temp;
    }
}


bool check_array(int array[], int high)
{
	for(int r= 0; r < high-1; r++)
		 {
			 if(array[r] > array[r+1])
			 {
				 cout << "zle: " << array[r] << endl;
				 cout << "zle: " << array[r+1] << endl;
				 cout << "indeks: " << r << endl;
			 return false;
			 }
		 }
	return true;
}

// Merge_sort

void Merge(int array[], int low, int mid, int high)
{
	int *array_tmp=new int [(high-low+1)];
	int i=low, j=mid+1 , n=0;

	while(i <= mid && j <= high)
	{
		if(array[j] < array[i])
		{
			array_tmp[n] = array[j];
			j++;
		}
		else
		{
			array_tmp[n] = array[i];
			i++;
		}
		n++;
	}
	if(i <= mid)
	{
		while(i <= mid)
		{
			array_tmp[n] = array[i];
			i++;
			n++;
		}
	}
	else
	{
		while(j <= high)
		{
			array_tmp[n] = array[j];
			j++;
			n++;
		}
	}

	for(i = 0; i <= high-low; i++)
		array[low+i] = array_tmp[i];

	delete [] array_tmp;

}
void Merge_sort(int array[], int low, int high)
{
	int mid;

	if(low != high)
	{
		mid = (low+high)/2;
		Merge_sort(array, low, mid);
		Merge_sort(array, mid+1, high);
		Merge(array, low, mid, high);
 	}
}


// Quicksort

int Partition(int array[], int low, int high)
{
int x = array[low];
int i = low, j = high, w;
while (true)
{
while (array[j] > x)
j--;
while (array[i] < x)
i++;
if (i < j)
{
w = array[i];
array[i] = array[j];
array[j] = w;
i++;
j--;
}
else
return j;
}
}

void Quicksort(int array[], int low, int high)
{
int q;
if (low < high)
{
q = Partition(array,low,high);
Quicksort(array, low, q);
Quicksort(array, q+1, high);
}
}


// Introsort

int partition(int data[], int left, int right) {
	int pivot = data[right];
	int temp;
	int i = left;

	for (int j = left; j < right; ++j)
	{
		if (data[j] <= pivot)
		{
			temp = data[j];
			data[j] = data[i];
			data[i] = temp;
			i++;
		}
	}

	data[right] = data[i];
	data[i] = pivot;

	return i;
}


void Heapify(int array[], int heapsize, int i) {
	int left = (i + 1) * 2 - 1;
	int right = (i + 1) * 2;
	int largest = 0;

	if (left < heapsize && array[left] > array[i])
		largest = left;
	else
		largest = i;

	if (right < heapsize && array[right] > array[largest])
		largest = right;

	if (largest != i)
	{
		int temp = array[i];
		array[i] = array[largest];
		array[largest] = temp;

		Heapify(array, heapsize, largest);
	}
}

void Heapsort(int array[], int count)
{
	int heapsize = count;

	for (int p = (heapsize - 1) / 2; p >= 0; --p)
		Heapify(array, heapsize, p);

	for (int i = count - 1; i > 0; --i)
	{
		int temp = array[i];
		array[i] = array[0];
		array[0] = temp;

		--heapsize;
		Heapify(array, heapsize, 0);
	}
}

void Insertionsort(int array[], int count)
{
	for (int i = 1; i < count; ++i)
	{
		int j = i;

		while ((j > 0))
		{
			if (array[j - 1] > array[j])
			{
				array[j - 1] ^= array[j];
				array[j] ^= array[j - 1];
				array[j - 1] ^= array[j];

				--j;
			}
			else
			{
				break;
			}
		}
	}
}

void Introsort(int array[], int count)
{
	int partitionsize = partition(array, 0, count - 1);

	if (partitionsize < 16)
	{
		Insertionsort(array, count);
	}
	else if (partitionsize >(2 * log(count)))
	{
		Heapsort(array, count);
	}
	else
	{
		Quicksort(array, 0, count - 1);
	}
}


int main()
{
	int  i, j, x;


	int *check = new int [100];

	double *tablica = new double [100];
	double *tablica1 = new double [100];
	double *tablica2 = new double [100];
	double *tablica3 = new double [100];
	double *tablica4 = new double [100];
	double *tablica5 = new double [100];
	double *tablica6 = new double [100];
	double *tablica7 = new double [100];

	ofstream NowyPlik;



	/********** MENU **********/


	 while(x>3 || x<1)
	    {
	    cout<<"*******************MENU********************"<<endl;
	    cout<<"1.Mergesort"<<endl;
	    cout<<"2.Quicksort"<<endl;
	    cout<<"3.Introsort"<<endl;
	    cout<<"Wybieram : ";
	    cin>>x;

	    system("cls");

	     }
	 srand(time(NULL));
	    switch (x)
	    {

	       case 1:

	    		   for (j = 0; j<100; j++)
	    		   {

	    			   int *array = new int [ROZMIAR];
	    			   for (i = 0; i < ROZMIAR; i++)
	    			   {
	    				   array[i] = rand() % ROZMIAR+1;
	    			   }
	    			   auto start = std::chrono::system_clock::now();
	    			   Merge_sort(array, 0, ROZMIAR-1);
	    			   auto end = std::chrono::system_clock::now();
	    			   check[j] = check_array(array, ROZMIAR);
	    			   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   	   tablica[j]=elapsed_seconds.count();
	    		   	   delete array;
	    		   }
	    		   cout << "0% sorted data - DONE" << endl;
	    		   for (j = 0; j<100; j++)
	    		   {

	    			   int *array = new int [ROZMIAR];
	    			   for (i = 0; i < ROZMIAR; i++)
	    			   {
	    				   array[i] = rand() % ROZMIAR+1;
	    			   }
	    			   Merge_sort(array, 0, 0.25*ROZMIAR-1);
	    			   auto start = std::chrono::system_clock::now();
	    			   Merge_sort(array, 0, ROZMIAR-1);
	    			   auto end = std::chrono::system_clock::now();
	    			   check[j] = check_array(array, ROZMIAR);
	    			   std::chrono::duration<double> elapsed_seconds = end-start;
	    			   tablica1[j]=elapsed_seconds.count();
	    			   delete array;
	    		   }
	    		   cout << "25% sorted data - DONE" << endl;
	    		   for (j = 0; j<100; j++)
	    		   {

	    			   int *array = new int [ROZMIAR];
	    			   for (i = 0; i < ROZMIAR; i++)
	    			   {
	    				   array[i] = rand() % ROZMIAR+1;
	    			   }
	    			   Merge_sort(array, 0, 0.5*ROZMIAR-1);
	    			   auto start = std::chrono::system_clock::now();
	    			   Merge_sort(array, 0, ROZMIAR-1);
	    			   auto end = std::chrono::system_clock::now();
	    			   check[j] = check_array(array, ROZMIAR);
	    			   std::chrono::duration<double> elapsed_seconds = end-start;
	    			   tablica2[j]=elapsed_seconds.count();
	    			   delete array;
	    		   }
	    		   cout << "50% sorted data - DONE" << endl;
	    		   for (j = 0; j<100; j++)
	    		   {

	    			   int *array = new int [ROZMIAR];
	    			   for (i = 0; i < ROZMIAR; i++)
	    			   {
	    				   array[i] = rand() % ROZMIAR+1;
	    			   }
	    			   Merge_sort(array, 0, 0.75*ROZMIAR-1);
	    			   auto start = std::chrono::system_clock::now();
	    			   Merge_sort(array, 0, ROZMIAR-1);
	    			   auto end = std::chrono::system_clock::now();
	    			   check[j] = check_array(array, ROZMIAR);
	    			   std::chrono::duration<double> elapsed_seconds = end-start;
	    			   tablica3[j]=elapsed_seconds.count();
	    			   delete array;
	    		   }
	    		   cout << "75% sorted data - DONE" << endl;
	    		   for (j = 0; j<100; j++)
	    		   {

	    			   int *array = new int [ROZMIAR];
	    			   for (i = 0; i < ROZMIAR; i++)
	    			   {
	    				   array[i] = rand() % ROZMIAR+1;
	    			   }
	    			   Merge_sort(array, 0, 0.95*ROZMIAR-1);
	    			   auto start = std::chrono::system_clock::now();
	    			   Merge_sort(array, 0, ROZMIAR-1);
	    			   auto end = std::chrono::system_clock::now();
	    			   check[j] = check_array(array, ROZMIAR);
	    			   std::chrono::duration<double> elapsed_seconds = end-start;
	    			   tablica4[j]=elapsed_seconds.count();
	    			   delete array;
	    		   }
	    		   cout << "95% sorted data - DONE" << endl;
	    		   for (j = 0; j<100; j++)
	    		   {

	    			   int *array = new int [ROZMIAR];
	    			   for (i = 0; i < ROZMIAR; i++)
	    			   {
	    				   array[i] = rand() % ROZMIAR+1;
	    			   }
	    			   Merge_sort(array, 0, 0.99*ROZMIAR-1);
	    			   auto start = std::chrono::system_clock::now();
	    			   Merge_sort(array, 0, ROZMIAR-1);
	    			   auto end = std::chrono::system_clock::now();
	    			   check[j] = check_array(array, ROZMIAR);
	    			   std::chrono::duration<double> elapsed_seconds = end-start;
	    			   tablica5[j]=elapsed_seconds.count();
	    			   delete array;
	    		   }
	    		   cout << "99% sorted data - DONE" << endl;
	    		   for (j = 0; j<100; j++)
	    		   {

	    			   int *array = new int [ROZMIAR];
	    			   for (i = 0; i < ROZMIAR; i++)
	    			   {
	    				   array[i] = rand() % ROZMIAR+1;
	    			   }
	    			   Merge_sort(array, 0, 0.997*ROZMIAR-1);
	    			   auto start = std::chrono::system_clock::now();
	    			   Merge_sort(array, 0, ROZMIAR-1);
	    			   auto end = std::chrono::system_clock::now();
	    			   check[j] = check_array(array, ROZMIAR);
	    			   std::chrono::duration<double> elapsed_seconds = end-start;
	    			   tablica6[j]=elapsed_seconds.count();
	    			   delete array;
	    		   }
	    		   cout << "99,7% sorted data - DONE" << endl;

	    		   for (j = 0; j<100; j++)
	    		   {

	    			   int *array = new int [ROZMIAR];
	    			   for (i = 0; i < ROZMIAR; i++)
	    			   {
	    				   array[i] = rand() % ROZMIAR+1;
	    			   }
	    			   Merge_sort(array, 0, ROZMIAR-1);
	    			   reverse(array, ROZMIAR);
	    			   auto start = std::chrono::system_clock::now();
	    			   Merge_sort(array, 0, ROZMIAR-1);
	    			   auto end = std::chrono::system_clock::now();
	    			   check[j] = check_array(array, ROZMIAR);
	    			   std::chrono::duration<double> elapsed_seconds = end-start;
	    			   tablica7[j]=elapsed_seconds.count();
	    			   delete array;
	    		   }
	    		   cout<<"Reversed sorted data - DONE"<<endl;

	    		   break;

	       case 2:

	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   auto start = std::chrono::system_clock::now();
	    		   Quicksort(array, 0, ROZMIAR-1);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout << "0% sorted data - DONE" << endl;
	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.25*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Quicksort(array, 0, ROZMIAR-1);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica1[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout << "25% sorted data - DONE" << endl;


	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.5*ROZMIAR-1);

	    		   auto start = std::chrono::system_clock::now();
	    		   Quicksort(array, 0, ROZMIAR-1);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica2[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout << "50% sorted data - DONE" << endl;



	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.75*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Quicksort(array, 0, ROZMIAR-1);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica3[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout << "75% sorted data - DONE" << endl;

	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.95*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Quicksort(array, 0, ROZMIAR-1);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica4[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }

	    	   cout << "95% sorted data - DONE" << endl;

	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.99*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Quicksort(array, 0, ROZMIAR-1);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica5[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout << "99% sorted data - DONE" << endl;


	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.997*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Quicksort(array, 0, ROZMIAR-1);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica6[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout << "99,7% sorted data - DONE" << endl;

	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, ROZMIAR-1);
	    		   reverse(array, ROZMIAR);
	    		   auto start = std::chrono::system_clock::now();
	    		   Quicksort(array, 0, ROZMIAR-1);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica7[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout<<"Reversed sorted data - DONE"<<endl;


	    	   break;


	       case 3:

	    	   for (j = 0; j<100; j++)
	    	   {
	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   auto start = std::chrono::system_clock::now();
	    		   Introsort(array, ROZMIAR);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout<<"0% sorted data - DONE"<<endl;

	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.25*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Introsort(array, ROZMIAR);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica1[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout<<"25% sorted data - DONE"<<endl;

	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.5*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Introsort(array, ROZMIAR);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica2[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout<<"50% sorted data - DONE"<<endl;

	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.75*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Introsort(array, ROZMIAR);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica3[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout<<"75% sorted data -DONE"<<endl;

	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.95*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Introsort(array, ROZMIAR);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica4[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }

	    	   cout<<"95% sorted data -DONE"<<endl;

	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.99*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Introsort(array, ROZMIAR);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica5[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout<<"99% sorted data -DONE"<<endl;


	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, 0.997*ROZMIAR-1);
	    		   auto start = std::chrono::system_clock::now();
	    		   Introsort(array, ROZMIAR);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica6[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout<<"99,7% sorted data -DONE"<<endl;

	    	   for (j = 0; j<100; j++)
	    	   {

	    		   int *array = new int [ROZMIAR];
	    		   for (i = 0; i < ROZMIAR; i++)
	    		   {
	    			   array[i] = rand() % ROZMIAR+1;
	    		   }
	    		   Quicksort(array, 0, ROZMIAR-1);
	    		   reverse(array, ROZMIAR);
	    		   auto start = std::chrono::system_clock::now();
	    		   Introsort(array, ROZMIAR);
	    		   auto end = std::chrono::system_clock::now();
	    		   check[j] = check_array(array, ROZMIAR);
	    		   std::chrono::duration<double> elapsed_seconds = end-start;
	    		   tablica7[j]=elapsed_seconds.count();
	    		   delete array;
	    	   }
	    	   cout<<"Reverse sorted data -DONE"<<endl;


	    	   	   break;

	    }

	    	   system("PAUSE");

	    	   NowyPlik.open("F:\\plik.csv");

	    	   for(j = 0; j<100; j++)
	    	   {
	    		   NowyPlik<<tablica[j]<<endl;
	    	   }
	    	   NowyPlik<<"\n";
	    	   for(j = 0; j<100; j++)
	    	   {
	    		   NowyPlik<<tablica1[j]<<endl;
	    	   }

	    	   NowyPlik<<"\n";
	    	   for(j = 0; j<100; j++)
	    	   {
	    		   NowyPlik<<tablica2[j]<<endl;
	    	   }

	    	   NowyPlik<<"\n";
	    	   for(j = 0; j<100; j++)
	    	   {
	    		   NowyPlik<<tablica3[j]<<endl;
	    	   }

	    	   NowyPlik<<"\n";
	    	   for(j = 0; j<100; j++)
	    	   {
	    		   NowyPlik<<tablica4[j]<<endl;
	    	   }

	    	   NowyPlik<<"\n";
	    	   for(j = 0; j<100; j++)
	    	   {
	    		   NowyPlik<<tablica5[j]<<endl;
	    	   }

	    	   NowyPlik<<"\n";
	    	   for(j = 0; j<100; j++)
	    	   {
	    		   NowyPlik<<tablica6[j]<<endl;
	    	   }

	    	   NowyPlik<<"\n";

	    	   for(j = 0; j<100; j++)
	    	   {
	    		   NowyPlik<<tablica7[j]<<endl;
	    	   }


	    	   NowyPlik.close();

	    	   delete check;
	    	   delete tablica;
	    	   delete tablica1;
	    	   delete tablica2;
	    	   delete tablica3;
	    	   delete tablica4;
	    	   delete tablica5;
	    	   delete tablica6;
	    	   delete tablica7;
	    	   return 0;
}
