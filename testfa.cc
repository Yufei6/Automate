#include <iostream>
#include <iomanip>
#include <fstream>

#include "gtest/gtest.h"

#include "Automaton.h"



class AutomatonTestFixture : public ::testing::Test{
protected:
    void SetUp() override{
        init();
        std::cout << "Foo FooEnvironment SetUP" << std::endl;
    }

    void init() {
        fa1.addState(1);
        fa1.addState(2);
    }

    fa::Automaton fa1;
};

// *********************************** Partie Yufei **************************

TEST_F(AutomatonTestFixture, TestduTest) {
    fa1.prettyPrint(std::cout);
}


TEST(AutomatonTest, Empty) {
  // AutomatonTest::fa1.prettyPrint(std::cout);
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(), 0u);
  EXPECT_EQ(fa.countTransitions(), 0u);
}



TEST(AutomatonTest, addStateOK1){
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

TEST(AutomatonTest, addStateKO1){
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(),0);
  fa.addState(-1);
  EXPECT_EQ(fa.countStates(),0);
  fa.addState(2);
  EXPECT_EQ(fa.countStates(),1);
  fa.addState(-3);
  EXPECT_EQ(fa.countStates(),1);
}


TEST(AutomatonTest, addStateKO2){
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_EQ(fa.countStates(),0);
  fa.addState(2);
  EXPECT_EQ(fa.countStates(),1);
  fa.addState(0);
  EXPECT_EQ(fa.countStates(),1);
}


// TEST(AutomatonTest, addStateKO3){
//   fa::Automaton fa;
//   fa.addState('p');
//   EXPECT_EQ(fa.countStates(),0);
//   fa.addState(2);
//   EXPECT_EQ(fa.countStates(),1);
//   fa.addState("Bonjour");
//   EXPECT_EQ(fa.countStates(),1);
// }
//
//
// TEST(AutomatonTest, addStateKO4){
//   fa::Automaton fa;
//   fa.addState(true);
//   EXPECT_EQ(fa.countStates(),0);
//   fa.addState(2);
//   EXPECT_EQ(fa.countStates(),1);
//   fa.addState(*);
//   EXPECT_EQ(fa.countStates(),1);
// }


TEST(AutomatonTest, removeStateOK1){
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(),0);
  fa.addState(1);
  EXPECT_EQ(fa.countStates(),1);
  fa.addState(2);
  EXPECT_EQ(fa.countStates(),2);
  fa.addState(3);
  EXPECT_EQ(fa.countStates(),3);
  fa.removeState(3);
  EXPECT_EQ(fa.countStates(),2);
  fa.removeState(3);
  EXPECT_EQ(fa.countStates(),2);
  fa.removeState('a');
  EXPECT_EQ(fa.countStates(),2);
}

TEST(AutomatonTest, removeStateKO1){
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(),0);
  fa.removeState(2);
  EXPECT_EQ(fa.countStates(),0);
  fa.removeState(4);
  EXPECT_EQ(fa.countStates(),0);
  fa.addState(3);
  EXPECT_EQ(fa.countStates(),1);
  fa.removeState(3);
  EXPECT_EQ(fa.countStates(),0);
  fa.removeState('a');
  EXPECT_EQ(fa.countStates(),0);
}



TEST(AutomatonTest, removeStateOKWithTranstion2){
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(),0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',4);

  EXPECT_EQ(fa.countTransitions(),3);
  ASSERT_TRUE(fa.hasTransition(1,'a',2));
  ASSERT_TRUE(fa.hasTransition(1,'b',3));
  ASSERT_TRUE(fa.hasTransition(2,'a',4));
  fa.removeState(5);
  EXPECT_EQ(fa.countTransitions(),3);
  ASSERT_TRUE(fa.hasTransition(1,'a',2));
  ASSERT_TRUE(fa.hasTransition(1,'b',3));
  ASSERT_TRUE(fa.hasTransition(2,'a',4));
  fa.removeState(1);
  EXPECT_EQ(fa.countTransitions(),1);
  ASSERT_FALSE(fa.hasTransition(1,'a',2));
  ASSERT_FALSE(fa.hasTransition(1,'b',3));
  ASSERT_TRUE(fa.hasTransition(2,'a',4));
  ASSERT_TRUE(fa.hasState(4));
  ASSERT_FALSE(fa.hasState(1));
  ASSERT_TRUE(fa.hasState(3));
  ASSERT_TRUE(fa.hasState(2));
  fa.removeState(4);
  EXPECT_EQ(fa.countTransitions(),0);
  EXPECT_EQ(fa.countStates(),2);
  ASSERT_FALSE(fa.hasTransition(2,'a',4));
  ASSERT_FALSE(fa.hasState(4));
  ASSERT_FALSE(fa.hasState(1));
  ASSERT_TRUE(fa.hasState(3));
  ASSERT_TRUE(fa.hasState(2));
}



