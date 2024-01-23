#include <Rcpp.h>
#include<vector>
#include<ctime>
#include<cstdlib>
#include"BarrierOption.h"


using std::vector;
using std::cout;
using std::cin;
using namespace Rcpp;

// [[Rcpp::export]]
double getBarrierPutPrice(
  int nInt,
  double strike,
  double spot,
  double vol,
  double r,
  double expiry,
  double barrier,
  long int nReps
){

  // set the seed
  srand( time(NULL) );

  //create a new instance of class
  BarrierOption myBarrier(nInt, strike, spot, vol, r, expiry, barrier);

  // return price of the option
  return myBarrier.getBarrierPutPrice(nReps);
}
