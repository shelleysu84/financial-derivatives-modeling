#inlcude <BlackModel.h>
/**********************************************************************************
priceBlackCap : computes the price of caplets using BlacksFormula
[in]: vector<double> capVol : vector of cap volatilities
vector<double> PDB : price of pure discount bonds
vector<double> maturity : vector of caplet maturities (payment times)
vector<double> Rcap : cap rate
double L : principal amount of loan
double tenor : length of time between payment times (reset dates)
[out]: vector<double> : caplets
*********************************************************************************/

std::vector <double > BlackModel1::priceBlackCap (std::vector<double> capVol , std::vector<double> PDB ,std::vector<double> maturity,double Rcap ,double L ,double tenor)
{
        int i ; 
        std::vector<double> f; 
        std::vector<double> R ; // yield price
        std::vector<double> capV ;
        std::vector<double> p ;
        std::vector<double> t ;
        std::vector<double> caplet ;
        std::vector<double> HL[20];
        double faceValue = 0.0 ; 
        double Ps= 0.0; 
        double tmp = 0.0 ; 
        std::vector<double>::iterator iter ;
        faceValue = L*(1+Rcap*tenor) ;
        for (iter = capVol.begin() ; iter != capVol.end(); iter++)
        {
                tmp = *iter ; 
                capV.push_back (tmp); 
        }  
        for (iter = PDB.begin(); iter !=PDB.end(); iter++) 
        {
                tmp = *iter ; 
                P.push_back (tmp);        
        } 

        for(iter = maturity.begin(); iter!=maturity.end (); iter ++) 
        {
                tmp = *iter ;
                t.push_back (tmp);
        } 
        for (i = 0 ; i <capValue.size(0; i ++) 
        {
                tmp = -(1/t[i])*log(P[i]) ; 
                R.push_back(tmp); 
                tmp = - (1/tenor)*log(P[i+1]/P[i]); 
                f.push_back(tmp) ; 
        } 
        for(i = 0 ; i <capVol.size() -1; i ++) 
        {
                tmp = BlacksFormula(f[i], P[i], 1, 0.07 , capV[i], t[i], tenor); 
                //tmp = BlackspotFormula(f[i], P[i], faceValue , Rcap , capV[i], t[i], tenor);
                caplet.push_back(tmp); 
        } 
        return caplet ; 
}

double BlackModel1::BlacksFormula(double f,double P ,double L ,double Rcap ,double vol ,double tau ,double dtau)
{
        StatUtility util ; 
        double d1 = log(f/Rcap) +((vol*vol)/2*tau)/(vol*sqrt(tau)); 
        double d2 = d1 - vol*sqrt(tau); 
        return P*dtau*L *(f*util.normalCalc(d1) - Rcap*util.normalCalc(d2)) ;
} 