TEST(AutomatonTest, removeStateOKWithTranstion3){
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(),0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',4);

  EXPECT_EQ(fa.countTransitions(),3);
  ASSERT_TRUE(fa.hasTransition(1,'a',2));
  ASSERT_TRUE(fa.hasTransition(1,'b',3));
  ASSERT_TRUE(fa.hasTransition(2,'a',4));
  fa.removeState(2);
  EXPECT_EQ(fa.countTransitions(),1);
  ASSERT_FALSE(fa.hasTransition(1,'a',2));
  ASSERT_TRUE(fa.hasTransition(1,'b',3));
  ASSERT_FALSE(fa.hasTransition(2,'a',4));
  EXPECT_EQ(fa.countStates(),3);
  fa.removeState(3);
  EXPECT_EQ(fa.countTransitions(),0);
  ASSERT_FALSE(fa.hasTransition(1,'a',2));
  ASSERT_FALSE(fa.hasTransition(1,'b',3));
  ASSERT_FALSE(fa.hasTransition(2,'a',4));
  EXPECT_EQ(fa.countStates(),2);
}

TEST(AutomatonTest, hasStateOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  ASSERT_TRUE(fa.hasState(1));
  ASSERT_TRUE(fa.hasState(2));
}

TEST(AutomatonTest, hasStateKO1){
  fa::Automaton fa;
  ASSERT_FALSE(fa.hasState(3));
  ASSERT_FALSE(fa.hasState(2));
  fa.addState(3);
  ASSERT_TRUE(fa.hasState(3));
  ASSERT_FALSE(fa.hasState(2));
}

TEST(AutomatonTest, setStateInitialOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  ASSERT_TRUE(fa.isStateInitial(1));
  fa.addState(2);
  fa.setStateInitial(2);
  ASSERT_TRUE(fa.isStateInitial(2));
}

TEST(AutomatonTest, setStateInitialKO1){
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(2);
  ASSERT_FALSE(fa.isStateInitial(2));
}

TEST(AutomatonTest, isStateInitialOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  ASSERT_TRUE(fa.isStateInitial(1));
}


TEST(AutomatonTest, isStateInitialKO1){
  fa::Automaton fa;
  fa.addState(2);
  ASSERT_FALSE(fa.isStateInitial(2));
}


TEST(AutomatonTest, isStateInitialKO2){
  fa::Automaton fa;
  ASSERT_FALSE(fa.isStateInitial(1));
}



TEST(AutomatonTest, setStateFinalOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(1);
  ASSERT_TRUE(fa.isStateFinal(1));
  fa.addState(2);
  fa.setStateFinal(2);
  ASSERT_TRUE(fa.isStateFinal(2));
}

TEST(AutomatonTest, setStateFinalKO1){
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(2);
  ASSERT_FALSE(fa.isStateFinal(2));
}

TEST(AutomatonTest, isStateFinalOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(1);
  ASSERT_TRUE(fa.isStateFinal(1));
}


TEST(AutomatonTest, isStateFinalKO1){
  fa::Automaton fa;
  fa.addState(2);
  ASSERT_FALSE(fa.isStateFinal(2));
}


TEST(AutomatonTest, isStateFinalKO2){
  fa::Automaton fa;
  ASSERT_FALSE(fa.isStateFinal(1));
}


TEST(AutomatonTest, addTransitionOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',3);
  EXPECT_EQ(2,fa.countTransitions());
  ASSERT_TRUE(fa.hasTransition(1,'a',2));
  ASSERT_TRUE(fa.hasTransition(2,'b',3));
  EXPECT_EQ(fa.getAlphabetSize(),2);
}


TEST(AutomatonTest, addTransitionOK2){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',3);
  EXPECT_EQ(2,fa.countTransitions());
  ASSERT_TRUE(fa.hasTransition(1,'a',2));
  ASSERT_TRUE(fa.hasTransition(2,'a',3));
  EXPECT_EQ(fa.getAlphabetSize(),1);
}


TEST(AutomatonTest, addTransitionKO1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addTransition(1,'a',2);
  EXPECT_EQ(0,fa.countTransitions());
  ASSERT_FALSE(fa.hasTransition(1,'a',2));
  EXPECT_EQ(fa.getAlphabetSize(),0);

}


TEST(AutomatonTest, addTransitionKO2){
  fa::Automaton fa;
  fa.addState(2);
  fa.addTransition(1,'a',2);
  EXPECT_EQ(0,fa.countTransitions());
  ASSERT_FALSE(fa.hasTransition(1,'a',2));
  EXPECT_EQ(fa.getAlphabetSize(),0);
}

