#include <iostream>
#include <iomanip>
#include <fstream>

#include "gtest/gtest.h"

#include "Automaton.h"


class testfa : public ::testing::Test {
  public:
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

TEST(AutomatonTest, addState){
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(),0);
  fa.addState(1);
  EXPECT_EQ(fa.countStates(),1);
  fa.addState(2);
  EXPECT_EQ(fa.countStates(),2);
  fa.addState(3);
  EXPECT_EQ(fa.countStates(),3);
  fa.addState(3);
  EXPECT_EQ(fa.countStates(),3);
  fa.addState(4);
  EXPECT_EQ(fa.countStates(),4);
  fa.addState(6);
  EXPECT_EQ(fa.countStates(),5);
  fa.addState(4);
  EXPECT_EQ(fa.countStates(),5);
}


TEST(AutomatonTest, removeState){
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(),0);
  fa.removeState(2);
  EXPECT_EQ(fa.countStates(),0);
  fa.addState(1);
  EXPECT_EQ(fa.countStates(),1);
  fa.addState(2);
  EXPECT_EQ(fa.countStates(),2);
  fa.addState(3);
  EXPECT_EQ(fa.countStates(),3);
  fa.removeState(4);
  EXPECT_EQ(fa.countStates(),3);
  fa.removeState(3);
  EXPECT_EQ(fa.countStates(),2);
  fa.removeState(3);
  EXPECT_EQ(fa.countStates(),2);

}


TEST(AutomatonTest, Empty) {
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(), 0u);
  EXPECT_EQ(fa.countTransitions(), 0u);
}

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

  if (automaton.match("abaaaba")) {
      std::cout << "OK for match! " << std::endl;
  }
  else {
      std::cout << "KO for match :(" << std::endl;
  }

  automaton.prettyPrint(std::cout);
  automaton.dotPrint(fout);
  automaton.addTransition(4,'b',4);
  automaton.prettyPrint(std::cout);

}

// TEST(AutomatonTest, removeNonCoAccessibleStates) {
//     fa::Automaton non_co_acc;
//     non_co_acc.addState(0);
//     non_co_acc.addState(1);
//     non_co_acc.addState(2);
//     non_co_acc.addState(3);
//     non_co_acc.addState(4);
//     non_co_acc.addTransition(0,'b',1);
//     non_co_acc.addTransition(1,'b',2);
//     non_co_acc.addTransition(0,'b',3);
//     non_co_acc.addTransition(3,'b',4);
//     non_co_acc.setStateInitial(0);
//     non_co_acc.setStateFinal(4);
//     std::cout << "Before deleting non-co-acc : " << std::endl;
//     non_co_acc.prettyPrint(std::cout);
//     non_co_acc.removeNonCoAccessibleStates();
//     std::cout << "After deleting non-co-acc : " << std::endl;
//     non_co_acc.prettyPrint(std::cout);
// }


TEST(AutomatonTest, moore){
  fa::Automaton a1,a2;
  a1.addState(1);
  a1.addState(2);
  a1.addState(3);
  a1.addState(4);
  a1.setStateInitial(1);
  a1.setStateFinal(4);
  a1.addTransition(1,'a',3);
  a1.addTransition(1,'b',2);
  a1.addTransition(2,'a',4);
  a1.addTransition(2,'b',4);
  a1.addTransition(3,'a',4);
  a1.addTransition(3,'b',4);
  a1.addTransition(4,'a',4);
  a1.addTransition(4,'b',4);
  std::cout << "This is Moore a1! : " << std::endl;
  a1.prettyPrint(std::cout);
  a2 = a2.createMinimalMoore(a1);
  std::cout << "This is Moore a2! : " << std::endl;
  a2.prettyPrint(std::cout);
}

TEST(AutomatonTest, epsilon){
  fa::Automaton a1,a2;
  a1.addState(1);
  a1.addState(2);
  a1.addState(3);
  a1.setStateFinal(3);
  a1.setStateInitial(1);
  a1.addTransition(1,'a',1);
  a1.addTransition(1,'\0',2);
  a1.addTransition(2,'b',2);
  a1.addTransition(2,'\0',3);
  a1.addTransition(3,'c',3);
  std::cout << "This is Epsilon a1! : " << std::endl;
  a1.prettyPrint(std::cout);
  a2 = a2.createWithoutEpsilon(a1);
  std::cout << "This is Epsilon a2! : " << std::endl;
  a2.prettyPrint(std::cout);
  a1.prettyPrint(std::cout);
}




TEST(AutomatonTest, read_words) {
    fa::Automaton word_r;
    word_r.addState(0);
    word_r.addState(1);
    word_r.addState(2);
    word_r.addState(3);
    word_r.setStateInitial(0);
    word_r.setStateInitial(3);
    word_r.setStateFinal(3);
    word_r.setStateFinal(0);
    word_r.addTransition(0, 'a', 1);
    word_r.addTransition(0, 'a', 2);
    word_r.addTransition(1, 'b', 3);
    word_r.addTransition(2, 'b', 3);
    word_r.addTransition(3, 'c', 0);
    if (word_r.match("")) {
        std::cout << "Recognized !" << std::endl;
    }
    else {
        std::cout << "Not recognized..." << std::endl;
    }
}

int main(int argc, char **argv) {
  	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();





    // Automaton se situe dans le namespace "fa", pour accéder à la classe Automaton et créer un objet "automaton" de type Automaton, on écrit donc :






    //non_accessible_states_automaton.dotPrint(fout_non_acc);





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
