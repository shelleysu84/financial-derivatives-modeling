#ifndef trinomial_tree _h 
#define trinomial_tree _h 

#include <DiffusionProcess.h >
#include <Tree.h>
#include <NumericalMethod.h>
#include <vector>

class TrinomialBranch 
{
public :
        TrinomialBranch () : probs_ (3) {}
        virtual ~TrinomialBranch () {}
        int children (int index ,int branch) const 
        {    return (k_[index] - Minimum()) - 1 + branch ;     } 
        
        double probability (int index ,int branch ) const 
        {    return probs[branch][index] ;    }
        
        int Minimum() const 
        {    return *std :: min_element (k.begin (), k.end ()) - 1 ;     }
        

private :
        std::vector <int > k_ ;
        friend class TrinomialTree ;
        std::vector <std::vector<double> > probs_;
} ;

class TrinomialTree : public Tree 
{
public :
        TrinomialTree ()    {}
        TrinomialTree (const Handle<DiffusionProcess>& process , const TimeGrid & timeGrid ,bool isPositive = false   );
        double dx (int i ) const {    return dx_[i];    }
        double underlying (int i ,int index ) const ;
        const TimeGrid & timeGrid () const {    return timeGrid_ ;    }
        inline int children (int i ,int index ,int branch) const 
        {    return branchings_ [i]-> children (index ,branch );     }
        inline double probability (int i ,int j ,int b ) const 
        {    return branchings_[i]-> probability (j , b );        }
        
        inline int size (int i )const 
        {
                if (i = = 0)     return  1;    
                const std ::vector <int >& k = branchings_[i -1 ]->k_ ;
                int Minimum = *std::min_element(k.begin(), k.end()) - 1;
                int Maximum = *std::max_element(k.begin(), k.end()) + 1;
                return Maximum - Minimum + 1;
        }

        double underlying (int i ,int index )const 
        {
                if (i ==0 )return x0_ ;
                const std ::vector <int >& k = branchings_[i -1 ]->k_ ;
                int Minimum = *std::min_element(k.begin(), k.end()) - 1;
                return x0_ + ( Minimum * 1.0+index *1.0)*dx(i) ; //?
        }
protected :
                std ::vector<Handle <TrinomialBranch>> branchings_ ;
                double x0_ ;
                std ::vector<double >  dx_ ;
                TimeGrid timeGrid_ ; 

} ;

using namespace Quantlib ::Lattices ;

// Cox-Ross Rubinstein Tree
// lambda = sqrt(3/2)
class CRRTrinomialTree : public TrinomialTree 
{
public:
      CRRTrinomialTree() {}
      CRRTrinomialTree(double initPrice, double strike, double vol,double rate,double div, double T,char type, char exercise,long N);
      double buildTrinomialTreeCRRAmerican(double price, double strike, double vol, double rate, double dividend, double T, long N, char type);
      double buildTrinomialTreeCRREuropean(double price, double strike, double vol, double rate, double dividend, double T, long N, char type);
private:
      double price_; 
      double sigma_;
      double mu_;
      double dt_;
     };

// Jarrow-Rudd binomial tree
// lambda = sqrt(3)
class JRTrinomialTree : public TrinomialTree 
{
public:
     JRTrinomialTree() {}
            JRTrinomialTree(double initPrice, double strike, double vol, double rate, double T,char type, char exercise, long N); 
            double buildTrinomialTreeJRAmerican(double price, double strike, double vol, double rate, double dividend, double T, long N, char type);
            double buildTrinomialTreeJREuropean(double price, double strike, double vol, double rate, double dividend, double T, long N, char type);
private:
            double price0_;
            double sigma_;
            double mu_;
            double dt_;
};

// lambda = 1
class GeneralTrinomialTree : public TrinomialTree
{
public:
            GeneralTrinomialTree() {}
            GeneralTrinomialTree(double initPrice, double strike, double vol, double rate, double T,char type, char exercise, long N); 
            double buildGeneralTrinomialAmerican(double price, double strike, double vol, double rate, double dividend, double T, long N, char type);
            double buildGeneralTrinomialEuropean(double price, double strike, double vol, double rate, double dividend, double T, long N, char type);
private:
            double price0_;
            double sigma_;
            double mu_;
            double dt_;
};