TEST(AutomatonTest, addTransitionKO3){
  fa::Automaton fa;
  fa.addTransition(1,'a',2);
  EXPECT_EQ(0,fa.countTransitions());
  ASSERT_FALSE(fa.hasTransition(1,'a',2));
  EXPECT_EQ(fa.getAlphabetSize(),0);
}

TEST(AutomatonTest, removeTransitionOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  EXPECT_EQ(0,fa.countTransitions());
  EXPECT_EQ(fa.getAlphabetSize(),0);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',3);
  EXPECT_EQ(2,fa.countTransitions());
  EXPECT_EQ(fa.getAlphabetSize(),2);
  fa.removeTransition(1,'a',2);
  EXPECT_EQ(1,fa.countTransitions());
  EXPECT_EQ(fa.getAlphabetSize(),2);
  fa.removeTransition(2,'b',3);
  EXPECT_EQ(0,fa.countTransitions());
  EXPECT_EQ(fa.getAlphabetSize(),2);
}

TEST(AutomatonTest, removeTransitionKO1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  EXPECT_EQ(fa.getAlphabetSize(),0);
  fa.addTransition(1,'a',2);
  EXPECT_EQ(1,fa.countTransitions());
  fa.removeTransition(1,'b',2);
  EXPECT_EQ(1,fa.countTransitions());
  ASSERT_TRUE(fa.hasTransition(1,'a',2));
  EXPECT_EQ(fa.getAlphabetSize(),1);
}

TEST(AutomatonTest, removeTransitionKO2){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  EXPECT_EQ(fa.getAlphabetSize(),0);
  fa.addTransition(1,'a',2);
  EXPECT_EQ(1,fa.countTransitions());
  fa.removeTransition(3,'a',4);
  EXPECT_EQ(1,fa.countTransitions());
  ASSERT_TRUE(fa.hasTransition(1,'a',2));
  EXPECT_EQ(fa.getAlphabetSize(),1);
}



TEST(AutomatonTest, hasTransitionOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'a',2);
  ASSERT_TRUE(fa.hasTransition(1,'a',2));
}


TEST(AutomatonTest, hasTransitionKO1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'a',2);
  ASSERT_FALSE(fa.hasTransition(1,'a',3));
}


TEST(AutomatonTest, hasTransitionKO2){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'a',2);
  ASSERT_FALSE(fa.hasTransition(4,'a',2));
}


TEST(AutomatonTest, hasTransitionOK3){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'a',2);
  ASSERT_FALSE(fa.hasTransition(4,'a',3));
}

TEST(AutomatonTest, hasTransitionOK4){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  ASSERT_FALSE(fa.hasTransition(1,'a',2));
}


TEST(AutomatonTest, countTransitionsOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  EXPECT_EQ(0,fa.countTransitions());
  fa.addTransition(1,'a',2);
  EXPECT_EQ(1,fa.countTransitions());
  fa.addTransition(2,'b',3);
  EXPECT_EQ(2,fa.countTransitions());
  fa.addTransition(1,'a',2);
  EXPECT_EQ(2,fa.countTransitions());
  fa.addTransition(1,'b',3);
  EXPECT_EQ(3,fa.countTransitions());
}


TEST(AutomatonTest, getAlphabetSizeOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  EXPECT_EQ(0,fa.getAlphabetSize());
  fa.addTransition(1,'a',2);
  EXPECT_EQ(1,fa.getAlphabetSize());
  fa.addTransition(2,'b',3);
  EXPECT_EQ(2,fa.getAlphabetSize());
  fa.addTransition(1,'a',2);
  EXPECT_EQ(2,fa.getAlphabetSize());
  fa.addTransition(1,'b',3);
  EXPECT_EQ(2,fa.getAlphabetSize());
  fa.removeTransition(1,'a',2);
  fa.removeTransition(2,'b',3);
  fa.removeTransition(1,'b',3);
  EXPECT_EQ(2,fa.getAlphabetSize());
}


TEST(AutomatonTest, prettyPrintOK1){
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
}


TEST(AutomatonTest, dotPrintOK1){
  fa::Automaton automaton;
  std::ofstream fout("diagramme.dot");
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
  automaton.dotPrint(fout);
}


TEST(AutomatonTest, isDeterministicOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateFinal(2);
  fa.setStateInitial(1);
  fa.addTransition(1,'a',2);
  ASSERT_TRUE(fa.isDeterministic());
}


TEST(AutomatonTest, isDeterministicOK2){
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  ASSERT_TRUE(fa.isDeterministic());
}


TEST(AutomatonTest, isDeterministicOK3){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  ASSERT_TRUE(fa.isDeterministic());
}


TEST(AutomatonTest, isDeterministicOK4){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'\0',2);
  ASSERT_TRUE(fa.isDeterministic());
}

TEST(AutomatonTest, isDeterministicKO1){
  fa::Automaton fa;
  ASSERT_FALSE(fa.isDeterministic());
}


