/*QUASI-RANDOM SEQUENCES*/
#ifndef _utility_h 
#define _utility_h 

#define min (a,b) (((a )<(b ))?    (a ):(b ))
#define GRAY (n) (n^(n>>1))

#define MAXBIT 30 
#define MAXDIM 6
#define VMAX 30

#include <vector>
#include <iostream>
#include <algorithm>
#include <constants.h>
#include <Deviates.h>
#include <math>
#include <gsl_math.h>
#include <gsl_rng.h>
#include <gsl_randist.h>
#include <gsl_integration.h>

#ifndef SOBOLP_H 
#define SOBOLP_H 

struct sobolp 
{
	double sequence [MAXDIM];  		//
	int x[MAXDIM]:
	int v[MAXDIM][VMAX];		
	double RECIPD;               
	int _dim;                                                
	int _skip;
	unsigned long _nextn;
	unsigned long cur_seed;
};

#endif 

using namespace std ;
 
class comp_last 
{
public :
	bool operator () (int x ,int y )
	{    return x < y ;    }
} ;

class StatUtility 
{
private :
        vector<double> Y ;
        vector<double>::iterator iter ;
        double *x , *g ,*h ;        //for simpson's rule ?
        int * A ;
        vector <double > X ;        //for Faure sequence ?
public :
        //正态分布的数值模拟算法
        double normalCalc (double d)
        {
            const double a1 = 0.31938530;    
	        const double a2 = -0.356563782;
	        const double a3 =  1.781477937;
	        const double a4 = -1.821255978;
	        const double a5 =  1.330274429;
			const double gamma = 0.2316419;
			const double k1 = 1/(1 + gamma *d ) ;
			const double k2 = 1/(1 - gamma *d ) ; 
			const double normalprime = (1/(sqrt(2*PI)))*exp(-d*d/2) ;
			double value = 0.0 ;
			//double h = 0.0 ;
			
			if (d >=0)
				value = 1- normalprime * (a1*k1 +a2*pow(k1,2)+ a3*pow(k1,3)+a4*pow(k1,4)+a5*pow(k1,5)) ;
			else 
				value = normalprime *(a1*k2 + a2*pow(k2,2)+ a3*pow(k2,3)+a4*pow(k2,4)+a5*pow(k2,5)) ;
			
			return value ;
        }//end of normal calculate
 
        //随机生成数 摘自<<数值算法in C++>>
        double ran1 (long *idum )
        {
                int j ;
                long k; 
                static long iy = 0;
                static long iv [NTAB];
                double temp ;

                if (*idum <=0 || !iy )
                {
					if (-(*idum) <1)
						*idum =1 ;
					else 
						*idum = -(*idum ) ;
					for (j=NTAB+7 ;j >=0;j --)
					{
						k = (*idum )/IQ ;
						*idum = IA *(*idum -k *IQ) -IR*k ;
						if (*idum<0)
							*idum+= IM ;
						if (j<NTAB)
							iv[j]= *idum ;
					}
					iy = iv [0];
                }
                k = (*idum)/IQ ;
                *idum = IA *(*idum -k *IQ) -IR*k ;
                if (*idum <0)
                        *idum +=IM ;
                j = iy /NDIV;
                iy = iv [j];
                if ((temp=AM *iy)>RNMX)
                        return RNMX ;
                else 
                        return temp ;

        }

        double gasdev (long *idum )
        { 
                static int iset = 0;
                static double gset ;
                double fac ,rsq ,v1 ,v2 ;
                if (!set ==0)
                {
                        do 
                        {
                                v1 = 2.0 *ran1 (idum ) -1.0 ;
                                v2 = 2.0 *ran1 (idum ) - 1.0 ;
                                rsq = v1*v1 + v2 * v2 ;
                        }while (rsq > = 1.0 || rsq == 0.0) ;
                        
                        fac = sqrt (-2.0*log (rsq )/rsq ) ;
                        gset = v1 *fac ;
                        iset = 1;
                        return v2 *fac ;
                }
                else 
                {
                        iset = 0 ;
                        return gset ;
                }                
        }

        double normalCalcPrime (double d)
        {        return (1/sqrt(2*PI)*exp(-d*d/2)) ;        }

        double Uniformrandom (double min ,double max )
        {
               //continue later     
        }

