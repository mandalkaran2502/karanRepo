#include <iostream>


void findMissingElemntArrXor(int arr[], int n, int k)
{
    int Arrans=0,kxor=0;
    for(int i=0; i<n; i++)
    {
        Arrans ^= arr[i];
    }

    for(int i=1; i<=k; i++)
    {
        kxor= kxor^ i;
    }

    int result = Arrans^kxor;
    std::cout << "Missing element: " << result << std::endl;

}

/* In the function calculate the sum of the k natural number
 *  calculate the sum of the element of the array 
 * sumofnaturalnum - sumofarrayelement
*/
void findMissingElemntArr(int arr[], int n, int k)
{
    int sum =0;
    for(int i=0; i<n; i++)
    {
        sum = sum + arr[i];
    }
    int naturalsum = (k*(k+1))/2;

    int result = naturalsum -sum;
    std::cout << "Missing element in array: " << result << std::endl; 

}

int main()
{
    int arr[] = {1,2,3,4,6,7,8,9};
    int size = sizeof(arr)/sizeof(arr[0]);
    int k = 9;
    //findMissingElemntArr(arr,size,k);
    findMissingElemntArrXor(arr,size,k);

    return 0;
}