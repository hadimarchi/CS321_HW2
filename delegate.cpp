// delegate.cpp
// Author: Hal DiMarchi
// Source file for Exercise A, HW2
// For CS 321

#include <thread>
using std::thread;

#include <future>
using std::promise;
using std::future;

#include <typeinfo>

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <vector>
using std::vector;

#include "sa2a.h"
// sa2a

const int NUM_THREADS = 6;

// input for main.cpp
// takes in positive numbers and adds to vector until
// a zero or negative number is entered
// then returns the vector
vector<int> getNumbers(){
  vector<int> numbers{};
  int input = 1;
  while(input >= 1){
    cout<<"Enter a positive integer (or 0 to end input):";
    cin>>input;
    numbers.push_back(input);
  }
  numbers.pop_back();
  return numbers;
}

// runs sa2a and assigns input and result
// to the passed promise
void run(promise<vector<int>> &&p, int number){
  vector<int> rv = {number, sa2a(number)};
  p.set_value(rv);
}

// multithreaded use of sa2a
void sa2a_multithreader(){
  auto numbers = getNumbers();
  vector<thread> ts{};
  promise<vector<int>> ps;
  vector<decltype(ps.get_future())> psgets{};

  for(auto i = 0; i < std::min(NUM_THREADS, int(numbers.size())); i++){
    promise<vector<int>> p{};
    psgets.push_back(p.get_future());
    ts.push_back(thread(run, std::move(p), numbers.back()));
    numbers.pop_back();
  }

  while(ts.size() or numbers.size()){
    for(unsigned int i = 0; i < ts.size(); i++){
      if (ts[i].joinable()){
        ts[i].join();
        auto rv = psgets[i].get();
        cout<<"sa2a("<<rv[0]<<") = "<<rv[1]<<endl;
        if (numbers.size()){
          promise<vector<int>> p{};
          psgets[i] = p.get_future();
          ts[i] = thread(run, std::move(p), numbers.back());
          numbers.pop_back();
        }
        else{
          psgets.erase(psgets.begin() + i);
          ts.erase(ts.begin()+i);
        }
      }
    }
  }
  exit(0);
}


int main(){
sa2a_multithreader();
return 0;
}