TEST(AutomatonTest, isDeterministicKO2){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  ASSERT_FALSE(fa.isDeterministic());
}

TEST(AutomatonTest, isDeterministicKO3){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  ASSERT_FALSE(fa.isDeterministic());
}


TEST(AutomatonTest, isDeterministicKO4){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateFinal(3);
  fa.setStateInitial(1);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'a',3);
  fa.addTransition(2,'b',3);
  ASSERT_FALSE(fa.isDeterministic());
}


TEST(AutomatonTest, isCompleteOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  ASSERT_TRUE(fa.isComplete());
}

TEST(AutomatonTest, isCompleteOK2){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',3);
  fa.addTransition(2,'b',3);
  fa.addTransition(3,'a',3);
  fa.addTransition(3,'b',3);
  ASSERT_TRUE(fa.isComplete());
}


TEST(AutomatonTest, isCOmpleteKO1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',3);
  fa.addTransition(2,'b',3);
  fa.addTransition(3,'a',3);
  ASSERT_FALSE(fa.isComplete());
}


TEST(AutomatonTest, makeCompleteOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',3);
  fa.addTransition(2,'b',3);
  fa.addTransition(3,'a',3);
  ASSERT_FALSE(fa.isComplete());
  fa.makeComplete();
  ASSERT_TRUE(fa.isComplete());
}


TEST(AutomatonTest, makeCompleteOK2){
  fa::Automaton fa;
  ASSERT_TRUE(fa.isComplete());
  fa.makeComplete();
  ASSERT_TRUE(fa.isComplete());
}


TEST(AutomatonTest, createProductOK1){
  fa::Automaton a1;
  a1.addState(1);
  a1.addState(2);
  a1.setStateFinal(2);
  a1.setStateInitial(1);
  a1.addTransition(1,'a',2);
  a1.addTransition(2,'b',2);
  a1.addTransition(2,'a',2);
  ASSERT_TRUE(a1.match("a"));
  ASSERT_TRUE(a1.match("aab"));
  ASSERT_TRUE(a1.match("aaaaaaaa"));
  ASSERT_TRUE(a1.match("abbbb"));
  ASSERT_TRUE(a1.match("abbababa"));

  fa::Automaton a2;
  a2.addState(3);
  a2.addState(4);
  a2.setStateFinal(4);
  a2.setStateInitial(3);
  a2.addTransition(3,'a',3);
  a2.addTransition(3,'b',4);
  a2.addTransition(4,'b',4);
  a2.addTransition(4,'a',3);
  ASSERT_TRUE(a2.match("b"));
  ASSERT_TRUE(a2.match("aaababab"));
  ASSERT_TRUE(a2.match("aaaaaaab"));
  ASSERT_TRUE(a2.match("bbbbbbbbb"));
  ASSERT_TRUE(a2.match("aabbbbbbbaab"));


  fa::Automaton a3;
  a3 = a3.createProduct(a1,a2);
  ASSERT_FALSE(a3.match("aaaaaaaa"));
  ASSERT_FALSE(a3.match("bbbbbbbbb"));
  ASSERT_TRUE(a2.match("ab"));
  ASSERT_TRUE(a2.match("aabababababab"));
  ASSERT_TRUE(a2.match("aaaaaaab"));
  ASSERT_TRUE(a2.match("abbbbbbbbb"));
  ASSERT_TRUE(a2.match("aabbbbbbbaab"));
}



TEST(AutomatonTest, createProductOK2){
  fa::Automaton a1;
  fa::Automaton a2;
  fa::Automaton a3;

  a1.addState(1);
  a1.addState(2);
  a1.setStateFinal(2);
  a1.setStateInitial(1);
  a1.addTransition(1,'a',2);
  a1.addTransition(2,'b',2);
  a1.addTransition(2,'a',2);
  ASSERT_TRUE(a1.match("a"));
  ASSERT_TRUE(a1.match("aab"));
  ASSERT_TRUE(a1.match("aaaaaaaa"));
  ASSERT_TRUE(a1.match("abbbb"));
  ASSERT_TRUE(a1.match("abbababa"));

  a2.addState(1);
  a2.addState(2);
  a2.setStateFinal(2);
  a2.setStateInitial(1);
  a2.addTransition(1,'a',2);
  a2.addTransition(2,'b',2);
  a2.addTransition(2,'a',2);
  ASSERT_TRUE(a2.match("a"));
  ASSERT_TRUE(a2.match("aab"));
  ASSERT_TRUE(a2.match("aaaaaaaa"));
  ASSERT_TRUE(a2.match("abbbb"));
  ASSERT_TRUE(a2.match("abbababa"));

  a3=a3.createProduct(a1,a2);
  ASSERT_TRUE(a1.match("a"));
  ASSERT_TRUE(a1.match("aab"));
  ASSERT_TRUE(a1.match("aaaaaaaa"));
  ASSERT_TRUE(a1.match("abbbb"));
  ASSERT_TRUE(a1.match("abbababa"));

}


