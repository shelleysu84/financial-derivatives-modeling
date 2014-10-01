/*
General Diffusion process : dX = drift * dT + sigma * dZ 
*/
#include<iostream>
#include<math>

using namespace std;

typedef double Rate;
typedef double Volatility;
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
	BlackScholesProcess (Rate rate, Volatility vol, Value s0 = 0.0) : DiffusionProcess(s0), rate_(rate), volatility_(vol) {}
	
	double dridt (Time t, Value x) const {
		return rate_ - 0.5*volatility_*volatility_;
	}
	
	double variance (Time t, Value x) const {
		return volatility_ ;
	}
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
	double diffusion (Time t, Value x) const {
		return volatility_;
	}
	
	double expectation (Time t0, Value x, Time dt) const {
		return x0 * exp(-speed_*dt);
	}

	double variance (Time t0, Value x, Time t) const {
		return 0.5*volatility_*volatility_/speed_*(1.0 - exp(-2.0*speed_*dt));
	}
};
