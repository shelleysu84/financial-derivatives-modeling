/**********************************************************************************
Abstract Instrument class
This class is purely abstract and defines the interface of concrete instruments
which will be derived from this one. It implements the Observable interface
**********************************************************************************/
#ifndef quantlib_instrument_h 
#define quantlib_instrument_h
#include "Observable.h"
#include <iostream>
using namespace std;
using namespace Quantlib;

class Instrument : public Patterns::Observer, public Patterns::Observable {

	std::string isinCode_ , descrition_ ;
	mutable bool calculated_;
	
protected:
	mutable bool isExpired_;
	mutable double NPV_;
	
	virtual void performCalculations() const = 0;
public:
	Instrument (const std::string& isinCode, const std::string& description) : NPV_(0.0), isExpired(false), calculated(false) {
	}
	
	virtual ~Instrument() {}
	
	inline std::string isinCode() const{
		return isinCode_;
	}
	
	inline double NPV() const{
		calculate();
		return isExpired_? 0.0 : NPV_;
	}
	inline std::string description() const{
		return descrition_ ;
	}
	
	bool isExpired() cosnt;
	
	void update();
	recalculate();
	
	inline void calculate() const{
		if(!calculated){
			performCalculations();
			calculated = true;
		}
	}

}
#endif