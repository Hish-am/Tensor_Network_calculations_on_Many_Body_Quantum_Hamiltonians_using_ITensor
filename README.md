# Tensor_Network_calculations_on_Many_Body_Quantum_Hamiltonians_using_ITensor
Using the powerful ITesnor lib. to run Tensor Network operations including DMRG on a 20-spin chain (as an MPS) under the Heisenberg Hamiltonian (as an MPO) to extract ground state energy and von-Neumann entanglement entropy around an arbitrary bond position.

### A few tips on making your own model using I tensor:

I used the C++ version on Linux to install the library as a Makefile. Using the ITensor Library, a quick way to start is always to use one of their templates provided with the library and read the documentation to adjust the Makefile appropriately, it will generate the required  C++ file with the Itensor Library imported as a header file, and you can read the documentation to figure out all the functions and tailor your Hamiltonian for the model by constructing your operators accordingly and create an MPO (Matrix product Operator) from it; the many-body quantum system arrangment, for example spin model, chain or otherwise; set your DMRG goal, accuracy and sweeps; and finally specify the bond site to perform an SVD for extracting the Schmidt numbers and in turn be able to calculate the von Neumann entanglment entropy.


### some extra info:

1.The first code is for a very simple Singlet under the effect of the Heisenberg Hamiltonian, calculating its lowest energy is pretty straightforward and is given on running the code instantly  

2.The second code is for approximating the entanglment entropy of a 20-body spin chain also with the Hesenberg Hamiltonian  

![Hamiltonian MPO](https://github.com/Hish-am/Tensor_Network_calculations_on_Many_Body_Quantum_Hamiltonians_using_ITensor/blob/master/Heisenberg_Hamiltonian_as_an_MPO.png)  

The following illustration shows the steps taken by the code to first of all approximate the ground state using MPS based operations (basically DMRG) by turning the model into an MPS chain and adjusting the most critical eigenvalues to weigh which degrees of freedom it can keep each sweep. Finally we get the most important bond indices at every site to contribute to the approximated MPS, which closely approximates the exact original state with all its possible degrees of freedom. Finally we here take the 4th bond in the chain as the site of our bipartition, to divide the global system into a bipartite system for which we can calculate non Neumann entropy given we can direcly (that's thw whole point) apply SVD to the Approxiamte MPS we got from DMRG as long as its 2 partitions have orthogonal basis.Since the bond index in question was set by "Guaging" the MPS into a left canonical and right canonical MPS, and since only then is the left and right partitions of the MPS orthogonal, we can apply SVD and extract schmidt numbers accordingly. It is straight forward to apply von-Neumann entropy after that. The code outputs the diagonal matrix of the SVD, the reader is left to square it and get the entanglment entroppy as they see fit. The illustration and final calculation is given bellow.  
  
  
![Hamiltonian MPO](https://github.com/Hish-am/Tensor_Network_calculations_on_Many_Body_Quantum_Hamiltonians_using_ITensor/blob/master/Illustration_of_the_Tensor_Network_Operation.png)  
  
  
The final extraction of the von-Neumann entanglment entropy from the SVD  
  
  ![Hamiltonian MPO](https://github.com/Hish-am/Tensor_Network_calculations_on_Many_Body_Quantum_Hamiltonians_using_ITensor/blob/master/SVD_result_of_the_MPS_and_isolating_the_Singular_Values_for_vN_entropy_extraction.png)  
