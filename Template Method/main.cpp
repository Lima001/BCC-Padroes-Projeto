#include <iostream>
#include <stdlib.h>
#include <time.h>

// Abstract Class
class Sorter {

    public:
        // Template Method
        virtual void sort(int* array, int size){
            quicksort(array,size);
        }

    protected:
        // Abstract primitive operation
        virtual bool compare(int a, int b) = 0;

    private:
        //Shared concrete operations - base for quicksort algorithm

        int partition(int* array, int start, int end){
            int pivot = *(array+start);
            
            *(array+start) = *(array+end);
            *(array+end) = pivot;
            
            int i=start, j=start;
            int temp;
            
            for (j; j<end; j++){
                
                if (compare(*(array+j), pivot)){
                    
                    temp = *(array+j);
                    *(array+j) = *(array+i);
                    *(array+i) = temp;

                    i++;
                }
            }

            *(array+end) = *(array+i);
            *(array+i) = pivot;

            return i;
        }

        void divide(int* array, int start, int end){
            if (start < end){
                int pos_pivot = partition(array, start, end);
                divide(array, start, pos_pivot-1);
                divide(array, pos_pivot+1, end);
            }
        }

        void quicksort(int* array, int size){
            divide(array, 0, size-1);
        }

};

// Concrete class
class AscendingSorter: public Sorter {
    public:
        // Concrete primitive operation
        bool compare(int a, int b){
            return (a < b);
        }
};

// Concrete class
class DescendingSorter: public Sorter {
    public:
        // Concrete primitive operation
        bool compare(int a, int b){
            return (a > b);
        }
};

// Class for testing the Template Method pattern
class TestSorter {

    public:

        void main(int n){
            
            // Creating array for sorting (and its copies - to avoid overwriting)
            int* array = new int[n];
            int* ascArray = new int[n];
            int* descArray = new int[n];
            
            // Generate random numbers and filling the base array
            fill(array,n);

            // Coping the base array to the ones that are going to be sorted
            copy(array,ascArray,n);
            copy(array,descArray,n);
            
            // Printing the arrays
            std::cout << "Base array: ";
            print(array,n);
            std::cout << "Ascending array (before sort): ";
            print(ascArray,n);
            std::cout << "Descending array (before sort): ";
            print(descArray,n);

            // Calling the concrete template method from each subclass
            ascSorter.sort(ascArray,n);
            descSorter.sort(descArray,n);

            // Printing sorted arrays - both are sorted as expected
            std::cout << "Ascending array (after sort): ";
            print(ascArray,n);
            std::cout << "Descending array (after sort): ";
            print(descArray,n);

            delete[] array;
            delete[] ascArray;
            delete[] descArray;
        }

    private:

        // Sort Subclasses - to call sort() method
        AscendingSorter ascSorter;
        DescendingSorter descSorter;

        // Auxiliar methods for array dealing
        
        void fill(int* array, int size, int max_value=1000){
            srand(time(NULL));

            for (int i=0; i<size; i++)
                *(array+i) = rand()%max_value + 1;
        }

        void print(int* array, int size){
            for (int i=0; i<size; i++)
                std::cout << *(array+i) << " ";
            
            std::cout << std::endl;
        }

        void copy(int* array, int* copyArray, int size){
            for (int i=0; i<size; i++)
                *(copyArray+i) = *(array+i);
        }

};

int main(){
    TestSorter t;
    t.main(15);
    return 0;
}