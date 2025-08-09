#include <iostream>
#include <unordered_set>
#include <vector>

void RemoveDuplicateElemnt(int arr[], int n)
{
    std::unordered_set<int> fset;
    std::vector<int> ansArr;
    for(int i=0; i<n; ++i)
    {
        if(fset.find(arr[i]) ==fset.end())
        {
            fset.insert(arr[i]);
            ansArr.push_back(arr[i]);
        }

    }
    // We can also print element of the set instead of ansArr
    for(int& it : ansArr)
    {
        std::cout << it << " " ;
    }
    std::cout << std::endl;

}

void RemoveDuplicateElemntOp(int arr[], int n)
{
    std::unordered_set<int> fset;
    int index =0;
    for(int i=0; i<n; ++i)
    {
        //If arr[i] is not already in the set, insert it and return true
        //is a compact way to check if an element was not already present in a std::unordered_set.
        //The insert() function returns a std::pair<iterator, bool>
        if(fset.insert(arr[i]).second)
        {
            arr[index++] = arr[i];
        }
    }

    for(int it =0; it< index; ++it)
    {
        std::cout << arr[it] << " " ;
    }
    std::cout << std::endl;
}



int main()
{
    int arr[] = {10,20,30,20,40,10,60,50,60};
    int size = sizeof(arr)/sizeof(arr[0]);
    RemoveDuplicateElemnt(arr,size);
    //RemoveDuplicateElemntOp(arr,size);

    return 0;
}