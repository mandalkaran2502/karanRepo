#include <iostream>

void printArr(int arr[], int n)
{
    for(int i=0; i<n; i++)
    {
        std::cout << arr[i] << " ";
    }
}

/*
void moveZeroEndBrute(int arr[], int n)
{
    int tempArr[n] = {0};
    int j=0;
    for(int i=0; i<n; i++)
    {
        if(arr[i] !=0)
        {
            tempArr[j] = arr[i];
            j++;
        }
    }
    printArr(tempArr, n);

}
*/

void moveZeroEnd(int arr[], int n)
{
    int j = -1;
    // finding the first zero in the array
    for(int i=0; i<n; i++)
    {
        if(arr[i] == 0)
        {
            j = i;
            break;
        }
    }
    // checking if is pointing to zero or not if zero is not found in the array return;
    if(j == -1)
    {
        std::cout << "Zero is not present in the Array" << std::endl;
        return;
    }
    for(int i =j+1; i<n; i++)
    {
        if(arr[i] != 0)
        {
            std::swap(arr[i], arr[j]);
            j++;
        }
    }
    printArr(arr,n);
}

int main()
{
    int numArr[] = {1,0,2,3,0,4,0,1};
    int size = sizeof(numArr)/sizeof(numArr[0]);
    //moveZeroEndBrute(numArr, size);
    moveZeroEnd(numArr, size);
    return 0;
}