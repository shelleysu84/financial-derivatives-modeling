#include <iostream>
using namespace std;

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
	
}