TEST(AutomatonTest, createProductKO1){
  fa::Automaton a1;
  fa::Automaton a2;
  fa::Automaton a3;

  a1.addState(1);
  a1.addState(2);
  a1.setStateFinal(2);
  a1.setStateInitial(1);
  a1.addTransition(1,'a',2);
  a1.addTransition(2,'b',2);
  a1.addTransition(2,'a',2);
  ASSERT_TRUE(a1.match("a"));
  ASSERT_TRUE(a1.match("aab"));
  ASSERT_TRUE(a1.match("aaaaaaaa"));
  ASSERT_TRUE(a1.match("abbbb"));
  ASSERT_TRUE(a1.match("abbababa"));

  a2.addState(3);
  a2.addState(4);
  a2.setStateFinal(4);
  a2.setStateInitial(3);
  a2.addTransition(3,'b',4);
  a2.addTransition(4,'b',4);
  a2.addTransition(4,'a',3);
  ASSERT_TRUE(a2.match("b"));
  ASSERT_TRUE(a2.match("bab"));
  ASSERT_TRUE(a2.match("bb"));
  ASSERT_TRUE(a2.match("bbbbbbbbb"));
  ASSERT_TRUE(a2.match("bababab"));

  a3=a3.createProduct(a1,a2);
  ASSERT_FALSE(a3.match("a"));
  ASSERT_FALSE(a3.match("aab"));
  ASSERT_FALSE(a3.match("aaaaaaaa"));
  ASSERT_FALSE(a3.match("abbbb"));
  ASSERT_FALSE(a3.match("abbababa"));
  ASSERT_TRUE(a3.isLanguageEmpty());
}



TEST(AutomatonTest,hasEmptyIntersectionWithOK1){
    fa::Automaton a1;
    fa::Automaton a2;

    a1.addState(1);
    a1.addState(2);
    a1.setStateFinal(2);
    a1.setStateInitial(1);
    a1.addTransition(1,'a',2);
    a1.addTransition(2,'b',2);
    a1.addTransition(2,'a',2);
    ASSERT_TRUE(a1.match("a"));
    ASSERT_TRUE(a1.match("aab"));
    ASSERT_TRUE(a1.match("aaaaaaaa"));
    ASSERT_TRUE(a1.match("abbbb"));
    ASSERT_TRUE(a1.match("abbababa"));

    a2.addState(3);
    a2.addState(4);
    a2.setStateFinal(4);
    a2.setStateInitial(3);
    a2.addTransition(3,'b',4);
    a2.addTransition(4,'b',4);
    a2.addTransition(4,'a',3);
    ASSERT_TRUE(a2.match("b"));
    ASSERT_TRUE(a2.match("bab"));
    ASSERT_TRUE(a2.match("bb"));
    ASSERT_TRUE(a2.match("bbbbbbbbb"));
    ASSERT_TRUE(a2.match("bababab"));

    ASSERT_TRUE(a2.hasEmptyIntersectionWith(a1));
}


TEST(AutomatonTest,hasEmptyIntersectionWithKO1){
    fa::Automaton a1;
    fa::Automaton a2;

    a1.addState(1);
    a1.addState(2);
    a1.setStateFinal(2);
    a1.setStateInitial(1);
    a1.addTransition(1,'a',2);
    a1.addTransition(2,'b',2);
    a1.addTransition(2,'a',2);
    ASSERT_TRUE(a1.match("a"));
    ASSERT_TRUE(a1.match("aab"));
    ASSERT_TRUE(a1.match("aaaaaaaa"));
    ASSERT_TRUE(a1.match("abbbb"));
    ASSERT_TRUE(a1.match("abbababa"));

    a2.addState(3);
    a2.addState(4);
    a2.setStateFinal(4);
    a2.setStateInitial(3);
    a2.addTransition(3,'a',4);
    a2.addTransition(3,'b',4);
    a2.addTransition(4,'b',4);
    a2.addTransition(4,'a',3);
    ASSERT_TRUE(a2.match("b"));
    ASSERT_TRUE(a2.match("bab"));
    ASSERT_TRUE(a2.match("bb"));
    ASSERT_TRUE(a2.match("bbbbbbbbb"));
    ASSERT_TRUE(a2.match("bababab"));

    ASSERT_FALSE(a2.hasEmptyIntersectionWith(a1));
}


