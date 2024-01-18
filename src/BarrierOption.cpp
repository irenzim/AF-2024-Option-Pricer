#include<iostream>
#include<cmath>
#include"getOneGaussianByBoxMueller.h"
#include"BarrierOption.h"


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
double BarrierOption::getArithmeticMean(){

  double runningSum = 0.0;

  for(int i = 0; i < nInt; i++){
    runningSum += thisPath[i];
  }

  return runningSum/double(nInt);
}


//method definition
double BarrierOption::getGeometricMean(){

  double runningSum = 0.0;

  for(int i = 0; i < nInt ; i++){
    runningSum += log(thisPath[i]);
  }

  return exp(runningSum/double(nInt));
}

//method definition
void BarrierOption::printPath(){

  for(int i = 0;  i < nInt; i++){

    std::cout << thisPath[i] << "\n";

  }

}


//method definition
double BarrierOption::getArithmeticBarrierPutPrice(int nReps){

  double rollingSum = 0.0;
  double thisMean = 0.0;

  for(int i = 0; i < nReps; i++){
    generatePath();
    thisMean=getArithmeticMean();

    // Check if S > barrier level
    bool barrierActivated = (spot>barrier);

    // Payoff calculation if the barrier is crossed
    if (barrierActivated) {
      rollingSum += (thisMean < strike) ? (strike - thisMean) : 0;
    }
  }

  return exp(-r*expiry)*rollingSum/double(nReps);

}



//method definition
double BarrierOption::getGeometricBarrierPutPrice(int nReps){

  double rollingSum = 0.0;
  double thisMean = 0.0;

  for(int i = 0; i < nReps; i++){
    generatePath();
    thisMean=getGeometricMean();

    // Check if S > barrier level
    bool barrierActivated = (spot>barrier);
    if (barrierActivated) {
      rollingSum += (thisMean < strike)? (strike - thisMean) : 0;
      }
  }

  return exp(-r*expiry)*rollingSum/double(nReps);

}

//overloaded operator ();
double BarrierOption::operator()(char char1, char char2, int nReps){
  if ((char1 == 'A') & (char2 =='P')) return getArithmeticBarrierPutPrice(nReps);
  else if ((char1 == 'G') & (char2 =='P')) return getGeometricBarrierPutPrice(nReps);
  else return -99;
}
