/*calc implied volatility*/
#include <VanillaOption.h >
#include <BlackShcolesModel.h >
#include <Brent.h>
#include <Option.h>

VanillaOption :: VanillaOption(double price , double strike , double Volatility, double rate ,double div ,double maturity , Option :: Type type , Option ::Exercise exercise , const Handle <PricingEngine >& engine ) : Option (engine ), riskfreerate_(rate ), dividendYield_(div ), type_(type ),exercise_ (exercise) , underlying_ (price ), stike_ (stike ), maturity_ (maturity ), Volatility_ (Volatility )
{
	//register parameters in engine
	registerWith (price);
	registerWith (div);
	registerWith (rate);
	registerWith (Volatility);
}

double VanillaOption::delta() const 
{
	calculate();
	return delta_;
}

double VanillaOption::gamma() const 
{
	calculate();
	return gamma_;
} 

double VanillaOption::theta() const 
{
	calculate();
	return theta_;
}
double VanillaOption::vega() const {
	calculate();
	return vega_;
}

double VanillaOption::rho() const {
	calculate();
	return rho_;
} 


double VanillaOption:: impliedVolatility (double targetValue, double accuracy, Szie maxEvaluations , double minVol ,double maxVol ) const 
{
	double value = NPV () ; //初始化股票
	vol = volatility_ ;
	if (value == targetValue )
	{    	return vol ;     }
	else 
	{
	        ImpliedVolHelper  f (engine_,targetValue ) ;
	        Solvers1D::Brent Solver; // 在Brent.h里定义的类
	        solver.setMaxEvaluations (maxEvaluations ) ;
	        return solver.solve (f ,accuracy ,vol ,minVol ,maxVol ); //在min,max 之间找到方程解的一个function
	}
//return 0.0 ;
}

void VanillaOption::setupEngine() const 
{
	PricingEngines::VanillaOptionArguments *Arguments = new PricingEngines ::VanillaOptionArguments () ;
	arguments->type = type_;
	arguments->underlying = underlying_;
	arguments->strike = strike_;
	arguments->volatility = volatility_;
	arguments->dividendYield = 0.0;
	arguments->riskFreeRate = riskFreeRate_;
}

void VanillaOption ::performCalculations () const 
{
	if(exerciseDate _ <= riskFreeRate -> referenceDate ())
	{
	        isExpired = ture ;
	        NPV_ =delta_ =gamma_ = theta_ =Vega_ =rho_=dividendRho_ = 0.0 ;
	}
	else 
	{
	        isExpired = false ;
	        Option::performCalculations (); //
	        const OptionGreeks * results = dynamic_cast <const OptionGreeks*> (engine_ ->results () );
	}
}

VanillaOption ::ImpliedVolHelper ::ImpliedVolHelper(const Handle <pricingEngine>& engine ,double targetValue) : engine_(engine),targetValue_(targetValue)
{
	results_ = dynamic_cast <const OptionValue *>(engine_->results()) ;
}

double VanillaOption ::ImpliedVolHelper ::operator()(double x) const 
{
	engine_ -> calculate ();
	return results_ ->value-targetValue_ ;
}
std::map<pair<double,int>,double >
VanillaOption ::ImpliedVolHelper::calcImpliedSurface (double price ,vector<double> opPrices ,vector <int> strikes ,
            vector <double>maturities, map<double,double > rates ,double dividend ,char type)
{
	const char *file = "surface.txt" ;
	ofstream fout (file ,ios::out |ios::app);
	int i = 0 ;
	map <pair<double ,int>, double > surfaceMap ;
	pair <double ,int> TXPair, TXpair1 ;
	vector <double>::iterator iter;
	vector <int>::iterator iter1;
	vector <pair<double ,int>> vecPair ;
	vector <double> mat ;
	vector <int> X ;
	vector <pair<double ,int>>::iterator vecPairIter ;
	list <double> volList [100] ;
	list <double> ::iterator listIter ;
	int j = 0;
	int cnt = 0 ;
	const epsilon = 0.00001;
	vector <double> ::iterator priceIterator ;
	double temp = 0.0;
	double vol1 = 0.0;
	double error = 0.0;
	double vol2 = 0.0;
	double vega = 0.0;
	double BSPrice = 0.0;
	double marketPrice = 0.0;
	
	int *stirke = new int [strikes.size()] ;
	double *maturity = new double [maturities.size ()] ;
	double *call = new double [opPrices.size()] ;
	Option::OptionGreeks og ;
	Pricers::BlackScholesOption bso ;
	copy (strikes .begin(), strikes.end(),stike) ;
	copy (opPrice.begin(),opPrices.end () ,call) ;
	copy (maturities.begin (), maturities.end() ,maturity) ;
	
	if (type == 'C')
	{
	        for (priceIter=opPrices.begin(); priceIter!=opPrices.end(); priceIter++)
	        {
	                marketPrice = *priceIter ;
	                vol1 = 0.45;
	                printf("strike[%d] = %d  Prices =  %0.3f\n",cnt,strike[cnt], *priceIter) ;
	                
	                do
	                {
	                        BSPrice = bso.calcBSCallPrice(vol1,rates[maturity[cnt]],dividend,strike[cnt],price,maturities[cnt]) ;
	                        Vega = og.calcVega (price, strike[cnt],rates [maturity [cnt],dividend,vol1,maturities[cnt],0) ;
	                        vol2 = vol1 - (BSPrice - marketprice)/(Vega) ;
	                        error = vol2- vol1 ;
	                        vol1= vol2 ; 
	                }while (abs(error) > epsilon) ;
	                TXPair .first = maturity[cnt];
	                TXPair.second = strike [cnt] ;
	                surfaceMap[TXPair] = vol1 ;
	                cnt++ ;
	        }        
	        
	}
	else
	{
		for (priceIter = opPrices.begin(); priceIter != opPrices.end(); priceIter++)
		{
				
		marketPrice = *priceIter;
		vol1 = 0.65;
		do
		{    
			BSPrice = bso.calcBSPutPrice(vol1,rates[maturity[cnt]],dividend,strike[cnt],price,maturities[cnt]);
	    		vega = og.calcVega(price,strike[cnt],rates[maturity[cnt]],dividend,vol1,maturities[cnt],0);
			vol2 = vol1 - (BSPrice - marketPrice)/(vega);
			error = vol2 - vol1; 
			vol1 = vol2;
		}while (abs(error) > epsilon);
		TXPair.first = maturity[cnt];
		TXPair.second = strike[cnt];
		surfaceMap[TXPair] = vol1;
		cnt++;
		}
	}
                
   	for (Iter = maturities.begin (); Iter != maturities.end () ; )
	{
		temp = *Iter ;
		Iter ++ ;
		if (temp !=*Iter)
		mat.push_back (temp);
    	}
	sort (strikes.begin(),strikes.end()) ; 
	for (Iter1= strikes.begin(); Iter1 !=strikes.end(); )
    	{
		temp = *iter1;
		iter1++;
		vector<int>::iterator k = find(X.begin(),X.end(),temp);
		if (k == X.end())
		X.push_back(temp);
    	}

        for (vecPairIter = vecPair.begin(); vecPairIter != vecPair.end(); vecPairIter++)
	{
		std::cout << "[ " << vecPairIter->second << ", " << vecPairIter->first << ", " << surfaceMap[*vecPairIter] << "]" << endl;
		fout << vecPairIter->second << " " << vecPairIter->first << " " << surfaceMap[*vecPairIter] << "\n" << endl;
        }
} 
