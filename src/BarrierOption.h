#include<vector>

class BarrierOption{
public:

  //constructor
  BarrierOption(
    int nInt_,
    double strike_,
    double spot_,
    double vol_,
    double r_,
    double expiry_,
    double barrier_
  );

  //destructor
  ~BarrierOption(){};

  //methods
  void generatePath();
  void printPath();
  double getBarrierPutPrice(int nReps);

  //members
  std::vector<double> thisPath;
  int nInt;
  double strike;
  double spot;
  double vol;
  double r;
  double expiry;
  double barrier;
};
