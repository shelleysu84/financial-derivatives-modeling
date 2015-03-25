#ifndef _brownianbridge_h_
#define _brownianbridge_h_

#include <assert.h >
#include <math >
#include <vector >
#include <Utility.h>
using namespace std ;

class BrownianBridge 
{
public :
            BrownianBridge (unsigned long numberofsteps );            //设置步数
            virtual ~ BrownianBridge()    {}
            void buildpath(vector <double >& theWienerProcessPath ,const vector <double >& gaussianVariates );
            //设置维纳路径和高斯变量
            void generateDeviates (unsigned long numberofsteps) ;
private :
            unsigne long numberofsteps ;
            vector <unsigned long > leftIndex ;            //左，右，中的索引
            vector <unsigned long > rightIndex ;
            vector <unsigned long > bridgeIndex ;
            vector <double > leftweight ;                      //左右权重
            vector <double > rightweight ;
            vector <double > stddev ;                            //standard deviates
            vector<double> normalVariates;                //epselon belong to Normal Distribution
            StatUtility util;
};

#endif 
