#include <../inc/Particle.h>

void StartAnim(){

  std::cout<<"unset key"<<std::endl;
  std::cout<<"set xrange [-50:50]"<<std::endl;
  std::cout<<"set yrange [-50:50]"<<std::endl;
  std::cout<<"set size ratio -1"<<std::endl;
  std::cout<<"set parametric"<<std::endl;
  std::cout<<"set trange [0:7]"<<std::endl;
  std::cout<<"set isosamples 12"<<std::endl;

}

void StartLine(){
        std::cout <<"plot 0,0";
}

void EndLine(){
        std::cout<<std::endl;
}


int main(int argc, char *argv[]){



	// Evolucion 
	double deltat = 0.001;

	double tmax = std::stof(argv[1]);
	int it = 0;

        int films = 200000;

        
	int NParticles = 4;

	srand48(time(0));

	double time = 0.;

	Particle *AllParticles[NParticles];

	double masa=10/NParticles;
	double radio=4/NParticles;
	double p0=0;

	for(int i = 0; i< NParticles; i++){
		Particle *p = new Particle(2*drand48(),3*drand48(),-0.5*drand48(),0.5*drand48(),masa,radio,i);
		p->SetWallLimits(-50,50,-50,50);
		AllParticles[i] = p;
		p0 += p->calculateMomentum();
	}


	// Evolucion
	while (time < tmax){

        if(it%films == 0){
	StartAnim();
	StartLine();
	}

	for(int i = 0; i< NParticles; i++){
	 AllParticles[i]->ChangeWallLimits(deltat,-1.0,0.);
	}
	double pfx = 0;
	double pfy = 0;

	for(int i = 0; i< NParticles; i++){
		AllParticles[i]->Move(time,deltat,it);
		AllParticles[i]->CheckWallLimits();
	//AllParticles[0]->CheckCollision(AllParticles[1]);
	//AllParticles[1]->CheckCollision(AllParticles[0]);
		for(int j = 0; j< NParticles; j++)
		{

			if(i!=j) AllParticles[i]->CheckCollision(AllParticles[j]);
		}

		
	

	//p1->Move(time,deltat,it);
	//p1->CheckWallLimits();

        if(it%films == 0)
	{
	//p1->Print();
	
	AllParticles[i]->Print();
	//AllParticles[i]->Print1();
	}
	pfx += AllParticles[i]->getM()*AllParticles[i]->getVx();
	pfy += AllParticles[i]->getM()*AllParticles[i]->getVy();
	
	}

	double pf = sqrt(pow(pfx,2)+pow(pfy,2));
			
	//if(p0==pf) std::cout << "El momento se conserva. P0: " << p0 << " ,Pf: " << pf << std::endl;
	//else std::cout << "El momento no se conserva. P0: " << p0 << " ,Pf: " << pf << std::endl;
	time += deltat;
	it ++;
        if(it%films == 0)	
	EndLine();
	}

	return 0;
}	
