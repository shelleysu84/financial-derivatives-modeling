#ifndef _call_option_h_
#define _call_option_h_

#include <vector>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <map>
#include <utility>
#include <set>
#include <list>
#include <fstream>
#include <iostream.h>
#include "Utility.h"
#include "Deviates.h"
#include "Handle.h"
#include "Argsandresults.h"
#include "PricingEngine.h"
#include "Instrument.h"
#include "NumericalMethod.h"
#include "Qldefines.h"
#include "Exercise.h"
#include "MonteCarlo.h"

#define max (a,b) (((a)>(b))?(a) : (b) )
using namespace std;
//using namespace Quantlib;

class Option : public Quantlib :: Instrument 
{
public :
	enum Exercise{
		European = 'E ', American = 'A '
	};
	enum Type{
		Call = 'C ', Put = 'P ', Straddle = 'S '
	};
	// default constructor
	Option (): price_(50.0), strike_(50.0), rate_(0.06), dividend_(0.0), T_(1), type_('C'), exercise_('E')	{}
	Option (double price, double strike , double vol , double rate , double div ,double T ,char type , char exercise );
	Option (const Quantlib :: handle <Quantlib::pricingEngine>& engine );
	virtual ~ Option() {}
	friend class OptionGreeks ;
	void setPricingEngine (const Quantlib::handle <Quantlib::pricingEngine>& engine ) ;
	virtual coid performEngine() const = 0 ;
	virtual setupEngine() const = 0;
	virtual double calculate () const = 0 ;
	Quantlib::handle<Quantlib ::pricingEngine> engine_ ;
	
	class OptionGreeks 
	{
	public :
		StatUtility util ;
		OptionGreeks () {}
		double calcVega		(double price , double strike ,double rate , double div , double vol ,double T , double t );
		double calcDelta	(double price , double strike ,double rate , double div , double vol ,double T , double t ,char type );
		double calcGamma	(double price , double strike ,double rate , double div , double vol ,double T , double t );
		double calcRho      (double price , double strike ,double rate , double div , double vol ,double T , double t ,char type );
		double calcTheta   	(double price , double strike ,double rate , double div , double vol ,double T , double t ,char type );
	protected :
	// Greek sensitives
		double delta ;
		double gamma ;
		double theta ;
		double Vega ;
		double rho ;
	};
	
protected :
	double 			strike_ ;
	double 			rate_ ;
	double 			T_ ;   
	double 			price_;
	double 			vol_ ;
	double 			dividend_ ;
	char 			type_ ;
	Exercise 		exercise_ ;
	OptionGreeks 	og ;
	StatUtility    	util ;                            //statistical utility class
	friend class 	MonteCarloMethod ;
	Matrixutil 		mu ;                              //matrix utility class 
};

/*namespace Quantlib 
{
    class Option : public Instrument 
    {
    public :
            enum Type {Call , Put , Straddle }; 
            Option1 (const Handle <pricingEngine >& engine , const std :: string & isinCode = "" , const std ::string& description ="" ) ;
            virtual ~Option1();
            void setPricingEngine (const handle <pricingEngine >& );

protected :
            void setPricingEngine() const = 0 ; 
            virtual void performCalculations () const ;
            Handle <pricingEngine > engine_ ;
    }    
}
*/
#endif