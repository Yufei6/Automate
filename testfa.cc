#include <iostream>
#include <iomanip>
#include <fstream>

#include "gtest/gtest.h"

#include "Automaton.h"


class testfa : public ::testing::Test {
  protected:
    virtual void SetUp() {
      std::ofstream fout("diagramme.dot");
      std::ofstream fout2("diagramme2.dot");
      std::ofstream fout3("diagramme3.dot");
      std::ofstream fout_non_acc("diagramme_na.dot");
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

};


TEST(AutomatonTest, Empty) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(), 0u);
  EXPECT_EQ(fa.countTransitions(), 0u);
}

<<<<<<< HEAD
TEST(AutomatonTest, removeNonAccessibleStates) {
    fa::Automaton non_acc;
    non_acc.addState(0);
    non_acc.addState(1);
    non_acc.addState(2);
    non_acc.addState(3);
    non_acc.addState(4);
    non_acc.addTransition(0, 'a', 4);
    non_acc.addTransition(1, 'a', 2);
    non_acc.setStateFinal(4);
    non_acc.setStateInitial(0);

    std::cout << "Before removing non-acc" << std::endl;
    non_acc.prettyPrint(std::cout);
    non_acc.removeNonAccessibleStates();
    std::cout << "After removing non-acc" << std::endl;
    non_acc.prettyPrint(std::cout);
=======
TEST(AutomatonTest, normal){
  std::ofstream fout("diagramme.dot");
  std::ofstream fout2("diagramme2.dot");
  std::ofstream fout3("diagramme3.dot");
  std::ofstream fout_non_acc("diagramme_na.dot");

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
  automaton.prettyPrint(std::cout);
  automaton.dotPrint(fout);
  automaton.addTransition(4,'b',4);
  automaton.prettyPrint(std::cout);
>>>>>>> 59dd74a956338fb2df5f6d37c50d088807e58c6f
}

int main(int argc, char **argv) {
  	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();



    // Automaton se situe dans le namespace "fa", pour accéder à la classe Automaton et créer un objet "automaton" de type Automaton, on écrit donc :






<<<<<<< HEAD
    //non_accessible_states_automaton.dotPrint(fout_non_acc);
=======
>>>>>>> 59dd74a956338fb2df5f6d37c50d088807e58c6f





//     if(automaton.isDeterministic()){
//     	std::cout << "OK for Deterministic" << std::endl;
//     }
//     else{
//     	std::cout << "KO for Deterministic" << std::endl;
//     }
//
//     if(automaton.isComplete()){
//     	std::cout << "OK for Complete" << std::endl;
//     }
//     else{
//     	std::cout << "KO for Complete" << std::endl;
//     }
//
//     automaton.makeComplete();
//     automaton.prettyPrint(std::cout);
//     automaton.dotPrint(fout2);
// 	if(automaton.isComplete()){
//     	std::cout << "OK for Complete" << std::endl;
//     }
//     else{
//     	std::cout << "KO for Complete" << std::endl;
//     }
//
//     automaton.makeComplement();
//     automaton.dotPrint(fout3);
//     automaton.prettyPrint(std::cout);
//     if(automaton.isComplete()){
//         std::cout << "OK for Complete" << std::endl;
//     }
//     else{
//         std::cout << "KO for Complete" << std::endl;
//     }
//
//
//
//
// // Test Produit
//     fa::Automaton a1;
//     a1.addState(1);
//     a1.addState(2);
//     a1.setStateFinal(2);
//     a1.setStateInitial(1);
//     a1.addTransition(1,'a',2);
//     a1.addTransition(2,'b',2);
//     a1.addTransition(2,'a',2);
//     a1.prettyPrint(std::cout);
//
//
//     fa::Automaton a2;
//     a2.addState(3);
//     a2.addState(4);
//     a2.setStateFinal(4);
//     a2.setStateInitial(3);
//     a2.addTransition(3,'a',3);
//     a2.addTransition(3,'b',4);
//     a2.addTransition(4,'b',4);
//     a2.addTransition(4,'a',3);
//     a2.prettyPrint(std::cout);
//
//     fa::Automaton a3;
//     a3 = a3.createProduct(a1,a2);
//     a3.prettyPrint(std::cout);
//
//     if(!a1.hasEmptyIntersectionWith(a2)){
//         std::cout << "OK for Intersection" << std::endl;
//     }
//
//
//
//     non_accessible_states_automaton.dotPrint(fout_non_acc);
//
//     fa::Automaton zero_non_accessible;
//     zero_non_accessible.addState(0);
//     zero_non_accessible.addState(1);
//     zero_non_accessible.setStateInitial(1);
//     zero_non_accessible.setStateFinal(1);
//     if (zero_non_accessible.isLanguageEmpty()) {
//         std::cout << "Test islanguageEmptyInitialAndFinal : KO" << std::endl;
//     }
//     else {
//         std::cout << "Test islanguageEmptyInitialAndFinal : OK" << std::endl;
//     }
//     zero_non_accessible.removeNonAccessibleStates();
//     zero_non_accessible.prettyPrint(std::cout);
//
//
//
//
//   	return RUN_ALL_TESTS();
}
