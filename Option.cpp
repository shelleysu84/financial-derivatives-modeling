#include "Option.h"
#include "BlackScholesModel.h"
#include "Utility.h"
#include "Constants.h"
#include "Handle.h"

using namespace std;

// overloaded constructor
Option:: Option(double price, double strike, double vol, double rate, double div, double T, char type, char exercise)
	: price_(price), strike_(strike), vol_(vol), rate_(rate), dividend_(div), T_(T), type_(type), exercise_(exercise)
{}
​
double Option :: OptionGreeks ::calcDelta (double price ,double strike,  double rate, double div, double vol, double T, double t, char type) 
{
	double delta = 0.0 ;
	double d1 = (log (price /strike ) + (rate - div + vol *vol /2) *(T - t ))/(vol * sqrt (T -t )) ;
	if (type == 'C')
		delta = exp (-div *(T - t )) * util.normalCalcPrime(d1);
	else 
		delta = exp (-div *(T - t )) *( util.normalCalc(d1)-1) ;
	return delta ;
}

double Option::OptionGreeks::calcGamma (double price ,double strike, double rate, double div, double vol, double T, double t) 
{
	double d1 = (log (price /strike )+(rate -div +vol *vol /2)*T )/(vol *sqrt (T)) ;
	double gamma= (util.normalCalcPrime (d1)*exp (-div *T ))/(price *vol *sqrt (T));
	return gamma;
}

double  Option ::OptionGreeks::calcVega (double price ,double strike , double rate ,double div ,double vol , double T ,double t )
{
	double d1 = (log (price /strike )+(rate - div + vol *vol /2))*T / (vol *sqrt (T ));
	return price * exp (-div *T)* sqrt (T)*util .normalCalcPrime (d1);
}

double Option ::OptionGreeks :: calcTheta (double price ,double strike,  double rate, double div, double vol, double T, double t, char type)
{
	double d1 = (log (price /strike )+(rate -div + vol *vol /2))*T / (vol *sqrt (T ));
	double d2 = d1 - vol *sqrt (T );
	double theta =0.0;
	if (type == 'C')
		theta = (-price *util .normalCalc (d1)* vol *exp (-div *T ))/(2*sqrt (T )) +div *price*util. normalCalc (d1)*exp (-div *T ) -rate *strike *exp (-rate *T )*util .normalCalc(d2);
	else 
		theta = (-price *util .normalCalc (d1)* vol *exp (-div *T ))/(2*sqrt (T )) - div *price*util. normalCalc (d1)*exp (-div *T ) +rate *strike *exp (-rate *T )*util .normalCalc(d2);
	return theta ;
}

double Option :: OptionGreeks :: calcRho (double price , double strike,  double rate, double div, double vol, double T, double t, char type) 
{
	double d1 = (log (price /strike )+ (rate - div +vol *vol/2)*(T -t )/(vol *sqrt (T - t ));
	double d2 = d1 - vol *sqrt (T - t );
	double rho = 0.0;
	if (type = 'C')
			rho = strike *( T - t )*exp (-rate *(T - t )*util.normalCalc (d2));
	else 
			rho = -strike *(T - t )* exp (-rate * (T - t ))* util.normalCalc (-d2);
	return rho ;
}

Option::Option(const Quantlib :: Handle <Quantlib :: pricingEngine>& engine ) : engine_ (engine )
{
    QL_REQUIRE (!engine_.ISNULL (), "Option::Option : null prcing engine not allowed ");
}

void Option ::setPricingEngine (const Quantlib ::Handle <Quantlib :: pricingEngine >& engine )
{
	QL_REQUIRE (!engine.ISNULL(),"Option ::setPricingEngine : null pricing engine not allowed " );
	engine_ = engine ;
	update();
	setupengine ();
}

void Option ::performCalculations () const 
{    
	setupEngine ();
	engine_ ->calculate ();
	const Quantlib::OptionValue *results = dynamic_cast <const Quantlib ::OptionValue * >(engine_ ->result ());
	QL_ENSURE(results != 0, "Option::performCalculation: no result");
	NPV_ = results ->value;
}

/*namespace Quantlib 
{
        Option1::Option1 (const Handle <PricingEngine> &engine , const std::string & isinCode ,const std ::string & description) : Instrument (isinCode , description ), engine_ (engine)
        {
        QL_REQUIRE (!engine_.isNull(), "Option :: Option : null pricing engine not allowed ");
        }

        Option1::~Option1() {}
        
        void Option1::setPricingEngine (const Handle <pricingEngine>& engine)
        {
                QL_REQUIRE (!engine.ISNULL (), "Option::setPricingEngine : null pricing engine not allowed ");
                engine_ =engine ;
                update ();
                setupEngine ();
        }

        void Option1::performCalculations() const 
        {
                setupEngine ();
                engine_ ->calculate ();
                const OptionValue *result = dynamic_cast <const OptionValue *> (engine_ ->result ());
                QL_ENSURE (results ! = 0, "Option::performCalculation :" "no results returned from option pricer ");
                NPV_ = results ->value ;
        }
}
*/