        void sobolp_generateSamples (struct sobolp *config, double *Samples)
        {// samples : pointer to sample Values 
                int i ;
                nextSobol(config, config->cur_seed) ;
                config ->cur_seed++;
                for (i=0;i <config->_dim; i++)
                        samples[i]= config->sequence[i];
        }
        static void nextSobol(struct sobolp* config, int seed)
        {
                int c ,gray ,i ;
                seed +=config->_skip +1;
        //if we have seed , we shall accumulate the value of config->x[i], until seeds disappear;
                for (i = 0 ;i <config ->_dim; i++)
                {
                        config ->x[i] = 0;        //store the direction numbers 
                        c =1 ;
                        gray = GRAY(seed) ;
                        while (gray)
                        {
                                if (gray&1)
                                        config ->x[i]=config->x[i]^( config->v[i][c-1]<<(VMAX-c) ); 
                                        // M = pow (v,q)^M , q = VMAX - index;
                                c ++;
                                gray>>=1; 
                                //gray = gray >>1 = gray /2 ;
                        }
                    
                 config ->sequence [i] = config->x[i]*config->RECIPD ;        
                 }
        }
        //if we do not have seed , then we just calculate x[i] once .
        static void nextSobolpNoSeed (struct * config )
        {
                int c =1;
                int i , save = config ->_nextn ;
                while ((save %2)==1)
                {
                        c ++;
                        save = save /2;
                }
                for ( i =0; i <config->_dim; i ++)
                {
                        config ->x[i] = config->x[i]^( config->v[i][c-1]<<(VMAX-c) ); 
                        config ->sequence [i] = config->x[i]*config->RECIPD ;  
                }
                config ->_nextn ++; 
        }
        
        //初始化Sobolp的结构，初始化V[i][j]的值，
        void Sobolp_init(struct sobolp* config ,int dim ,unsigned long seed)
        {
                int d[MAXDIM],POLY[MAXDIM];
                int save ;
                int m ,i ,j ,k ;
                config ->_dim = dim ;
                config ->_nextn = 0; 
                config ->RECIPED= 1.0/ pow (2.0, VMAX);
                
                POLY[0] = 3;  d[0] = 1;  /* x + 1         */
                POLY[1] = 7;  d[1] = 2;  /* x^2 + x + 1   */
                POLY[2] = 11; d[2] = 3;  /* x^3 + x + 1   */    
                POLY[3] = 19; d[3] = 4;  /* x^4 + x  + 1  */
                POLY[4] = 37; d[4] = 5;  /* x^5 + x^2 + 1 */
                
                for (i = 0 ; i <config ->_dim; i ++)
                        for (j = 0; j <d[i]; j ++)
                                config->v[i][j] =1;        //做出下三角型的V矩阵

                for (i = 0 ; i <config ->_dim; i ++)
                        for (j =0; j< VMAX; j ++)
                        {
                                config->v[i][j] = config->v[i][j-d[i]] ;
                                save = POLY[i];
                                m = pow(2, d[i]);
                                for (k = d[i]; k>0 ; k --)
                                {
                                        config->v[i][j] = config->v[i][j] ^ m* (save%2)* config->v[i][j-k];
                                        save = save /2;
                                        m = m /2;
                                }
                        }

                for (i = 0 ;i <config->_dim ; i ++)
                        config ->x[i] = 0;
                config ->_skip = pow (2,6) ;
                for (i =1; i <= config->_skip ; i ++)
                        nextSobolpNoSeed(config) ;
           
        }
    
//generate the Faure sequence 
        vector<double> generateFaure (long N ,long M)
        {
                int p = generateprime (N);
                int l , q, k ;
                long v1, v2 ,v3 ;
                long value = 0 ;
                long a[250][250] = {0};
                int m = (int) log(M)/log(p) ;
                if (m ==0)
                        m =1 ;
                long x[] = {0} ;
                unsigned long fact = 0;
                
                for (k =1 ;k <=N ;k++)
                {
                        for (l = 0; l <= m ; l ++)
                }
                
        }
	//generate poisson distribution
        int poisson (double mu)
        {
                assert (mu >0 )
                double a = exp (- mu );
                double b =1 ;
                int i ; 
                for (i = 0; b > =a ; i ++)
                        b *= _u (); 

                return i -1 ;   
        } 

	//.. continue later        
}//StatUtility  
#endif
