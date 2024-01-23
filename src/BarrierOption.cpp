#include<iostream>
#include<cmath>
#include"getOneGaussianByBoxMueller.h"
#include"BarrierOption.h"
using namespace std;

//definition of constructor
BarrierOption::BarrierOption(
  int nInt_,
  double strike_,
  double spot_,
  double vol_,
  double r_,
  double expiry_,
  double barrier_){
  nInt = nInt_;
  strike = strike_;
  spot = spot_;
  vol = vol_;
  r = r_;
  expiry = expiry_;
  barrier = barrier_;
  generatePath();
}

//method definition
void BarrierOption::generatePath(){
  double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
  double cumShocks = 0;
  thisPath.clear();

  for(int i = 0; i < nInt; i++){
    cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
    thisPath.push_back(spot * exp(cumShocks));
  }
}


//method definition
void BarrierOption::printPath(){
  for(int i = 0;  i < nInt; i++){
    std::cout << thisPath[i] << "\n";
  }
}


// z generatePath ostatni element

//method definition
double BarrierOption::getBarrierPutPrice(int nReps){

  double rollingSum = 0.0;
  double last_price;
  double max_price;

  for(int i = 0; i < nReps; i++){
    generatePath();
    // assign last price of the underlying (S_T)
    last_price = thisPath[thisPath.size()-1];

    // assign maximum value of the underlying on path (max(S_t))
    max_price = *std::max_element(thisPath.begin(), thisPath.end());

    // 1. Check if S_t > barrier level
    bool barrierActivated = (max_price > barrier);

    // 2. Payoff calculation if the barrier is crossed & strike > last_price
    if (barrierActivated) {
      rollingSum += (strike > last_price) ? (strike - last_price) : 0;
    }
  }

  return exp(-r*expiry)*rollingSum/double(nReps);

}


