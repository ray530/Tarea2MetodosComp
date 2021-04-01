#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <list>
using namespace std;

class MCIntegral{
    
    public:

    MCIntegral(){
    }
    double f(double r_, double theta_)
    {
        return exp(r_)*pow(r_,2)*sin(theta_);
    }
    double Integral(unsigned long int N_)
    {
        list <double> r;
        srand(static_cast<unsigned int>(clock()));
        for (int i=0; i < N_; i++) 
        {
            r.push_back(double(rand()) / (double(RAND_MAX) + 1.0));
        }

        list <double> theta;
        srand(static_cast<unsigned int>(clock()));
        for (int i=0; i < N_; i++) 
        {
            theta.push_back(double(rand())*0.5*M_PI / (double(RAND_MAX) + 1.0));
        }

        double theta_a = 0;
        double theta_b = 0.5*M_PI;
        
        double phi_a = 0;
        double phi_b = 2*M_PI;

        double peso = (theta_b-theta_a)*(phi_b-phi_a);
        double suma = 0;

        list<double>::iterator posr;
        posr = r.begin();
        list<double>::iterator postheta;
        postheta = theta.begin();

        while( posr != r.end() and postheta != theta.end())
        {
            double funcion = f(*posr,*postheta);
            
            suma = suma + funcion;
            
            posr++;
            postheta++;
        }

        double mean = suma/N_;
        return peso*mean;
    }
};

int main()
{
    int N=1000000;
    MCIntegral *integral = new MCIntegral();
    double I = integral->Integral(N);
    cout << "Con " << N << " puntos muestrales la integral da como resultado: " << I << endl;

    return 0;
}