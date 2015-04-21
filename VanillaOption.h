#ifndef quantlib_vanilla_option_h
#define quantlib_vanilla_option_h 

#include "Option.h "
#include "Termstructure.h "
#include "Solver1D.h "
#include "MarketElement.h "
#include "VanillaEngines.h "
#include "PricingEngine.h "
using namespace QuantLib;
namespace Instruments 
{
	class VanillaOption : public option 
	{
	public :
		VanillaOption () { }
		VanillaOption (double price ,double strike ,double rate , double div ,double vol ,double T ,
			Option ::Type type , Option ::Exercise exercise ,const Handle <pricingEngine>& engine ) ;
		double delta () const ;
		double gamma () const ;
		double theta () const ;
		double Vega () const ;
		double rho () const ;
		double impliedVolatility (double targetValue , double accuracy = 1.0e -4 , 
			Size maxEvaluations = 100, double minVol=1.0e -4, double maxVol =4.0) const;

	protected :
		void setupEngine () const ;
		void performCalculations () const ;
		virtual double calculate () const {    return 0.0;    }

		Date exerciseDate_ ;
		relinkableHandle <TermStructure> riskFreeRate ;
		mutable double delta_ , gamma_ , theta_ , Vega_ , rho_ , dividendRho_ ;
		Option ::Type type_ ;
		Option ::Exercise exercise_ ;
		double underlying_ ; //what does this mean?
		double strike_;
		double dividendYield_ ;
		double riskFreeRate_ ;
		double maturity_ ;
		double Volatility_ ; 
        
	private :
		// helper class for implied volatility calculation
		class ImpliedVolHelper : public ObjectiveFunction 
		{
		public :
			StatUtility util ;
			std :: map <int ,double > calcImpliedVols (double price ,std ::vector <double > opPrices ,  
				std ::vector <int >strikes , double rate , double dividend , double T ,char Type );    
			//计算隐含波动率： 股价，Option价格，执行价格，利率，分走的红利，成熟时间，期权种类
			
			std::map <std::pair<double ,int>, double > calcImpliedSurface (double price , std :: vector <double> opPrices, 
				std ::vector <int > strikes, std::vector <double > T , std::map <double ,double > rates , double dividend ,char type );
			//计算波动率曲面： 股价，Option价格(向量)，执行价格(向量)，成熟时间(向量)，利率(Key-Value查询数据)，红利，期权种类
			
			ImpliedVolHelper (const Handle <PricingEngine >& engine , double targetValue ) ; 
			ImpliedVolHelper () {}
			double operator ()(double x ) const;
		private :
			Handle <PricingEngine > engine_ ;
			double targetValue_ ;
			const OptionValue* results_ ;
			
			//QuantLib::PricingEngines::VanillaOptionArguments* arguments_;
		};
	};
}

#endif 
