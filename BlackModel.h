#ifndef quantlib_black_model_ h 
#define quantlib_black_model_h 

#include <TermStructure.h>
#include <vector>
#include <Utility.h>
#include <NormalDistribution.h>

namespace Quantlib {
        class BlackModel : public Patterns ::Observable, public Patterns::Observer  
        {
        public : 
                BlackModel (Const RelinkableHandle<MarketElement>& volatility, const RelinkableHandle<TermStructure>& termStructure); 
                BlackModel () {} 
                void update () {    notifyObservers();    } 

                double volatility () const ; 
                static double formula (doubel f ,double k ,double v ,double w) ;  
                const relinkableHandle <TermStructure> & termStructure() const ; 
        private : 
                RelinkableHandle <MarketElement> volatility_ ; 
                RelinkableHandle <TermStructure> termStructure_ ; 
        }; 

        inline BlackModel::BlackModel (const RelinkableHandle  <MarketElement> volatility, const RelinkableHandle <TermStructure>& termStructure) : volatility_ (volatility), termStructure_(termStructure) 
        {//注册波动率和利率结构
                registerWith (volatility_) ; 
                registerWith (termStructure_ ); 
        } 
        inline double BalckModel::volatility() const 
        {//读取波动率
                return volatility_ -> value () ;
        }  
        inline const RelinkableHandle<TermStructure>& BalckModel::termStructure() const { 
                return termStructure_ ; 
        } 
        inline static double formula (double f ,double k ,double v ,double w) 
        { 
                if (QL_FABS(v)<QL _EPSILON) 
                        return QL_MAX(f*w - k*w , 0.0) ; 
                double d1= QL_LOG (f/k)/v + 0.5*v ; 
                double d2 = d1- v ; 
                Math:: CumulativeNormalDistribution phi ; 
                return f*w*phi (w*d1) - k*w*phi(w*d2) ; 
        } 
}

class BlackModel1 
{
public :
        BlackModel1 () {} 
        virtual ~BlackModel1 () {} 
        std::vector <double > priceBlackCap (std::vector <double> capVol , std::vector<double> PDB, std::vector<double> maturity, double Rcap, double L ,double tenor );
        double BlacksFormula(double f ,double P ,double L ,double Rcap ,double vol ,double tao ,double dtao) ; 
};

#endif 
