/*
General Diffusion process : dX = drift * dT + sigma * dZ 
*/
#include<iostream>

using namespace std;

typedef double Rate;
typedef double Vol;
typedef double Time;
typedef double Value;

class DiffusionProcess{
	double x0_; //init value
public:
	DiffusionProcess(double x0): x0_(x0) {}	
	virtual ~DiffusionProcess(){}
	
	double getValue() const{	
		return x0_;	
	}
	//define interface for drift part and stochastic process part
	virtual double drift(Time t, Value x) const = 0;
	virtual double diffusion(Time t, Value x) const = 0;
	
	//Ex = x0_ + drift value
	virtual double expectation(Time t0, Value x0, Time dt) const{
		return x0 + drift(t0,x0)*dt;
	}
	
	//Var x = sigma^2 * dt for diffusion process
	virtual double variance(Time t0, Value x0, Time dt) const{
		double sigma = diffusion(t0,x0);
		return sigma*sigma*dt;
	}
};

class BlackScholesProcess : public DiffusionProcess{
	Rate rate_ ;
	Volatility volatility_;

public:
	BlackScholesProcess (Rate rate, Volatility vol, ) 

};

class OrnsteinUlenbeckProcess: public DiffusionProcess{
	double speed_ ;
	Volatility volatility_;
public:
	OrnsteinUlenbeckProcess(double speed , Volatility vol, Value x0 = 0.0) :
	speed_(speed), volatility_(vol), DiffusionProcess(x0) {}
	
	double drift (Time t , Value x) const {
		return 0 - speed_*x; 
	}
	
}
