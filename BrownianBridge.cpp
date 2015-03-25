#include <BrownianBridge.h >

BrownianBridge::BrownianBridge(unsigned long numberofsteps) : numberofsteps(numberofsteps) ,leftIndex(numberOfsteps),rightIndex(numberofsteps),  bridgeIndex(numberofsteps), leftWeight (numberofsteps),rightweight(numberofsteps),stddev (numberofsteps)
{
        vector <unsigned long> map (numberofsteps) ;
        unsigned long i ,j , k ,l ;

        map [numberofsteps -1 ] = 1;                //first pointer is the global step 
        bridgeIndex [0] = numberofsteps -1 ;    
        stddev [0] = sqrt (numberofsteps ) ;    //var of global step is numberofsteps*1 
        leftweight [0] =rightWeight[0] =0 ;    

        for (j = 0 ,i =0; i <numberofsteps ; ++i)
        {
                while (map[j])
                        ++ j ;
                k = j ;
                while (!map[k])
                        ++k ;                //find a blank gap choose the head and tail 
                l = j +((k -1-j)>>1) ;
                map [l] = i ;
                bridgeIndex [i] = l ;
                leftIndex = j ;
                rightIndex = k ;
                leftWeight [i] = (k -l) /(k +1 - j );
                rightWeight [i] = (l+1 - j) / (k +1 - j );
                stddev[i] = sqrt( ((l +1 - j )*(k - l )/(k+1 - j)) ) ;        //fomula (2.42)
                j = k +1 ;

                if (j > = numberof steps)
                            j = 0 ; 
        }
}

void BrownianBridge::buildPath (vector <double >& path , const vector <double> & normalVariates )
{
        assert (normalVariates .size () = = numberofsteps && path.size() == numberofsteps ) ;
        unsigned long i , j ,k , l ;
        path [numberofsteps - 1] = stddev [0] *normalVariates [0] ;
        
        for (i = 1; i < numberofsteps ;i ++)
        {
                j = leftIndex [i];
                k = rightIndex [i] ;
                l = bridgeIndex [i] ;
                if (j)
                        path [l] = leftweight [i]*Path[j -1] + rightweight[i]*path [k] + stddev [i]*normalVariates [i] ;
                else 
                        path [l] =  rightweight[i]*path [k] + stddev [i]*normalVariates [i] ;
        }
}

void BrownianBridge::generateDeviates (unsigned long numberofsteps)
{
        double deviate = 0.0 ;
        srand (time (0)) ;
        long seed = (long) rand ();
        long *idum = &seed ;
        for (int i = 0 ; i <numberofsteps; i ++)
        {
                deviate = util.gasdev (idum ) ;
                normalVariates.push_back (deviate) ;
        }

}
