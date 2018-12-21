#include <iostream>
#include <iomanip>
#include <fstream>

#include "gtest/gtest.h"

#include "Automaton.h"



class AutomatonTestFixture : public ::testing::Test{
protected:
    void SetUp() override{
        init();
        init_NonCoAccessibleStatesAndCoAccessibleStates();
        init_OnlyNonAccessibleStates();
        init_NonAccessibleStatesAndAccessibleStates();
        init_withLoop();
    }

    void init() {
        fa1.addState(1);
        fa1.addState(2);
    }

    fa::Automaton fa1;

    fa::Automaton OnlyNonAccessibleStates;
    fa::Automaton NonAccessibleStatesAndAccessibleStates;

    fa::Automaton NonCoAccessibleStatesAndCoAccessibleStates;

    fa::Automaton withLoop;

    void init_withLoop() {
        withLoop.addState(1);
        withLoop.addState(2);
        withLoop.addState(3);
        withLoop.addState(4);
        withLoop.setStateInitial(1);
        withLoop.setStateFinal(4);
        withLoop.addTransition(1,'a',2);
        withLoop.addTransition(2,'b',3);
        withLoop.addTransition(3,'c',2);
        withLoop.addTransition(3,'d',4);
    }

    void init_OnlyNonAccessibleStates() {
        OnlyNonAccessibleStates.addState(1);
        OnlyNonAccessibleStates.addState(2);
        OnlyNonAccessibleStates.addState(3);
        OnlyNonAccessibleStates.addState(4);
        OnlyNonAccessibleStates.setStateInitial(1);
        OnlyNonAccessibleStates.setStateFinal(4);
        OnlyNonAccessibleStates.addTransition(2,'a',3);
    }

    void init_NonAccessibleStatesAndAccessibleStates() {
        NonAccessibleStatesAndAccessibleStates.addState(1);
        NonAccessibleStatesAndAccessibleStates.addState(2);
        NonAccessibleStatesAndAccessibleStates.addState(3);
        NonAccessibleStatesAndAccessibleStates.setStateInitial(1);
        NonAccessibleStatesAndAccessibleStates.setStateFinal(3);
        NonAccessibleStatesAndAccessibleStates.addTransition(1, 'f', 3);
    }

    void init_NonCoAccessibleStatesAndCoAccessibleStates() {

        NonCoAccessibleStatesAndCoAccessibleStates.addState(1);
        NonCoAccessibleStatesAndCoAccessibleStates.addState(2);
        NonCoAccessibleStatesAndCoAccessibleStates.addState(3);
        NonCoAccessibleStatesAndCoAccessibleStates.addState(4);
        NonCoAccessibleStatesAndCoAccessibleStates.addState(5);
        NonCoAccessibleStatesAndCoAccessibleStates.setStateInitial(1);
        NonCoAccessibleStatesAndCoAccessibleStates.setStateFinal(5);
        NonCoAccessibleStatesAndCoAccessibleStates.addTransition(1,'a',2);
        NonCoAccessibleStatesAndCoAccessibleStates.addTransition(2,'b',3);
        NonCoAccessibleStatesAndCoAccessibleStates.addTransition(1,'a',4);
        NonCoAccessibleStatesAndCoAccessibleStates.addTransition(4,'c',5);
    }

};

// *********************************** Partie Yufei **************************


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
  fa.addState(-1);
  EXPECT_EQ(fa.countStates(),0);
  fa.addState(2);
  EXPECT_EQ(fa.countStates(),1);
  fa.addState(-1);
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

TEST(AutomatonTest, makeComplementOK1){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',3);
  fa.addTransition(3,'a',3);
  ASSERT_TRUE(fa.match("aaa"));
  ASSERT_TRUE(fa.match("aaaa"));
  ASSERT_TRUE(fa.match("aaaaa"));
  ASSERT_TRUE(fa.match("aa"));
  ASSERT_FALSE(fa.match("a"));
  ASSERT_TRUE(fa.isComplete());
  fa.makeComplement();
  ASSERT_TRUE(fa.isComplete());
  ASSERT_FALSE(fa.match("aaa"));
  ASSERT_FALSE(fa.match("aaaa"));
  ASSERT_FALSE(fa.match("aaaaa"));
  ASSERT_FALSE(fa.match("aa"));
  ASSERT_TRUE(fa.match("a"));
}