TEST(AutomatonTest,createMinimalMooreWithCompleAndDeterministOK1){
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
      ASSERT_TRUE(a1.match("aa"));
      ASSERT_TRUE(a1.match("aaa"));
      ASSERT_TRUE(a1.match("bb"));
      ASSERT_TRUE(a1.match("bbb"));
      ASSERT_TRUE(a1.match("aabababa"));
      ASSERT_TRUE(a1.match("aabababa"));
      ASSERT_TRUE(a1.match("bbbababa"));


      a2 = a2.createMinimalMoore(a1);
      ASSERT_TRUE(a2.match("aa"));
      ASSERT_TRUE(a2.match("aaa"));
      ASSERT_TRUE(a2.match("bb"));
      ASSERT_TRUE(a2.match("bbb"));
      ASSERT_TRUE(a2.match("aabababa"));
      ASSERT_TRUE(a2.match("aabababa"));
      ASSERT_TRUE(a2.match("bbbababa"));
      ASSERT_TRUE(a2.countStates()<=a1.countStates());
}


TEST(AutomatonTest,createMinimalMooreWithCompleNoDeterministeOK2){
      fa::Automaton a1,a2;
      a1.addState(1);
      a1.addState(2);
      a1.addState(3);
      a1.addState(4);
      a1.setStateInitial(1);
      a1.setStateFinal(4);
      a1.addTransition(1,'a',3);
      a1.addTransition(1,'a',4);
      a1.addTransition(1,'b',2);
      a1.addTransition(2,'a',4);
      a1.addTransition(2,'b',4);
      a1.addTransition(3,'a',4);
      a1.addTransition(3,'b',4);
      a1.addTransition(4,'a',4);
      a1.addTransition(4,'b',4);
      ASSERT_TRUE(a1.match("a"));
      ASSERT_TRUE(a1.match("aa"));
      ASSERT_TRUE(a1.match("aaa"));
      ASSERT_TRUE(a1.match("bb"));
      ASSERT_TRUE(a1.match("bbb"));
      ASSERT_TRUE(a1.match("aabababa"));
      ASSERT_TRUE(a1.match("aabababa"));
      ASSERT_TRUE(a1.match("bbbababa"));


      a2 = a2.createMinimalMoore(a1);
      ASSERT_TRUE(a2.match("a"));
      ASSERT_TRUE(a2.match("aa"));
      ASSERT_TRUE(a2.match("aaa"));
      ASSERT_TRUE(a2.match("bb"));
      ASSERT_TRUE(a2.match("bbb"));
      ASSERT_TRUE(a2.match("aabababa"));
      ASSERT_TRUE(a2.match("aabababa"));
      ASSERT_TRUE(a2.match("bbbababa"));
      ASSERT_TRUE(a2.countStates()<=a1.countStates());
}


TEST(AutomatonTest,createMinimalMooreWithNoCompleAndDeterministeOK2){
      fa::Automaton a1,a2;
      a1.addState(1);
      a1.addState(2);
      a1.addState(3);
      a1.addState(4);
      a1.setStateInitial(1);
      a1.setStateFinal(4);
      a1.addTransition(1,'a',3);
      a1.addTransition(2,'a',4);
      a1.addTransition(2,'b',4);
      a1.addTransition(3,'a',4);
      a1.addTransition(3,'b',4);
      a1.addTransition(4,'b',4);
      ASSERT_TRUE(a1.match("ab"));
      ASSERT_TRUE(a1.match("aa"));
      ASSERT_FALSE(a1.match("aaa"));
      ASSERT_FALSE(a1.match("aabababa"));
      ASSERT_TRUE(a1.match("aabbbb"));
      ASSERT_TRUE(a1.match("abbbbb"));


      a2 = a2.createMinimalMoore(a1);
      ASSERT_TRUE(a1.match("ab"));
      ASSERT_TRUE(a1.match("aa"));
      ASSERT_FALSE(a1.match("aaa"));
      ASSERT_FALSE(a1.match("aabababa"));
      ASSERT_TRUE(a1.match("aabbbb"));
      ASSERT_TRUE(a1.match("abbbbb"));
      ASSERT_TRUE(a2.countStates()<=a1.countStates());
}



