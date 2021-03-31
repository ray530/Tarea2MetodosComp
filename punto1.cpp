#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <list>
#include <stdlib.h>
#include<fstream>
using namespace std;

class Random{

    private:

	unsigned long int a;
	unsigned long int c;
  	unsigned long int m;


	unsigned long int r;

	public:
		Random()
        {
            r=0;
        }
		Random(long int seed_, string method_)
        {
            r = seed_;
            if(method_=="drand48")
            {
                set_a_drand48();
                set_c_drand48();
                set_m_drand48();
            }
            else if(method_=="simple")
            {
                set_a_simple();
                set_c_simple();
                set_m_simple();
            }
            else
            {
                cout << "Generador no reconocido" << endl;
            }
        }
        ~Random(){

        }        
        void set_a_drand48()
        {
            a=0x5DEECE66D;
        }
        void set_c_drand48()
        {
            c=0xB;
        }
        void set_m_drand48()
        {
            m=pow(2,48);
        }
        void set_a_simple()
        {
            a=57;
        }
        void set_c_simple()
        {
            c=1;
        }
        void set_m_simple()
        {
            m=265;
        }

		void SetSeed(long int seed_)
        {
            r = seed_;
        }
		double rand(double A_, double B_)
        {
            return A_ + (B_-A_)*Random::rand();
        }
        double rand()
        {
            r = (a*r + c)%m;

	        return double(r)/double(m);	
        }
        double testMethod(int Npoints, int moment, int seed_, string method_)
        {
            Random *rand = new Random(seed_,method_);
            list <double> array;
            for (int i=0 ; i < Npoints ; i++)
            {
                array.push_back(rand->rand());
            }
            double ck = 0;
            list<double>::iterator pos;
            pos = array.begin();
            list<double>::iterator posk;
            posk = array.begin();
            for (int i=0 ; i < moment ; i++)
            {
                posk++;
            }
            
            while( pos != array.end() and posk != array.end())
            {
                ck = ck+((*pos)*(*posk));
                
                pos++;
                posk++;
            }
            return ck/Npoints;
        }
            
        

};

int main(){

    int moment_ = 20;
    int Npoints = 1000;
    long int seed = time(0);

    string method = "drand48";
    Random *r = new Random(seed,method);

    ofstream archivo;
    archivo.open ("drand48.dat");
	for(int i = 0; i < moment_; i++)
    {
        double drand48 = r->testMethod(Npoints,i+1,seed,method);
        archivo << drand48;
        archivo << "\n";
        cout << drand48 << endl;
    }
    
    archivo.close ();
	delete r;

    method = "simple";
    Random *r1 = new Random(seed,method);

    archivo.open ("simple.dat");
	for(int i = 0; i < moment_; i++)
    {
        double simple = r1->testMethod(Npoints,i+1,seed,method);
        archivo << simple;
        archivo << "\n";
        cout << simple << endl;
    }
    
    archivo.close ();
	delete r1;
	return 0;

}