TEST(AutomatonTest, makeComplementOK2){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(2,'a',3);
  fa.addTransition(3,'a',3);
  fa.addTransition(3,'b',3);
  ASSERT_TRUE(fa.match("aaa"));
  ASSERT_TRUE(fa.match("aaaa"));
  ASSERT_TRUE(fa.match("aaaaa"));
  ASSERT_TRUE(fa.match("aa"));
  ASSERT_FALSE(fa.match("a"));
  ASSERT_TRUE(fa.match("aab"));
  ASSERT_TRUE(fa.match("aaaabb"));
  fa.makeComplement();
  ASSERT_FALSE(fa.match("aaa"));
  ASSERT_FALSE(fa.match("aaaa"));
  ASSERT_FALSE(fa.match("aaaaa"));
  ASSERT_FALSE(fa.match("aa"));
  ASSERT_TRUE(fa.match("a"));
  ASSERT_FALSE(fa.match("aab"));
  ASSERT_FALSE(fa.match("aaaabb"));
}



TEST(AutomatonTest, makeComplementOK3){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);
  fa.addTransition(3,'a',3);
  ASSERT_TRUE(fa.match("b"));
  ASSERT_TRUE(fa.match("baaaa"));
  ASSERT_TRUE(fa.match("aaa"));
  ASSERT_TRUE(fa.match("aaaa"));
  ASSERT_TRUE(fa.match("aaaaa"));
  ASSERT_TRUE(fa.match("aa"));
  ASSERT_FALSE(fa.match("a"));
  fa.makeComplement();
  ASSERT_TRUE(fa.isComplete());
  ASSERT_FALSE(fa.match("aaa"));
  ASSERT_FALSE(fa.match("aaaa"));
  ASSERT_FALSE(fa.match("aaaaa"));
  ASSERT_FALSE(fa.match("aa"));
  ASSERT_TRUE(fa.match("a"));
  ASSERT_FALSE(fa.match("b"));
  ASSERT_FALSE(fa.match("baaaa"));
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
  ASSERT_TRUE(a3.match("ab"));
  ASSERT_TRUE(a3.match("aabababababab"));
  ASSERT_TRUE(a3.match("aaaaaaab"));
  ASSERT_TRUE(a3.match("abbbbbbbbb"));
  ASSERT_TRUE(a3.match("aabbbbbbbaab"));
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
  ASSERT_TRUE(a3.match("a"));
  ASSERT_TRUE(a3.match("aab"));
  ASSERT_TRUE(a3.match("aaaaaaaa"));
  ASSERT_TRUE(a3.match("abbbb"));
  ASSERT_TRUE(a3.match("abbababa"));

}

TEST(AutomatonTest, createProductOK3){
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

  fa::Automaton a3;
  a3 = a3.createProduct(a1,a2);
  ASSERT_FALSE(a3.match("aaaaaaaa"));
  ASSERT_FALSE(a3.match("bbbbbbbbb"));
  ASSERT_FALSE(a3.match("ab"));
  ASSERT_FALSE(a3.match("aabababababab"));
  ASSERT_FALSE(a3.match("aaaaaaab"));
  ASSERT_FALSE(a3.match("abbbbbbbbb"));
  ASSERT_FALSE(a3.match("aabbbbbbbaab"));
}