TEST(AutomatonTest,createMinimalMooreWithNoCompleNoDeterministeOK3){
      fa::Automaton a1,a2;
      a1.addState(1);
      a1.addState(2);
      a1.addState(3);
      a1.addState(4);
      a1.setStateInitial(1);
      a1.setStateFinal(4);
      a1.addTransition(1,'a',3);
      a1.addTransition(1,'a',4);
      a1.addTransition(1,'b',2);
      a1.addTransition(2,'a',4);
      a1.addTransition(2,'b',4);
      a1.addTransition(3,'a',4);
      a1.addTransition(3,'b',4);
      a1.addTransition(4,'b',4);
      ASSERT_TRUE(a1.match("a"));
      ASSERT_TRUE(a1.match("ab"));
      ASSERT_TRUE(a1.match("aa"));
      ASSERT_TRUE(a1.match("bb"));
      ASSERT_FALSE(a1.match("aaa"));
      ASSERT_FALSE(a1.match("aabababa"));
      ASSERT_TRUE(a1.match("aabbbb"));
      ASSERT_TRUE(a1.match("abbbbb"));
      ASSERT_TRUE(a1.match("bab"));
      ASSERT_TRUE(a1.match("babbbbb"));
      ASSERT_TRUE(a1.match("bbbbbb"));
      ASSERT_TRUE(a1.match("bbb"));


      a2 = a2.createMinimalMoore(a1);
      ASSERT_TRUE(a1.match("a"));
      ASSERT_TRUE(a1.match("ab"));
      ASSERT_TRUE(a1.match("aa"));
      ASSERT_TRUE(a1.match("bb"));
      ASSERT_FALSE(a1.match("aaa"));
      ASSERT_FALSE(a1.match("aabababa"));
      ASSERT_TRUE(a1.match("aabbbb"));
      ASSERT_TRUE(a1.match("abbbbb"));
      ASSERT_TRUE(a1.match("bab"));
      ASSERT_TRUE(a1.match("babbbbb"));
      ASSERT_TRUE(a1.match("bbbbbb"));
      ASSERT_TRUE(a1.match("bbb"));
      ASSERT_TRUE(a2.countStates()<=a1.countStates());
}


TEST(AutomatonTest, createWithoutEpsilonOK1){
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
     ASSERT_TRUE(a1.match("a\0\0"));
     ASSERT_TRUE(a1.match("a\0\0c"));
     ASSERT_TRUE(a1.match("aaa\0\0c"));
     ASSERT_TRUE(a1.match("a\0b\0c"));
     ASSERT_TRUE(a1.match("aa\0bb\0ccc"));
     ASSERT_TRUE(a1.match("\0bbbbb\0cc"));
     ASSERT_TRUE(a1.match("\0b\0c"));
     ASSERT_TRUE(a1.match("\0b\0cccc"));

     a2 = a2.createWithoutEpsilon(a1);
     ASSERT_TRUE(a2.match("a"));
     ASSERT_TRUE(a2.match("ac"));
     ASSERT_TRUE(a2.match("aaac"));
     ASSERT_TRUE(a2.match("abc"));
     ASSERT_TRUE(a2.match("aabbccc"));
     ASSERT_TRUE(a2.match("bbbbbcc"));
     ASSERT_TRUE(a2.match("bc"));
     ASSERT_TRUE(a2.match("bcccc"));
}












// ************************ Partie Augustin ************************************
TEST(AutomatonTest, simpledetermine) {
    fa::Automaton s;
    s.addState(0);
    s.addState(1);
    s.addState(2);
    s.setStateInitial(0);
    s.setStateFinal(1);
    s.addTransition(0, 'a', 1);
    s.addTransition(0, 'a', 2);
    s.addTransition(2, 'b', 1);
    fa::Automaton d = fa::Automaton::createDeterministic(s);
    d.prettyPrint(std::cout);
}

TEST(AutomatonTest, isIncludedIn) {
    std::cout << "TestSpecial!" << std::endl;
    fa::Automaton a;
    a.addState(1);
    a.addState(2);
    a.addState(3);
    a.addTransition(1, 'a', 2);
    a.addTransition(2, 'b', 3);
    a.setStateInitial(1);
    a.setStateFinal(3);

    fa::Automaton b;
    b.addState(1);
    b.addState(2);
    b.addState(3);
    b.addTransition(1, 'a', 2);
    b.addTransition(2, 'b', 3);
    b.setStateInitial(1);
    b.setStateFinal(3);
    b.addTransition(1, 'c', 3);


    if (b.isIncludedIn(a)) {
        std::cout << "OK for isIncludedIn!" << std::endl;
    }
    else {
        std::cout << "KO for isIncludedIn..." << std::endl;
    }
}



TEST(AutomatonTest, determine) {
    fa::Automaton a;
    a.addState(0);
    a.addState(1);
    a.addState(2);
    a.addState(3);
    a.addState(4);
    a.setStateInitial(0);
    a.setStateFinal(4);
    a.addTransition(0, 'b', 1);
    a.addTransition(0, 'a', 2);
    a.addTransition(0, 'b', 2);
    a.addTransition(0, 'a', 3);
    a.addTransition(2, 'b', 1);
    a.addTransition(2, 'a', 2);
    a.addTransition(2, 'b', 2);
    a.addTransition(2, 'a', 3);
    a.addTransition(1, 'b', 4);
    a.addTransition(3, 'a', 4);
    a.addTransition(4, 'a', 4);
    a.addTransition(4, 'b', 4);
    fa::Automaton b = fa::Automaton::createDeterministic(a);
    if (b.match("abb")) {
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OK for match after make-determinist!" << std::endl;
    }
    else {
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> KO for match after make-determinist..." << std::endl;
    }
    b.prettyPrint(std::cout);
}
















