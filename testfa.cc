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

    //std::cout << "hi" << std::endl;

    //TEMP : //
    // std::set<int> set = automaton.from(0);
    // std::set<int>::iterator it = set.begin();
    // std::cout << "hello" << std::endl;
    // while(it != set.end()) {
    //     std::cout << (*it) << std::endl;
    //     it++;
    // }
    //////////


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

    if(automaton.isLanguageEmpty()) {
        std::cout << "OK for IsLanguageEmpty" << std::endl;
    }
    else {
        std::cout << "KO for IsLanguageEmpty" << std::endl;
    }

    fa::Automaton empty_automaton;
    empty_automaton.addState(0);
    empty_automaton.addState(1);
    empty_automaton.addState(2);
    empty_automaton.setStateInitial(0);
    empty_automaton.setStateFinal(2);
    empty_automaton.addTransition(0, 'a', 1);

    if(empty_automaton.isLanguageEmpty()) {
        std::cout << "OK for IsLanguageEmpty" << std::endl;
    }
    else {
        std::cout << "KO for IsLanguageEmpty" << std::endl;
    }

    fa::Automaton non_accessible_states_automaton;
    non_accessible_states_automaton.addState(0);
    non_accessible_states_automaton.addState(1);
    non_accessible_states_automaton.addState(2);
    non_accessible_states_automaton.addState(3);
    non_accessible_states_automaton.addState(4);
    non_accessible_states_automaton.setStateInitial(0);
    non_accessible_states_automaton.addTransition(2, 'a', 3);
    non_accessible_states_automaton.addTransition(0, 'b', 4);
    non_accessible_states_automaton.setStateFinal(4);

    std::cout << "Before removing non-accessible states : " << std::endl;
    non_accessible_states_automaton.prettyPrint(std::cout);

    non_accessible_states_automaton.removeNonAccessibleStates();

    std::cout << "After removing non-accessible states : " << std::endl;
    non_accessible_states_automaton.prettyPrint(std::cout);



// Test Produit
    fa::Automaton a1;
    a1.addState(1);
    a1.addState(2);
    a1.setStateFinal(2);
    a1.setStateInitial(1);
    a1.addTransition(1,'a',2);
    a1.addTransition(2,'b',2);
    a1.addTransition(2,'a',2);
    a1.prettyPrint(std::cout);


    fa::Automaton a2;
    a2.addState(3);
    a2.addState(4);
    a2.setStateFinal(4);
    a2.setStateInitial(3);
    a2.addTransition(3,'a',3);
    a2.addTransition(3,'b',4);
    a2.addTransition(4,'b',4);
    a2.addTransition(4,'a',3);
    a2.prettyPrint(std::cout);

    fa::Automaton a3;
    a3 = a3.createProduct(a1,a2);
    a3.prettyPrint(std::cout);






  	return RUN_ALL_TESTS();
}
