#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>

struct movie
{
    std::string title;
    int rating;
};

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

void printmovies(std::vector<movie> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << "Movie: " << vec[i].title << ", Rating: " << vec[i].rating << std::endl;
    }
}

//quicksort
void quicksort(std::vector<movie> &arr, int first, int last) //int arr[]
{
    if (first < last)
    {
        int pivot = arr[last].rating;
        int i = first;
        int j = first - 1;
        while (i < last)
        {
            
            if (arr[i].rating <= pivot)
            {
                j++;
                std::swap(arr[i], arr[j]);
            }
            i++;
        }
        j++;
        std::swap(arr[j], arr[last]);
        
        quicksort(arr, first, j-1);
        quicksort(arr, j+1, last);
    }   
}


//mergesort
void merge(std::vector<movie>& vec, int left, int mid, int right)
{
    //helper vectors (left and right)
    std::vector<movie> lvec;
    std::vector<movie> rvec;

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
            if (lvec[lcount].rating < rvec[rcount].rating)
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

void mergesort(std::vector<movie> &vec, int first, int last)
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
void bucketsort(std::vector<movie> & vec, int n)
{
    std::vector<std::vector<movie>> buckets(n+1);
    int max_value = 10;
    int bucket_index;

    //put all data to different buckets
    for (int i = 0; i < vec.size(); i++)
    {
        bucket_index = vec[i].rating * n / max_value;
        buckets[bucket_index].push_back(vec[i]);
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


void writefile(std::string path, std::vector<movie> vec)
{
    std::ofstream file;
    file.open(path);

    for (int i = 0; i < vec.size(); i++)
    {
        file << vec[i].title << ',' << vec[i].rating << std::endl;
    }

}

void readfile(std::string path, std::vector<movie> & movie_list)
{
    std::ifstream file;
    file.open(path);

    std::string row;
    std::string cell;
    movie m;

    std::string junk; //read id here    

    int i = 0; //movies iterator
    int a = 0;
    std::getline(file, junk);


    while (file.good() && a < 100) //&& a < 10000
    {
        //get column names
        std::getline(file, row);

        //make stream from string
        std::stringstream ss;
        ss.str(row);

        //junk for row id
        std::getline(ss, junk, ','); 

        // get movie name
        std::getline(ss, cell, ',');

        if (cell.empty()) {
            continue; // skip line if movie name is missing
        }
        m.title = cell;

        // get rating
        std::getline(ss, cell, ',');
        if (cell.empty()) {
            continue; // skip line if rating is missing
        }
        while (cell.size() > 2)
        {
            m.title = m.title + "," + cell;
            std::getline(ss, cell, ',');
        }
        int temp;
        try {
            temp = std::stoi(cell);
        }
        catch (const std::invalid_argument&) {

            continue;
            a++;
        }
        m.rating = std::stoi(cell);

        movie_list.push_back(m);

        a++;
    }
}


int main()
{
    std::vector<movie> movie_list;

    readfile("projekt2_dane.csv", movie_list);
    
    
    printmovies(movie_list);

    auto start = std::chrono::high_resolution_clock::now();

    //quicksort(movie_list, 0, movie_list.size()-1);
    //mergesort(movie_list, 0, movie_list.size()-1);
    //bucketsort(movie_list, 10);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    printmovies(movie_list);

    //writefile("test.csv", movie_list);
    
}