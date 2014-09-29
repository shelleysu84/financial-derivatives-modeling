#include <iostream>
using namespace std;

class Instrument : public Patterns::Observer, public Patterns::Observable {

	std::string isinCode_ , descrition_ ;
	mutable bool calculated;
	
protected:
	mutable bool isExpired;
	mutable double NPV;
	
	virtual void performCalculations() const = 0;
public:
	
	
}