TEST(AutomatonTest, createProductOK4){
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

  fa::Automaton a3;
  a3 = a3.createProduct(a2,a1);
  ASSERT_FALSE(a3.match("aaaaaaaa"));
  ASSERT_FALSE(a3.match("bbbbbbbbb"));
  ASSERT_FALSE(a3.match("ab"));
  ASSERT_FALSE(a3.match("aabababababab"));
  ASSERT_FALSE(a3.match("aaaaaaab"));
  ASSERT_FALSE(a3.match("abbbbbbbbb"));
  ASSERT_FALSE(a3.match("aabbbbbbbaab"));
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


TEST(AutomatonTest, createProductKO2){
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
  a2.addTransition(1,'c',2);
  a2.addTransition(2,'d',2);
  a2.addTransition(2,'c',2);
  ASSERT_TRUE(a2.match("c"));
  ASSERT_TRUE(a2.match("ccd"));
  ASSERT_TRUE(a2.match("cccccccc"));
  ASSERT_TRUE(a2.match("cdddd"));
  ASSERT_TRUE(a2.match("cddcdcdc"));

  a3=a3.createProduct(a1,a2);
  ASSERT_FALSE(a3.match("a"));
  ASSERT_FALSE(a3.match("aab"));
  ASSERT_FALSE(a3.match("aaaaaaaa"));
  ASSERT_FALSE(a3.match("abbbb"));
  ASSERT_FALSE(a3.match("abbababa"));
  ASSERT_FALSE(a3.match("c"));
  ASSERT_FALSE(a3.match("ccd"));
  ASSERT_FALSE(a3.match("cccccccc"));
  ASSERT_FALSE(a3.match("cdddd"));
  ASSERT_FALSE(a3.match("cddcdcdc"));
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


TEST(AutomatonTest,hasEmptyIntersectionWithOK2){
    fa::Automaton a1;
    fa::Automaton a2;
    ASSERT_TRUE(a2.hasEmptyIntersectionWith(a1));
}


TEST(AutomatonTest,hasEmptyIntersectionWithOK3){
    fa::Automaton a1;
    fa::Automaton a2;
    ASSERT_TRUE(a1.hasEmptyIntersectionWith(a2));
}

TEST(AutomatonTest,hasEmptyIntersectionWithOK4){
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
    ASSERT_TRUE(a2.hasEmptyIntersectionWith(a1));
}


TEST(AutomatonTest,hasEmptyIntersectionWithOK5){
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
    ASSERT_TRUE(a1.hasEmptyIntersectionWith(a2));
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
      fa::Automaton a1_deterministe = fa::Automaton::createDeterministic(a1);
      ASSERT_TRUE(a2.countStates()<=a1_deterministe.countStates());
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
      fa::Automaton a1_deterministe = fa::Automaton::createDeterministic(a1);
      ASSERT_TRUE(a2.countStates()<=a1_deterministe.countStates());
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
     ASSERT_TRUE(a1.match("a"));
     ASSERT_TRUE(a1.match("ac"));
     ASSERT_TRUE(a1.match("aaac"));
     ASSERT_TRUE(a1.match("abc"));
     ASSERT_TRUE(a1.match("aabbccc"));
     ASSERT_TRUE(a1.match("bbbbbcc"));
     ASSERT_TRUE(a1.match("bc"));
     ASSERT_TRUE(a1.match("bcccc"));


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


TEST(AutomatonTest, createWithoutEpsilonOK2){
     fa::Automaton a1,a2;
     a1.addState(1);
     a1.addState(2);
     a1.addState(3);
     a1.setStateFinal(3);
     a1.setStateInitial(1);
     a1.addTransition(1,'a',1);
     a1.addTransition(1,'b',2);
     a1.addTransition(2,'b',2);
     a1.addTransition(2,'a',3);
     a1.addTransition(3,'c',3);
     ASSERT_FALSE(a1.match("a"));
     ASSERT_FALSE(a1.match("ac"));
     ASSERT_FALSE(a1.match("aaac"));
     ASSERT_FALSE(a1.match("abc"));
     ASSERT_FALSE(a1.match("aabbccc"));
     ASSERT_FALSE(a1.match("bbbbbcc"));
     ASSERT_FALSE(a1.match("bc"));
     ASSERT_FALSE(a1.match("bcccc"));
     ASSERT_TRUE(a1.match("bac"));
     ASSERT_TRUE(a1.match("aaaabbbaccccc"));

     a2 = a2.createWithoutEpsilon(a1);
     ASSERT_FALSE(a2.match("a"));
     ASSERT_FALSE(a2.match("ac"));
     ASSERT_FALSE(a2.match("aaac"));
     ASSERT_FALSE(a2.match("abc"));
     ASSERT_FALSE(a2.match("aabbccc"));
     ASSERT_FALSE(a2.match("bbbbbcc"));
     ASSERT_FALSE(a2.match("bc"));
     ASSERT_FALSE(a2.match("bcccc"));
     ASSERT_TRUE(a2.match("bac"));
     ASSERT_TRUE(a2.match("aaaabbbaccccc"));
}

TEST(AutomatonTest, createWithoutEpsilonOK3){
     fa::Automaton a1,a2;
     a1.addState(1);
     a1.addState(2);
     a1.addState(3);
     a1.setStateFinal(3);
     a1.setStateInitial(1);
     a1.addTransition(1,'a',1);
     a1.addTransition(1,'b',2);
     a1.addTransition(2,'b',2);
     a1.addTransition(2,'\0',3);
     a1.addTransition(3,'c',3);
     ASSERT_TRUE(a1.match("b"));
     ASSERT_TRUE(a1.match("ab"));
     ASSERT_TRUE(a1.match("aabc"));
     ASSERT_TRUE(a1.match("abc"));
     ASSERT_TRUE(a1.match("aabbccc"));
     ASSERT_TRUE(a1.match("bbbbbcc"));
     ASSERT_TRUE(a1.match("bc"));
     ASSERT_TRUE(a1.match("bcccc"));


     a2 = a2.createWithoutEpsilon(a1);
     ASSERT_TRUE(a1.match("b"));
     ASSERT_TRUE(a1.match("ab"));
     ASSERT_TRUE(a1.match("aabc"));
     ASSERT_TRUE(a1.match("abc"));
     ASSERT_TRUE(a1.match("aabbccc"));
     ASSERT_TRUE(a1.match("bbbbbcc"));
     ASSERT_TRUE(a1.match("bc"));
     ASSERT_TRUE(a1.match("bcccc"));
}


// ******************************* Faut sortir en commentaire un fois fixer le bug ********************************
// TEST(AutomatonTest, createWithoutEpsilonOK4){
//      fa::Automaton a1,a2;
//      a1.addState(1);
//      a1.addState(2);
//      a1.addState(3);
//      a1.setStateFinal(3);
//      a1.setStateInitial(1);
//      a1.addTransition(1,'\0',1);
//      a1.addTransition(2,'\0',3);
//      ASSERT_TRUE(a1.match("a"));
//
//      a2 = a2.createWithoutEpsilon(a1);
//      ASSERT_FALSE(a2.match("a"));
// }
// ******************************* Faut sortir en commentaire un fois fixer le bug ********************************













// ************************ Partie Augustin ************************************

TEST(AutomatonTest, consomme) {
    fa::Automaton a;
    a.addState(1);
    a.addState(2);
    a.setStateInitial(1);
    a.setStateFinal(2);
    a.addTransition(1, '\0', 2);
    a.addTransition(2, 'a', 2);
    ASSERT_TRUE(a.match("a") && a.match("aa") && !a.match("b") && !a.match("ab") && !a.match("aba"));
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
    // if (b.match("abb")) {
    //     std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> OK for match after make-determinist!" << std::endl;
    // }
    // else {
    //     std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> KO for match after make-determinist..." << std::endl;
    // }
    // b.prettyPrint(std::cout);
}


/// [ isLanguageEmpty - Tests ] ///

TEST(AutomatonTest, empty_without_states) {
    fa::Automaton a;
    ASSERT_TRUE(a.isLanguageEmpty());
}

TEST(AutomatonTest, empty_without_initial) {
    fa::Automaton a;
    a.addState(1);
    a.setStateFinal(1);
    ASSERT_TRUE(a.isLanguageEmpty());
}

TEST(AutomatonTest, empty_without_final) {
    fa::Automaton a;
    a.addState(1);
    a.setStateInitial(1);
    ASSERT_TRUE(a.isLanguageEmpty());
}

TEST(AutomatonTest, empty_with_initial_and_final) {
    fa::Automaton a;
    a.addState(1);
    a.addState(2);
    a.addState(3);
    a.addTransition(1,'a',2);
    a.setStateInitial(1);
    a.setStateFinal(3);
    ASSERT_TRUE(a.isLanguageEmpty());
}

TEST(AutomatonTest, not_empty_with_one_state) {
    fa::Automaton a;
    a.addState(1);
    a.setStateInitial(1);
    a.setStateFinal(1);
    ASSERT_FALSE(a.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, not_empty_with_dead_ends) {
    ASSERT_FALSE(NonCoAccessibleStatesAndCoAccessibleStates.isLanguageEmpty());
}

TEST(AutomatonTest, not_empty_casual) {
    fa::Automaton a;
    a.addState(1);
    a.addState(2);
    a.setStateInitial(1);
    a.setStateFinal(2);
    a.addTransition(1,'b',2);
    ASSERT_FALSE(a.isLanguageEmpty());
}

/// [ removeNonAccessibleStates - Tests ] ///


    TEST(AutomatonTest, non_accessible_no_initial_state) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addTransition(1, 'c', 2);
        a.removeNonAccessibleStates();
        ASSERT_EQ(a.countStates(), 0);
    }

    TEST_F(AutomatonTestFixture, non_accessible_partially) {
        NonAccessibleStatesAndAccessibleStates.removeNonAccessibleStates();
        ASSERT_EQ(NonAccessibleStatesAndAccessibleStates.countStates(), 2);
        ASSERT_FALSE(NonAccessibleStatesAndAccessibleStates.hasState(2));
    }

    TEST_F(AutomatonTestFixture, non_accessible_only_initial) {
        OnlyNonAccessibleStates.removeNonAccessibleStates();
        ASSERT_EQ(OnlyNonAccessibleStates.countStates(), 1);
        ASSERT_TRUE(OnlyNonAccessibleStates.hasState(1));
    }

    TEST(AutomatonTest, all_accessible_one_state) {
        fa::Automaton a;
        a.addState(1);
        a.setStateInitial(1);
        a.setStateFinal(1);
        a.removeNonAccessibleStates();
        ASSERT_EQ(a.countStates(), 1);
    }

    TEST(AutomatonTest, non_accessible_multiple_initial_states) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.setStateInitial(1);
        a.setStateInitial(2);
        a.removeNonAccessibleStates();
        ASSERT_EQ(a.countStates(), 2);
    }

/// [ removeNonCoAccessibleStates - Tests ] ///

    TEST_F(AutomatonTestFixture, non_co_accessible_partially) {
        NonCoAccessibleStatesAndCoAccessibleStates.removeNonCoAccessibleStates();
        ASSERT_EQ(NonCoAccessibleStatesAndCoAccessibleStates.countStates(), 3);
    }

    TEST(AutomatonTest, non_co_accessible_no_final_state) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addTransition(1, 'c', 2);
        a.removeNonCoAccessibleStates();
        ASSERT_EQ(a.countStates(), 0);
    }

    TEST(AutomatonTest, non_co_accessible_only_final) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.setStateInitial(1);
        a.setStateFinal(3);
        a.addTransition(1,'a',2);
        a.removeNonCoAccessibleStates();
        ASSERT_EQ(a.countStates(), 1);
        ASSERT_TRUE(a.hasState(3));
    }

    TEST(AutomatonTest, all_co_accessible_one_state) {
        fa::Automaton a;
        a.addState(1);
        a.setStateInitial(1);
        a.setStateFinal(1);
        a.removeNonCoAccessibleStates();
        ASSERT_EQ(a.countStates(), 1);
    }

    TEST(AutomatonTest, non_co_accessible_multiple_final_states) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.setStateFinal(1);
        a.setStateFinal(2);
        a.removeNonCoAccessibleStates();
        ASSERT_EQ(a.countStates(), 2);
    }

