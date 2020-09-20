#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>

int twod_to_oned(int row, int col, int rowlen);
bool proc_num(std::vector<int>& v, int bi, int ei);
void rotate_anti_clock(std::vector<int>&v);
bool game_over(const std::vector<int>&v);
void print_grid(const std::vector<int>& v);
void random2(std::vector<int>& v);

int main(){
    
    std::string newgame = "yes";
    
while(newgame == "yes") {
    std::vector<int> vector;
    std::string filename;
    
    std::cout << "Welcome to 2048. Enter the initial configuration file name:" << std::endl;
    std::cin >> filename;
    
    std::ifstream infile;
    infile.open(filename.c_str());
    
    if(infile.is_open()){
        int number;
    
        while(infile >> number){
            vector.push_back(number);
        }
    }
    
    if(!infile.is_open()){
        std::cout << "Error, file not found, using default start configuration. Enjoy" << std::endl;
        int number[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2};
        vector.insert(vector.end(), number, number+16);;
    }
    
    print_grid(vector);
    int side = std::sqrt(vector.size());
    bool can_move;
 
 
    while(!game_over(vector)) {

        can_move = false;
        std::string move;
        std::cin >> move;
        
            if(move == "w") {
                rotate_anti_clock(vector);
                for(int i = 0; i < side; i++){
                    if(proc_num(vector,(i*side),((i+1)*side)) == true){
                        can_move = true; 
                    }
                }
                rotate_anti_clock(vector);
                rotate_anti_clock(vector);
                rotate_anti_clock(vector);
            }

            if(move == "a") {
                for(int i = 0; i < side; i++){
                    if(proc_num(vector,(i*side),((i+1)*side)) == true){
                        can_move = true;
                    }
                }
            }
            
            if(move == "d") {
                rotate_anti_clock(vector);
                rotate_anti_clock(vector);
                    for(int i = 0; i < side; i++){
                        if(proc_num(vector,(i*side),((i+1)*side)) == true){
                            can_move = true; 
                        }
                    }
                rotate_anti_clock(vector);
                rotate_anti_clock(vector);
            }
                    
            if(move == "s") {
                rotate_anti_clock(vector);
                rotate_anti_clock(vector);
                rotate_anti_clock(vector);
                for(int i = 0; i < side; i++){
                    if(proc_num(vector,(i*side),((i+1)*side)) == true){
                        can_move = true; 
                    }
                }
                rotate_anti_clock(vector);
            }
            
        std::cout << std::endl;
        
        if(can_move == true){
            random2(vector);
            print_grid(vector);
            std::cout << std::endl;
        }
    }
    
   std::cout << std::endl << "G A M E    O V E R" << std::endl;
    std::cout << std::endl << "Thank you for playing 2048 by Baptiste Provendier." << std::endl << "Ready to try again?" << std::endl << "yes OR no?" << std::endl;
    std::cin >> newgame;
    }
    std::cout << "I hope you enjoyed and see you next time!" << std::endl; 
    return 0;
}

int twod_to_oned(int row, int col, int rowlen){
    return row*rowlen+col;
}

bool proc_num(std::vector<int>& v, int bi, int ei) {
    std::vector<int> vin;
    for(int i = 0; i < v.size(); i++) {
    vin.push_back(v[i]);
    }
    
    for(int i = (ei-1); i > bi; i--){
        if(v[i-1] == 0) {
            v[i-1] = v[i];
            v[i] = 0;
            for(int j=i; j< (ei-1); j++) {
                v[j] = v[j+1];
                v[j+1] = 0;
            }
        }
    }
    
    for(int i = (bi+1); i < ei; i++){
        if(v[i-1] == v[i]) {
            v[i-1] = 2*v[i-1];
            v[i] = 0;
            for(int j=i; j< (ei-1); j++) {
                v[j] = v[j+1];
                v[j+1] = 0;
            }
        }
    }

    
    for(int i = 0; i < v.size(); i++) {
        if(vin[i] != v[i]) {
            return true;
        }
    }
            return false;
}


void rotate_anti_clock(std::vector<int>&v) {
    int side = std::sqrt(v.size());
    std::vector<int> vin;
    for(int i = 0; i < v.size(); i++) {
    vin.push_back(v[i]);
    }
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            v[twod_to_oned((3-j),i,side)] = vin[twod_to_oned(i,j,side)];
        }
    }
}
    


bool game_over(const std::vector<int>&v) {
    int side = std::sqrt(v.size());
    
    //check for zero
    for(int i=0; i < side; i++) {
        for(int j=0; j < side; j++) {
            if(v[twod_to_oned(i,j,side)] == 0) {
                return false;
            }
        }
    }
    
    //check for row
    for(int i=0; i < side; i++) {
        for(int j=0; j < (side-1); j++) {
            if(v[twod_to_oned(i,j,side)] == v[twod_to_oned(i,(j+1),side)]) {
                return false;
            }
        }
    }
    
    //check for column
    for(int i=0; i < (side-1); i++) {
        for(int j=0; j < side; j++) {
            if(v[twod_to_oned(i,j,side)] == v[twod_to_oned((i+1),j,side)]) {
                return false;
            }
        }
    }
return true;
}


void print_grid(const std::vector<int>& v) {
        
    int side = std::sqrt(v.size());

    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            std::cout << v[twod_to_oned(i,j,side)];
            
            int digits = 0;
            int number = v[twod_to_oned(i,j,side)];
            
                if(number == 0) { 
                    digits = 1;
                }
                
                while(number > 0) {
                    number = number/10;
                    digits++;
                }
                    
                for(int space = 0; space < (8 - digits); space ++) {
                    std::cout << " ";
                }
                
        }
        std::cout << std::endl;
    }
}

void random2(std::vector<int>& v) {
    int side = std::sqrt(v.size());
    //check for zero
    bool check = false;
    for(int i=0; i < side; i++) {
        for(int j=0; j < side; j++) {
            if(v[twod_to_oned(i,j,side)] == 0) {
                check = true;
            }
        }
    }
    
    if(check){
        srand(time(NULL));
        int random = rand() % (v.size()-1);
        while(v[random] != 0) {
            random = rand() % (v.size()-1);
        }
        v[random] = 2;
    }
}

