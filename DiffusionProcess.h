#include<iostream>

using namespace std;

typedef double Rate;
typedef double Time;
typedef double Value;

class DiffusionProcess{
	double x0_; //init value
public:
	DiffusionProcess(double x0): x0_(x0) {}	
	virtual ~DiffusionProcess(){}
	
	double x0() const{	
		return x0_;	
	}
	
	virtual double drift(Time t, Value x) const = 0;
	virtual double diffusion(Time t, Value x) const = 0;
	
	virtual double expectation(Time t0, Value x0, Time dt) const{
		return x0+drift(t0,x0)*dt;
	}
	
	virtual double variance(Time t0, Value x0, Time dt) const{
		double sigma = diffusion(t0,x0);
		return sigma*sigma*dt;
	}
  
}
