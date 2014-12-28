#ifndef BSM_option_pricer_h 
#define BSM_option_pricer_h 
#include "Solver1d.h"
#include "Errors.h"
#include "VanilaOption.h"

#define QL_MIN_VOLATILITY 1.0e-4
#define QL_MIN_DIVYIELD 1.0e-7
#define QL_MAX_VOLATILITY 4.0
#define QL_MAX_DIVYIELD 4.0

namespace Quantlib {
	namespace Pricer {
		double ExercisePayoff (Option ::Type type ,double price ,double strike ) ;
		class BlackScholesOption : public Quantlib ::Instrument ::VanillaOption {
		public :
			BlackScholesOption () {}
			BlackScholesOption (Option::Type type ,double underlying ,double strike ,
				double dividendYield ,double riskfreeRate ,double residualTime ,double volatility ) ;
			virtual ~BlackScholesOption () {}
			virtual void setVolatility(double newVolatility) ;
			virtual void setDividendYield (double newDividendYield ) ;
			virtual double value () const ;
			virtual double delta () const ;
			virtual double gamma () const ;
			virtual double theta ()const ;
			virtual double Vega () const ;
			virtual double rho () const ;
			double calcBSCallPrice (double price ,double strike ,double vol ,
				double rate ,double dividend ,double T ) ;
			double calcBSCallPrice () ;
			double calcBSPutPrice (double vol ,double rate ,double div ,
				double strike , double price ,double T ) ;
			double calcBSPutPrice () ;
		protected :
			Option::Type type_ ;
			Option::Exercise exercise_ ;
			double underlying_ ;
			double strike_ ;
			double dividendYield_ ;
			double riskFreeRate_ ;
			double residualTime_ ;
			double volatility_ ;
			double value_ ;
		private :
			class VolatilityFunction ;
			friend class VolatilityFunction ;
			class DivYieldFunction ;
			friend class DivYieldFunction ;
		};
		
		class BlackScholesOption ::VolatilityFunction : Public ObjectiveFunction {
		public :
			VolatilityFunction (const Handle <BlackScholesOption >& tempBSM ,double targetPrice ) ;
			double operator () (double x) const ;
		private :
			mutable Handle <BlackScholesOption> bsm ;
			doubel targetPrice_ ;
		};
		
		inline BlackSholesOption ::VolatilityFunction ::VolatilityFunction (const Handle <BlackScholesOption >& tempBSM ,double targetPrice ){
					bsm = tempBSM ;    
					targetPricer_ = targetPrice ;
		}
		inline double BlackScholesOptipn::VolatilityFunction::Operator () (double x) const {
					bsm ->setVolatility (x);
					return (bsm ->value () - targetPrice_) ;   
		}
		inline BlackScholesOption ::DivYieldFunction ::DivYieldFunction (const Handle <BlackScholesOption >& tempBSM ,double targetPrice)
		{
					bsm = tempBSM;
					targetPrice_ = targetPrice;
		}

		inline double BlackScholesOption ::DivYieldFunction::Operator () (double x) const {
					bsm ->setDividendYield (x);
					return (bsm ->value () - targetPrice_) ;   
		}
	}//endof namespace Pricer  
}//endof namespace Quantlib 

#endif