/// [ readString - Tests ] ///

    TEST(AutomatonTest, readstring_normal) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.setStateInitial(1);
        a.setStateFinal(3);
        a.addTransition(1, 'a', 2);
        a.addTransition(2, 'b', 3);
        std::set<int> final = a.readString("ab");
        ASSERT_EQ(final.size(), 1);
        ASSERT_TRUE(final.find(3) != final.end());
        std::set<int> final_2 = a.readString("a");
        ASSERT_EQ(final_2.size(), 1);
        ASSERT_TRUE(final_2.find(2) != final_2.end());
        std::set<int> final_3 = a.readString("abc");
        ASSERT_EQ(final_3.size(), 0);
        std::set<int> final_4 = a.readString("");
        ASSERT_EQ(final_4.size(), 1);
        ASSERT_TRUE(final_4.find(1) != final_4.end());
        std::set<int> final_5 = a.readString("d");
        ASSERT_EQ(final_5.size(), 0);
    }

    TEST(AutomatonTest, readstring_multiple_ending) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.setStateInitial(1);
        a.addTransition(1, 'a', 2);
        a.addTransition(1, 'a', 3);
        std::set<int> final = a.readString("a");
        ASSERT_EQ(final.size(), 2);
        ASSERT_TRUE(final.find(2) != final.end());
        ASSERT_TRUE(final.find(3) != final.end());
    }

    TEST_F(AutomatonTestFixture, readstring_loop) {
        std::set<int> final = withLoop.readString("abcbcbcbcbcbcbc");
        ASSERT_EQ(final.size(), 1);
        ASSERT_TRUE(final.find(2) != final.end());
    }

    TEST(AutomatonTest, readstring_final_loop) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.setStateInitial(1);
        a.setStateFinal(2);
        a.addTransition(1, 'a', 2);
        a.addTransition(2, 'b', 2);
        std::set<int> final = a.readString("abbbbbb");
        ASSERT_EQ(final.size(), 1);
        ASSERT_TRUE(final.find(2) != final.end());
    }

    TEST(AutomatonTest, readstring_multiple_initial) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.addState(4);
        a.setStateInitial(1);
        a.setStateInitial(2);
        a.addTransition(1, 'b', 3);
        a.addTransition(2, 'b', 4);
        std::set<int> final = a.readString("b");
        ASSERT_EQ(final.size(), 2);
        ASSERT_TRUE(final.find(3) != final.end());
        ASSERT_TRUE(final.find(4) != final.end());
    }

    TEST(AutomatonTest, readstring_no_state) {
        fa::Automaton a;
        std::set<int> final = a.readString("a");
        ASSERT_EQ(final.size(), 0);
    }

    TEST(AutomatonTest, readstring_no_initial) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addTransition(1, 'a', 2);
        std::set<int> final = a.readString("a");
        ASSERT_EQ(final.size(), 0);
    }