// TEST(AutomatonTest, normal){
//   fa::Automaton automaton;
//
//   automaton.addState(0);
//   automaton.addState(1); // On ajoute l'état 1 à l'automate
//   automaton.addState(2); // ...
//   automaton.addState(3); // ...
//   automaton.removeState(1);
//   automaton.addState(1);
//   automaton.addState(4);
//   automaton.setStateInitial(0);
//   automaton.setStateInitial(1);
//   automaton.setStateFinal(1);
//   automaton.setStateFinal(4);
//
//   automaton.addTransition(1,'b',3);
//   automaton.addTransition(0,'a',1);
//   automaton.addTransition(0,'a',2);
//   automaton.addTransition(0,'a',3);
//   automaton.addTransition(2,'a',3);
//   automaton.addTransition(2,'b',4);
//   automaton.addTransition(3,'a',3);
//   automaton.addTransition(3,'b',4);
//   automaton.addTransition(4,'a',4);
//   automaton.addTransition(4,'a',4);
//
//   if (automaton.match("abaaaba")) {
//       std::cout << "OK for match! " << std::endl;
//   }
//   else {
//       std::cout << "KO for match :(" << std::endl;
//   }
//
//   automaton.prettyPrint(std::cout);
//   automaton.dotPrint(fout);
//   automaton.addTransition(4,'b',4);
//   automaton.prettyPrint(std::cout);
//
// }

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


// TEST(AutomatonTest, moore){
//   fa::Automaton a1,a2;
//   a1.addState(1);
//   a1.addState(2);
//   a1.addState(3);
//   a1.addState(4);
//   a1.setStateInitial(1);
//   a1.setStateFinal(4);
//   a1.addTransition(1,'a',3);
//   a1.addTransition(1,'b',2);
//   a1.addTransition(2,'a',4);
//   a1.addTransition(2,'b',4);
//   a1.addTransition(3,'a',4);
//   a1.addTransition(3,'b',4);
//   a1.addTransition(4,'a',4);
//   a1.addTransition(4,'b',4);
//   std::cout << "This is Moore a1! : " << std::endl;
//   a1.prettyPrint(std::cout);
//   a2 = a2.createMinimalMoore(a1);
//   std::cout << "This is Moore a2! : " << std::endl;
//   a2.prettyPrint(std::cout);
// }
//
// TEST(AutomatonTest, epsilon){
//   fa::Automaton a1,a2;
//   a1.addState(1);
//   a1.addState(2);
//   a1.addState(3);
//   a1.setStateFinal(3);
//   a1.setStateInitial(1);
//   a1.addTransition(1,'a',1);
//   a1.addTransition(1,'\0',2);
//   a1.addTransition(2,'b',2);
//   a1.addTransition(2,'\0',3);
//   a1.addTransition(3,'c',3);
//   std::cout << "This is Epsilon a1! : " << std::endl;
//   a1.prettyPrint(std::cout);
//   a2 = a2.createWithoutEpsilon(a1);
//   std::cout << "This is Epsilon a2! : " << std::endl;
//   a2.prettyPrint(std::cout);
//   a1.prettyPrint(std::cout);
// }
//
//
//
//
// TEST(AutomatonTest, read_words) {
//     fa::Automaton word_r;
//     word_r.addState(0);
//     word_r.addState(1);
//     word_r.addState(2);
//     word_r.addState(3);
//     word_r.setStateInitial(0);
//     word_r.setStateFinal(3);
//     word_r.addTransition(0, 'a', 1);
//     word_r.addTransition(0, 'a', 2);
//     word_r.addTransition(1, 'b', 3);
//     word_r.addTransition(2, 'b', 3);
//     std::set<int> traveled_states = word_r.readString("ab");
//     std::cout << "Traveled states to recognize ab : " << std::endl;
//     for (std::set<int>::iterator iter = traveled_states.begin(); iter != traveled_states.end(); iter++) {
//         std::cout << *iter << " ";
//     }
//     std::cout << std::endl;
// }
//
// TEST(AutomatonTest, read_words_loop) {
//     fa::Automaton word_r;
//     word_r.addState(0);
//     word_r.setStateInitial(0);
//     word_r.setStateFinal(0);
//     word_r.addTransition(0, 'a', 0);
//     std::set<int> traveled_states = word_r.readString("aaaa");
//     std::cout << "Traveled states to recognize aaaa : " << std::endl;
//     for (std::set<int>::iterator iter = traveled_states.begin(); iter != traveled_states.end(); iter++) {
//         std::cout << *iter << " ";
//     }
//     std::cout << std::endl;
// }

int main(int argc, char **argv) {
    // testing::AddGlobalTestEnvironment(new FooEnvironment);
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
