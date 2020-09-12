#include "itensor/all.h"

using namespace itensor;

int main()
    {

    /////////////////////// ~ PART 2~ /////////////////////////////////////
    /////////////////// SVD calculation and von Neumann////////////////////

    
// we construct a 20-body spin half chain, so 20=4 and specify that it's spin half
auto N = 20;
auto sites = SpinHalf(N);

//Here we initiate a Matrix Product Operator MPO

auto ampo = AutoMPO(sites);

/* Next we construct a sum of local operators for our local Hamiltoninan...
 ....in this case the Heisenberg Hamiltonian*/

for( auto j : range1(N-1) )
    {
    ampo += 0.5,"S+",j,"S-",j+1;
    ampo += 0.5,"S-",j,"S+",j+1;
    ampo +=     "Sz",j,"Sz",j+1;
    }

// we turn the Heisenberg Hamiltonian into an MPO

auto H = toMPO(ampo);

// we set all the initial states to UP, and the odd sites rewritten to down

auto state = InitState(sites,"Up");
for( auto n : range1(N) ) if( n%2==0 ) state.set(n,"Dn");


//we run DMRG to reach an approximate ground state `psi`
//number of sweeps is 5,the maximum bond dimension of every sweep is also set
//The truncation error cutoff is also set at a modest value here it's near exact

auto sweeps = Sweeps(5); 
sweeps.maxdim() = 10,9,8,7,6;
sweeps.cutoff() = 1E-10;

auto [energy,psi] = dmrg(H,randomMPS(state),sweeps,"Silent");

//Given an MPS called "psi" and can identify any of the (N-1) bonds "b"
//The von neumann entropy is measured across this bond b
auto b = 4;

//"Gauge" the MPS to site b, so we select the bond site.

psi.position(b); 

//SVD this wavefunction around the bond (b) to get the singular value spectrum

auto l = leftLinkIndex(psi,b);
auto s = siteIndex(psi,b);
auto [U,S,V] = svd(psi(b),{l,s});
auto u = commonIndex(U,S);


//Apply von Neumann formula using the singular values

Real SvN = 0.;
for(auto n : range1(dim(u)))
    {
    auto Sn = elt(S,n,n);
    auto p = sqr(Sn);
    /* we print the diagonal matrix to look at the singular values before we use them to 
    extract the entropy*/
    Print(p);
    if(p > 1E-12) SvN += -p*log(p);
    }

printfln("Across bond b=%d, SvN = %.10f",b,SvN);

         

    return 0;
    }
