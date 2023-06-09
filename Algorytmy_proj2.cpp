#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//print funcs
void print(int* arr)
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

void printvec(std::vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << ' ';
    }
    std::cout << '\n';
}

void print2dvec(std::vector<std::vector<int>> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            std::cout << vec[i][j]<<' ';
        }
        std::cout << '\n';
    }
}


//quicksort
void swap(int* a, int* b) //addresses of array elements
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(std::vector<int> &arr, int first, int last) //int arr[]
{
    if (first < last)
    {
        int pivot = arr[last];
        int i = first;
        int j = first - 1;
        while (i < last)
        {
            
            if (arr[i] <= pivot)
            {
                j++;
                swap(&arr[i], &arr[j]);   
            }
            i++;
        }
        j++;
        swap(&arr[j], &arr[last]);
        
        quicksort(arr, first, j-1);
        quicksort(arr, j+1, last);
    }   
}


//mergesort
void merge(std::vector<int>& vec, int left, int mid, int right)
{
    //helper vectors (left and right)
    std::vector<int> lvec;
    std::vector<int> rvec;

    //fill left and right helpers
    for (int i = left; i <= mid; i++)
    {
        lvec.push_back(vec[i]);
    }
    for (int i = mid + 1; i <= right; i++)
    {
        rvec.push_back(vec[i]);
    }

    //counters
    int lcount = 0;
    int rcount = 0;

    for (int i = left; i <= right; i++)
    {
        if (lcount == lvec.size())
        {
            vec[i] = rvec[rcount];
            rcount++;
        }
        else if (rcount == rvec.size())
        {
            vec[i] = lvec[lcount];
            lcount++;
        }
        else
        {
            if (lvec[lcount] < rvec[rcount])
            {
                vec[i] = lvec[lcount];
                lcount++;
            }
            else
            {
                vec[i] = rvec[rcount];
                rcount++;
            }
        }
    }

    //delete vectors (free memory)
    lvec.clear();
    rvec.clear();
    lvec.shrink_to_fit();
    rvec.shrink_to_fit();
}

void mergesort(std::vector<int> &vec, int first, int last)
{
    int mid = ((first + last) / 2);

    if (first<last)
    {
        mergesort(vec, first, mid);
        mergesort(vec, mid + 1, last);
        merge(vec, first, mid, last);
    }
}


//bucketsort
int find_max(std::vector<int> vec)
{
    int max = vec[0];
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i]>max)
        {
            max = vec[i];
        }
    }
    return max;
}

void bucketsort(std::vector<int> & vec, int n)
{
    std::vector<std::vector<int>> buckets(n+1);
    int max_value = find_max(vec);
    int bucket_index;

    //put all data to different buckets
    for (int i = 0; i < vec.size(); i++)
    {
        bucket_index = vec[i] * n / max_value;
        buckets[bucket_index].push_back(vec[i]);
    }

    for (int i = 0; i < buckets.size(); i++)
    {
        quicksort(buckets[i], 0, buckets[i].size()-1);
    }

    vec.clear();

    for (int i = 0; i < buckets.size(); i++)
    {
        for (int j = 0; j < buckets[i].size(); j++)
        {
            vec.push_back(buckets[i][j]);
        }
    }
}


int main()
{
    //quicksort on array (need to change parameter in quicksort func)
    /*int arr[10] = {0,6,2,3,9,7,1,8,4,5};
    print(arr);
    quicksort(arr, 0, 9);
    print(arr);*/

    //example array
    std::vector<int> vec{ 0,6,2,3,9,7,1,8,4,5 };
    printvec(vec);

    quicksort(vec, 0, vec.size()-1);

    //mergesort(vec, 0, vec.size()-1);

    //bucketsort(vec, 10);


    printvec(vec);


    
}