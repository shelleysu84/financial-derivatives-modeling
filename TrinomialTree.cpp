#include <TrinomialTree.h>

double GeneralTrinomialTree::buildGeneralTrinomialTreeEuropean(double price ,double strike ,double vol ,double rate ,double div ,double T ,long N ,char type)

{
  int i ,j ;
  double pd ;
  double pm ;
  double pu ;
  double S[250][250] = {0.0} ;
  double C[250][250] = {0.0} ;
  double num = 0.0 ;
  double up = 0.0 ;
  double down = 0.0 ;
  double drift = 0.0 ;
  double dt = 0.0 ;
  double dx = 0.0 ;

        dt = T /N ;

        drift = rate -div -0.5*vol*vol ;
        pu = 0.5+ 0.5*(drift/vol)*sqrt (dt) ;
  pd = 0.5 - 0.5*(drift/vol)*sqrt(dt);
 pm = 0.0;
 up = exp(vol*sqrt(dt));
 down = 1/up;

        for (i = N ;i >= 0 ; i --) 
        {
                for (j =-i ; j <=i ;j ++) 
                        S[i][j] = price *pow(up , j ) ; 
        } 

        for (j = N ; j >= -N ;j --) 
        {
                if (type == 'C') 
                        C[N][j] = max (0, S[N][j] -strike) ; 
                else  
                        C[N][j] = max (0, strike- S[N][j]) ; 
        } 

        for (i = N -1 ;i >= 0 ;i --) 
        {
                for (j = i ; j >= -i ; j --) 
                    C[i][j] = exp (-rate*dt)*(pu*C[i+1][j+1] + pm*C[i+1][j] +pd*C[i+1][j -1]);      
        } 
        return C[0][0] ; 

}

double GeneralTrinomialTree::buildGeneralTrinomialTreeAmerican(double price ,double strike ,double vol ,double rate ,double div ,double T ,long N ,char type)

{
        int i ,j ;
        double pd ;
        double pm ;
        double pu ;
        double S[250][250] = {0.0} ;
        double C[250][250] = {0.0} ;
        double num = 0.0 ;
        double up = 0.0 ;
        double down = 0.0 ;
        double drift = 0.0 ;
        double dt = 0.0 ;
        double dx = 0.0 ;

        dt = T /N ;

        drift = rate -div -0.5*vol*vol ;
        pu = 0.5+ 0.5*(drift/vol)*sqrt (dt) ;
  pd = 0.5 - 0.5*(drift/vol)*sqrt(dt);
 pm = 0.0;
 up = exp(vol*sqrt(dt));
 down = 1/up;

        for(i = N ; i > =0 ;i --) 
        {
                for (j = - i ; j<=i ;j ++) 
                {
                        S[i][j] = price *pow (up ,j) ; 
                } 
        } 
         
        for (j = N ; j >= -N ; j --) 
        {
                if(type =='C') 
                {
                        C[N][j] = max (0, S[N][j] -strike) ;
                        Ci [N][j] = max (0, S[N][j] -strike) ;
                } 
                else  
                {
                        C[N][j] = max ( 0 , strike - S[N][j]) ;
                        Ci [N][j] = max (0, strike - S[N][j]) ;
                } 
        } 

        for (i = N -1; i >= 0; i --) 
        {
                for (j = i ; j >= - i ; j --)
                {
                        if(type == 'C') 
                        { 
                        C[i][j] = exp(-rate *dt) *(pu*C[i+1][j+1]+pm*C[i+1][j]+ pd *C[i+1][j-1]) ;
                        Ci[i][j] = max (S[i][j] - strike , 0) ; 

                        C[i][j] = max (C[i][j], Ci[i][j]) ; 
                        } 
                        else  
                        {
                        C[i][j] = exp(-rate *dt) * (pu*C[i+1][j+1]+pm*C[i+1][j]+ pd *C[i+1][j-1]);
                        Ci[i][j] = max (strike - S[i][j] , 0) ;

                        C[i][j] = max (C[i][j], Ci[i][j]) ;
                        } 
                }      
        } 

        return C[0][0] ; 
}

double CRRTrinomialTree::buildTrinomialTreeCRREuropean  (double price,double strike,double vol,double rate,  double div, double T, long N, char type)
{
        int i , j ;
        double pd;
 double pm;
 double pu;
 double S[250][250] = {0.0};
 double c[250][250] = {0.0};
 double num = 0.0;
 double up = 0.0;
 double down = 0.0;
 double drift = 0.0;
 double dt = 0.0;
 double dx = 0.0;

  dt = T/N;
 
 drift = rate - div - 0.5*vol*vol;
        pu = 0.33333+ (drift/vol)*sqrt(dt/6) ;
        pd =  0.33333 - (drift/vol)*sqrt(dt/6) ;
        pm = 0.33333;
        up = exp (vol *sqrt(3*dt/2));
        down = 1/up ;

        for (i >N ; i >= 0; i --)
        {
                for (j =- i ;j <= i ; j ++)
                {
                        S[i][j] =price *pow (up ,j) ;
                }
        }

        for (j = N ;j >= -N ; j --)
        {
 if (type == 'C')
 c[N][j] = max(S[N][j] - strike,0);
 else
 c[N][j] = max(strike - S[N][j],0);       
        }
         
        for (i = N -1 ; i >= 0 ; i --)
        {
                for (j =i ; j >= -i ; j --)
                        C[i][j] =exp (-rate*dt) *(pu*c[i+1][j+1] + pm*c[i+1][j] + pd*c[i+1][j-1]) ;
        }
        return C[0][0] ;
}

