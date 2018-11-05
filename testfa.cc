#include <iostream>
#include <iomanip>
#include <fstream>


#include "gtest/gtest.h"

#include "Automaton.h"

TEST(AutomatonTest, Empty) {
  fa::Automaton fa;

  EXPECT_EQ(fa.countStates(), 0u);
  EXPECT_EQ(fa.countTransitions(), 0u);
}

int main(int argc, char **argv) {
  	::testing::InitGoogleTest(&argc, argv);
  	std::ofstream fout("diagramme.dot");
  	std::ofstream fout2("diagramme2.dot");
  	std::ofstream fout3("diagramme3.dot");
    fa::Automaton automaton;


    automaton.addState(0);
    automaton.addState(1); // On ajoute l'état 1 à l'automate
    automaton.addState(2); // ...
    automaton.addState(3); // ...
    automaton.removeState(1);
    automaton.addState(1);
    automaton.addState(4);
    automaton.setStateInitial(0);
    automaton.setStateInitial(1);
    automaton.setStateFinal(1);
    automaton.setStateFinal(4);

    // Automaton se situe dans le namespace "fa", pour accéder à la classe Automaton et créer un objet "automaton" de type Automaton, on écrit donc :




    automaton.addTransition(1,'b',3);
    automaton.addTransition(0,'a',1);
    automaton.addTransition(0,'a',2);
    automaton.addTransition(0,'a',3);
    automaton.addTransition(2,'a',3);
    automaton.addTransition(2,'b',4);
    automaton.addTransition(3,'a',3);
    automaton.addTransition(3,'b',4);
    automaton.addTransition(4,'a',4);
    automaton.addTransition(4,'a',4);
    // transitions.removeTransition(4,'a',4);


    automaton.prettyPrint(std::cout);
    automaton.dotPrint(fout);

    automaton.addTransition(4,'b',4);
    automaton.prettyPrint(std::cout);


    if(automaton.isDeterministic()){
    	std::cout << "OK for Deterministic" << std::endl;
    }
    else{
    	std::cout << "KO for Deterministic" << std::endl;
    }

    if(automaton.isComplete()){
    	std::cout << "OK for Complete" << std::endl;
    }
    else{
    	std::cout << "KO for Complete" << std::endl;
    }

    automaton.makeComplete();
    automaton.prettyPrint(std::cout);
    automaton.dotPrint(fout2);
	if(automaton.isComplete()){
    	std::cout << "OK for Complete" << std::endl;
    }
    else{
    	std::cout << "KO for Complete" << std::endl;
    }

    automaton.makeComplement();
    automaton.dotPrint(fout3);
    automaton.prettyPrint(std::cout);
    if(automaton.isComplete()){
        std::cout << "OK for Complete" << std::endl;
    }
    else{
        std::cout << "KO for Complete" << std::endl;
    }



    // std::cout << "new------------------------------------------------------" << std::endl;
    // fa::Automaton automaton2;
    // automaton2 = automaton.createProduct(automaton, automaton);
    // automaton2.prettyPrint(std::cout);



  	return RUN_ALL_TESTS();
}