/// [ match - Tests ] ///

    TEST(AutomatonTest, match_normal) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.setStateInitial(1);
        a.setStateFinal(3);
        a.addTransition(1, 'a', 2);
        a.addTransition(2, 'b', 3);
        ASSERT_TRUE(a.match("ab"));
        ASSERT_FALSE(a.match("a"));
        ASSERT_FALSE(a.match("abb"));
        ASSERT_FALSE(a.match(""));
        ASSERT_FALSE(a.match("f"));
    }

    TEST_F(AutomatonTestFixture, match_loop) {
        ASSERT_TRUE(withLoop.match("abd"));
        ASSERT_TRUE(withLoop.match("abcbd"));
        ASSERT_TRUE(withLoop.match("abcbcbd"));
        ASSERT_FALSE(withLoop.match("ab"));
        ASSERT_FALSE(withLoop.match("abc"));
        ASSERT_FALSE(withLoop.match("d"));
    }

    TEST(AutomatonTest, match_loop_one_state) {
        fa::Automaton a;
        a.addState(1);
        a.setStateInitial(1);
        a.setStateFinal(1);
        a.addTransition(1, 'a', 1);
        ASSERT_TRUE(a.match(""));
        ASSERT_TRUE(a.match("a"));
        ASSERT_TRUE(a.match("aa"));
        ASSERT_TRUE(a.match("aaaaa"));
        ASSERT_FALSE(a.match("d"));
    }

    TEST(AutomatonTest, match_with_epsilons) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.setStateInitial(1);
        a.setStateFinal(3);
        a.addTransition(1, 'a', 2);
        a.addTransition(2, 'b', 3);
        a.addTransition(3, 'c', 3);
        a.addTransition(1, '\0', 3);
        ASSERT_TRUE(a.match("abccc"));
        ASSERT_TRUE(a.match("cccc"));
        ASSERT_TRUE(a.match("c"));
        ASSERT_TRUE(a.match(""));
        ASSERT_FALSE(a.match("a"));
        //ASSERT_FALSE(a.match("\0"));
    }

    /// [ createDeterministic - Tests ] ///

    TEST(AutomatonTest, createdeterministic_normal) {
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
        a.addTransition(2, 'a', 2);
        a.addTransition(2, 'b', 2);
        a.addTransition(2, 'b', 1);
        a.addTransition(2, 'a', 3);
        a.addTransition(1, 'b', 4);
        a.addTransition(3, 'a', 4);
        a.addTransition(4, 'a', 4);
        a.addTransition(4, 'b', 4);
        ASSERT_FALSE(a.isDeterministic());
        fa::Automaton b = fa::Automaton::createDeterministic(a);
        ASSERT_TRUE(b.isDeterministic());
        ASSERT_TRUE(b.match("bb"));
        ASSERT_TRUE(b.match("bbaaabbbabbab"));
        ASSERT_TRUE(b.match("aa"));
        ASSERT_FALSE(b.match("b"));
        ASSERT_FALSE(b.match(""));
    }

    TEST(AutomatonTest, createdeterministic_multiple_initial) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.setStateInitial(1);
        a.setStateInitial(2);
        a.setStateFinal(3);
        a.addTransition(1, 'a', 3);
        a.addTransition(2, 'b', 3);
        ASSERT_FALSE(a.isDeterministic());
        fa::Automaton b = fa::Automaton::createDeterministic(a);
        ASSERT_TRUE(b.isDeterministic());
        ASSERT_EQ(b.getInitialStates().size(),1);
        ASSERT_TRUE(b.match("a") && b.match("b"));
    }

    TEST(AutomatonTest, createdeterministic_already_deterministic) {
        fa::Automaton a;
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.setStateInitial(1);
        a.setStateFinal(2);
        a.setStateFinal(3);
        a.addTransition(1,'a',2);
        a.addTransition(1,'b',3);
        ASSERT_TRUE(a.isDeterministic());
        fa::Automaton b = fa::Automaton::createDeterministic(a);
        ASSERT_TRUE(b.isDeterministic());
    }

    TEST(AutomatonTest, createdeterministic_complex) {
        fa::Automaton a;
        a.addState(0);
        a.addState(1);
        a.addState(2);
        a.addState(3);
        a.setStateInitial(0);
        a.setStateInitial(1);
        a.setStateFinal(2);
        a.addTransition(0,'a',1);
        a.addTransition(0,'a',2);
        a.addTransition(0,'a',3);
        a.addTransition(3,'b',2);
        a.addTransition(1,'c',3);
        ASSERT_FALSE(a.isDeterministic());
        fa::Automaton b = fa::Automaton::createDeterministic(a);
        ASSERT_TRUE(b.isDeterministic());
        ASSERT_TRUE(b.match("a") && b.match("ab") && b.match("acb") && b.match("cb"));
        ASSERT_FALSE(b.match("") || b.match("b") || b.match("c") || b.match("aa"));
    }

