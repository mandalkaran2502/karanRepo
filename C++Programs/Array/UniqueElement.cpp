#include <iostream>

void findUniqueElement(int arr[], int n)
{
    int ans;
    for(int i=0; i<n; i++)
    {
        ans ^= arr[i];
    }
    std::cout << "Unique Element : " << ans << std::endl;

}

int main()
{
    int arr[] = {10,20,20,30,40,10,40};
    int size = sizeof(arr)/sizeof(arr[0]);
    findUniqueElement(arr,size);
    return 0;
}