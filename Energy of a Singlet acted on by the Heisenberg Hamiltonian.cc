
#include "itensor/all.h"

using namespace itensor;

/////////////////////// ~ PART 1~ /////////////////////////////////////
//////////// The singlet state and the Heisenberg model ///////////////

ITensor
// making the operators for the Hysenberg Model, the S1_z,S2_z, and the S+ and S-
makeSp(Index const& s)
    {
    auto Sp = ITensor(s,prime(s));
    Sp.set(s=2,prime(s)=1, 1);
    return Sp;
    }

ITensor
makeSm(Index const& s)
    {
    auto Sm = ITensor(s,prime(s));
    Sm.set(s=1,prime(s)=2,1);
    return Sm;
    }

ITensor
makeSz(Index const& s)
    {
    auto Sz = ITensor(s,prime(s));
    Sz.set(s=1,prime(s)=1,+0.5);
    Sz.set(s=2,prime(s)=2,-0.5);
    return Sz;
    }


int main()
    {

    // Initial product state of the most general two site wavefunction
    

    // Building the two physical indices sticking out of the tensor

    //defining the two physical indices individually as s1 and s2

    auto s1 = Index(2,"s1");
    auto s2 = Index(2,"s2");
    

    //combining the two physical indices into one big tensor

    auto psi = ITensor(s1,s2);

    //making a singlet state, one of the most common two site states

    psi.set(s1(1),s2(2),+1./sqrt(2));
    psi.set(s1(2),s2(1),-1./sqrt(2));


    PrintData(psi);

    
    /*defining the Single-site local operators using the operators we ..
    ..made before the main function for the Heisenberg model*/
    
    auto Sz1 = makeSz(s1);
    auto Sz2 = makeSz(s2);
    auto Sp1 = makeSp(s1);
    auto Sp2 = makeSp(s2);
    auto Sm1 = makeSm(s1);
    auto Sm2 = makeSm(s2);

    
    /* Using a sum of local spin operators to...
    .. construct a Two-site Heisenberg Hamiltonian */
    
    auto H = Sz1*Sz2 + 0.5*Sp1*Sm2 + 0.5*Sm1*Sp2;

    // Initial energy expectation value

    auto initEn = elt(dag(prime(psi)) * H * psi);
    printfln("\nInitial energy = %.10f",initEn);


    
    return 0;
    }
