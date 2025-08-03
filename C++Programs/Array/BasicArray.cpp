#include <iostream>

/*Function to print elements of an array*/
void printArr(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        //std::cout << *(arr+i) << " ";
        std::cout << arr[i] << " ";
    }
}


// minElemArr function to return the smallest element in the array
int minElemArr(int arr[], int n)
{
    int min = arr[0];
    for(int i=1; i<n; i++)
    {
        if(arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

// minElemArr function to return the smallest element in the array
int maxElemArr(int arr[], int n)
{
    int max = arr[0];
    for(int i=1; i<n; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// reverseArr function to reverse element in an array using two pointer
void reverseArr(int arr[], int n)
{
    int start = 0;
    int end = n-1;
    while(start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}


// reverseArr function to reverse element in an array using extra array
void reverseArrBrute(int arr[], int n)
{
    int temp[n];
    int size = n-1;
    for(int i= size; i >=0; i--)
    {
        temp[size-i] = arr[i];
    }
    printArr(temp, size+1);
}

// secondLarge function to return second large element 
void secondLarge(int arr[], int n)
{
    //{10,2,9,4,6,20}
    int max = 0;
    int secondmax = 0;
    for(int i=0; i< n; i++)
    {
        if(arr[i] > max)
        {
            secondmax = max;
            max = arr[i];   
        }
        //else if(arr[i] > secondmax && arr[i] < max)
        else if(arr[i] > secondmax && arr[i] != max)
        {
            secondmax = arr[i];
        }
    }
    std::cout << "Largest Element is : " << max << std::endl;
    std::cout << "Second Largest Element is : " << secondmax << std::endl;
}

// secondSmall function to return second small element 
void secondSmall(int arr[], int n)
{
    int small = arr[0];
    int secondSmall = 0;
    for(int i=1; i< n; i++)
    {
        if(arr[i] < small)
        {
            secondSmall = small;
            small = arr[i];   
        }
        else if(arr[i] < secondSmall && arr[i] > small)
        //else if(arr[i] < secondSmall && arr[i] != small)
        {
            secondSmall = arr[i];
        }
    }
    std::cout << "Smallest Element is : " << small << std::endl;
    std::cout << "Second Samllest Element is : " << secondSmall << std::endl;
}

int main()
{
    // int arr[] ={10,988,33,40,5,90};
    // int size = sizeof(arr)/sizeof(arr[0]);
    // printArr(arr,size);
    // std::cout << "Array operation" << std::endl;
    // std::cout << "Min element is: " << minElemArr(arr, size) << std::endl;
    // std::cout << "Min element is: " << maxElemArr(arr, size) << std::endl;
    // std::cout << "After reversing array " << std::endl;
    // reverseArrBrute(arr, size);
    // function to call reverseArr 
    //reverseArr(arr, size);
/*
    int intArr[5] ={1,2,3,4,5};
    // deferencing the intArr will print the firt element of the array
    std::cout << "*intArr: " << *intArr << std::endl;

    int* ptr = intArr;
    ptr++;
    std::cout << "*ptr: " << *ptr << std::endl;

    // Creating array using dynamically memory 
    int* dptr = new int[5];
    if(dptr)
    {
        for(int i=0; i<5; i++)
        {
            *(dptr+i) = (i+1)*2;
            //dptr++;
        }
    }
    for(int i=0; i<5; i++)
    {
        std::cout << dptr[i] << " ";
    }

    std::cout << std::endl;
*/

    int numArr[] = {10,2,9,4,6,20};
    int size = sizeof(numArr)/sizeof(numArr[0]);
    secondLarge(numArr, size);
    secondSmall(numArr, size);

    return 0;
}