/// [ isIncludedIn - Tests ] ///

    // TEST(AutomatonTest, isincludedin_normal) {
    //     fa::Automaton a;
    //     a.addState(1);
    //     a.addState(2);
    //     a.addState(3);
    //     a.addTransition(1, 'a', 2);
    //     a.addTransition(2, 'b', 3);
    //     a.setStateInitial(1);
    //     a.setStateFinal(3);
    //
    //     fa::Automaton b;
    //     b.addState(1);
    //     b.addState(2);
    //     b.addState(3);
    //     b.addTransition(1, 'a', 2);
    //     b.addTransition(2, 'b', 3);
    //     b.setStateInitial(1);
    //     b.setStateFinal(3);
    //     b.addTransition(1, 'c', 3);
    //
    //     ASSERT_TRUE(b.isIncludedIn(a));
    // }
    //
    // TEST(AutomatonTest, isincludedin_identical) {
    //
    // }



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

TEST(AutomatonTest, removeNonCoAccessibleStates) {
    fa::Automaton non_co_acc;
    non_co_acc.addState(0);
    non_co_acc.addState(1);
    non_co_acc.addState(2);
    non_co_acc.addState(3);
    non_co_acc.addState(4);
    non_co_acc.addTransition(0,'b',1);
    non_co_acc.addTransition(1,'b',2);
    non_co_acc.addTransition(0,'b',3);
    non_co_acc.addTransition(3,'b',4);
    non_co_acc.setStateInitial(0);
    non_co_acc.setStateFinal(4);
    std::cout << "Before deleting non-co-acc : " << std::endl;
    non_co_acc.prettyPrint(std::cout);
    non_co_acc.removeNonCoAccessibleStates();
    std::cout << "After deleting non-co-acc : " << std::endl;
    non_co_acc.prettyPrint(std::cout);
}


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


}
