#include<iostream>
#include<fstream>
using namespace std;

int M[2000][2000];
int solution[2000];
long long cost, n_cost;
int neighbor[2000];
int NumberOfCity;

void read_file(string f_name){
    fstream file(f_name, ios::in);
    if (!file.is_open()){
        cout<<"An error occured when reading file"<<endl;
        return;
    }
    file>>NumberOfCity;
    for (int i = 0; i < NumberOfCity; i++)
        for (int j = 0; j < NumberOfCity; j++)
            file>>M[i][j];
    file.close();
}

void init_individual(){
    for (int i = 0; i < NumberOfCity; i++)
        solution[i] = i;
    int j, tmp;
    for (int i = NumberOfCity-1; i > 0; i--){
        j = rand() % i;
        tmp = solution[i];
        solution[i] = solution[j];
        solution[j] = tmp;
    }
    cost = 0;
    for (int i = 1; i < NumberOfCity; i++)
        cost += M[solution[i-1]][solution[i]];
    cost += M[solution[NumberOfCity-1]][solution[0]];
}

bool update_solution(){
    n_cost = 0;
    for (int i = 1; i < NumberOfCity; i++)
        n_cost += M[neighbor[i-1]][neighbor[i]];

    n_cost += M[neighbor[NumberOfCity-1]][neighbor[0]];

    if (n_cost >= cost)
        return false;
    
    for (int i = 0; i < NumberOfCity; i++)
        solution[i] = neighbor[i];
    cost = n_cost;
    
    return true;
}

bool reverse(){

    int x = rand()%(NumberOfCity-1);
    int y = x + rand()%(NumberOfCity-x-1);
    for (int i = 0; i < x; i++)
        neighbor[i] = solution[i];
        
    for (int i = x; i <= y; i++)
        neighbor[i] = solution[y - i + x];
        
    for (int i = y+1; i < NumberOfCity; i++)
        neighbor[i] = solution[i];
    
    n_cost = 0;
    for (int i = 0; i < NumberOfCity; i++)
        n_cost += neighbor[i];
    
    return update_solution();
}
bool insert(){
    int u = rand()%(NumberOfCity-1);
    int v = rand()%(NumberOfCity-1);
    if (u < v){
        for (int i = 0; i < u; i++)
            neighbor[i] = solution[i];
        for (int i = u; i < v; i++)
            neighbor[i] = solution[i+1];
        neighbor[v] = solution[u];
        for (int i = v+1; i < NumberOfCity; i++)
            neighbor[i] = solution[i];
    }
    else{
        for (int i = 0; i < v; i++)
            neighbor[i] = solution[i];    
        neighbor[v] = solution[u];

        for (int i = v+1; i <= u; i++)
            neighbor[i] = solution[i-1];
        for (int i = u+1; i < NumberOfCity; i++)
            neighbor[i] = solution[i];
    }
    return update_solution();
}
bool cut(){
    int x = rand()%(NumberOfCity-1);
    int y = x + rand()%(NumberOfCity-x-1);
    int u = rand()%(NumberOfCity-1 - (y-x));
    
    for (int i = 0; i < NumberOfCity; i++)
        neighbor[u+i] = solution[x+i];
    int i = 0;
    int k = 0;
    while (i < u && k < NumberOfCity){
        if (k < x || k > y){
            neighbor[i] = solution[k];
            i++;
        }
        k++;
    }
    i = u+y-x+1;
    while (i < NumberOfCity && k < NumberOfCity){
        if (k < x || k > y){
            neighbor[i] = solution[k];
            i++;
        }
        k++;
    }

    return update_solution();
}
bool exchange(){
    int x = rand()%(NumberOfCity-1);
    int y = rand()%(NumberOfCity-1);
    for (int i = 0; i < NumberOfCity; i++)
        neighbor[i] = solution[i];
    int tmp = neighbor[x];
    neighbor[x] = neighbor[y];
    neighbor[y] = tmp;
    return update_solution();
}
void write_file(string name, long start, long stop){
    fstream file(name, ios::out | ios::app);
    if (!file.is_open()){
        cout<<"error in writing file!";
        return;
    }
    file<<"Time: "<<(stop - start)*1.0/CLOCKS_PER_SEC<<endl;
    file<<cost<<endl;
    for (int i = 0; i < NumberOfCity; i++)
        file<<solution[i]+1<<" ";
    file<<solution[0]+1;
    file<<endl<<"----------------------"<<endl;
    file.close();
}
void VNS(){
    init_individual();
    bool flag;
    int loop = 0;
    while (loop < 10000000){
        flag = (reverse() || cut() || insert() || exchange());
        loop = flag ? 0 : loop+1;
    }
}
int main(){

    string files[1] = {"tsp1.txt"};
    
    string outs[1] = {"out_1.txt"};
    for (int j = 0; j < 3; j++){
        read_file(files[j]);
        for (int i = 0; i < 2; i++){
            srand(time(NULL));
            long start = clock();
            VNS();
            long stop = clock();
            write_file(outs[j], start, stop);
        }
    }

    read_file("tsp1.txt");
    srand(time(NULL));
    long start = clock();
    VNS();
    long stop = clock();
    write_file("out_1a.txt", start, stop);
    
}