double CRRTrinomialTree::buildTrinomialTreeCRRAmerican( double price,double strike,double vol,double rate, double div, double T, long N, char type )
{
  int i, j;
 double pd;
 double pm;
 double pu;
 double S[250][250];
 double c[250][250];
 double up = 0.0;
 double down =0.0;
 double dt;
 double drift = rate - div - 0.5*vol*vol;
 
 dt = T/N;
 

 pu = 0.33333 + (drift/vol)*sqrt(dt/6);
 pd = 0.33333 - (drift/vol)*sqrt(dt/6);
 pm = 0.33333;
 up = exp(vol*sqrt(3*dt/2));
 down = 1/up;

 for (i = N; i >= 0;  i--)
 {
 for (j = -i; j <= i; j++)
 {
 S[i][j] = price*pow(up,j);
 }
 }

 for (j = N; j >= -N; j--)
 {
 if (type == 'C')
 c[N][j] = max(S[N][j] - strike,0);
 else
 c[N][j] = max(strike - S[N][j],0);
 }

        for (i = N -1 ; i >= 0 ; i --) 
        {
                for (j = i ; j >= -i ;j --) 
                {
                        if (type =='C') 
                                C[i][j] = max (exp (-rate *dt)*(pu*C[i+1][j+1] +pm*C[i+1][j]+pd *C [i+1][j-1], S[i][j] -strike) ; 
                        else  
                                C[i][j] = max (exp (-rate *dt)*(pu*C[i+1][j+1] +pm*C[i+1][j]+pd *C [i+1][j-1], strike - S[i][j]) ;
     
                } 
        } 
         
        return C[0][0] ; 
}

double JRTrinomialTree::buildTrinomialTreeJRAmerican( double price , double strike,double vol,double rate,  double div, double T, long N, char type)
{
        int i ,j ;
        double pd ;
        double pm ;
        double pu ;
        double S[200][200] ;
        double C[200][200] ;
        double Ci [200][200] ;
        double up = 0.0 ;
        double down = 0.0 ;
        double dt ;
        double drift = rate -div -0.5*vol*vol ;
        dt = T /N ;

        pu = sqrt(dt/12) *(drift/vol) + 0.16667 ;
        pd = - sqrt(dt/12)*(drift/vol) +0.16667 ;
        pm = 0.666667 ;
        up = exp (vol*sqrt(3*dt)) ;
        down = 1/up ;

        for (i= N ; i>=0 ; i --)
        {
                for (j=-i ;j<= i ; j ++)
                        S[i][j] = price *pow (up ,j) ;
        }

        for (j = N ;j >=-N ; j--)
        {
                if (type =='C')
                {
                        C[N][j] = max (S[N][j] - strike ,0) ;
                        Ci [N][j] = max ( S[N][j] - strike ,0 ) ;
                }
                else 
                {
                        C[N][j] = max (strike - S[N][j] , 0 );
                        Ci [N][j] = max (strike -S [N][j] , 0 );
                }
        }

        for (i = N -1 ; i > = 0 ; i --)
        {
                for (j = i ;j >= - i ; j --)
                {
                        if (type =='C')
                        {
                        C[i][j] = exp (-rate*dt)*(pu*c[i+1][j+1] + pm*c[i+1][j] + pd*c[i+1][j-1]) ; 
                        Ci [i][j] = max (S[i][j] -strike ,0) ;
                        C[i][j] = max (C[i][j] , Ci[i][j]) ;
                        }
                        else 
                        {
                        C [i][j] = exp(-rate*dt)*(pu*c[i+1][j+1] + pm*c[i+1][j] + pd*c[i+1][j-1]);
                 Ci[i][j] = max(strike - S[i][j],0);
 
                 C[i][j] = max(c[i][j],ci[i][j]);
                        }
                }
        }
        return C[0][0] ;
}

double JRTrinomialTree::buildTrinomialTreeJREuropean ( double price,double strike,double vol,double rate,  double div, double T, long N, char type )
{
        int i , j ;
        double pd ;
        double pm;
 double pu;
 double S[250][250];
 double c[250][250];
 double num = 0.0;
 double up = 0.0;
 double down = 0.0;
 double drift = 0.0;
 double dt = 0.0;
 double dx = 0.0;

  dt = T/N;
 drift = rate - div - 0.5*vol*vol; 

  pu = sqrt(dt/12)*(drift/vol) +  0.16667;
 pd = -sqrt(dt/12)*(drift/vol) + 0.16667;
 pm = 0.666667;
 up = exp(vol*sqrt(3*dt));
 down = 1/up;

  for (i = N; i >= 0;  i--)
 {
 for (j = -i; j <= i; j++)
 {
 S[i][j] = price*pow(up,j);
 }
 }

        for (j= N ; j >= -N ;j --)
        {
                if (type =='C')     
                        C[N][j] = max (S[N][j] -strike , 0 ) ;
                else 
                        C[N][j] = max (strike - S[N][j] , 0) ;
        }

        for (i = N -1 ; i >= 0 ; i --)
        {
                for (j= i ; j >= -i ;j --)
                        C[i][j] =exp ( -rate*dt) *( pu*c[i+1][j+1] + pm*c[i+1][j] + pd*c[i+1][j-1] );
        }
        return C[0][0];
}
