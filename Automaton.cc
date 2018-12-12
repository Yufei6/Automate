#include "Automaton.h"

#include <cassert>


namespace fa {
	// Complexity: O(log n)
  	void fa::Automaton::addState(int state){
      if(state>0){
	    // Ici, on écrit le code pour ajouter un état à l'automate
	    // La méthode "addState" doit naturellement ajouter un état à l'automate
	    // On ajoute donc l'état "state" à l'ensemble des états de l'automate (donc à l'attribut "states"):
	       states.insert(state);
       }
	    // Pour débugger plus facilement, vous pouvez afficher le nombre d'états dans l'automate après insertion :
	    // std::cout << "Après insertion de l'état " << state << ", l'automate possède " << states.size() << " état(s)." << std::endl;
	}


	// Complexity: O(log n)
	void fa::Automaton::removeState(int state){
        if(state > 0){
    		states.erase(state);
            std::set<struct trans>::iterator iter = transitions.begin();
            while(iter != transitions.end()){
                if (((*iter).from == state) || (*iter).to == state) {
                    iter = transitions.erase(iter);
                }
                else{
                    iter ++;
                }
            }
        }
		// std::cout << "Après suppression de l'état " << state << ", l'automate possède " << states.size() << " état(s)." << std::endl;

	}


	// Complexity: O(log n)
	bool fa::Automaton::hasState(int state) const{
        if(state < 0){
            return false;
        }
        std::set<int>::iterator iter;
        iter=states.find(state);
        if(iter!=states.end()){
            return true;
        }
        else{
            return false;
        }
	}


	// Complexity: O(1)
	std::size_t fa::Automaton::countStates() const{
		return states.size();
	}


	// Complexity: O(log n)
	void fa::Automaton::setStateInitial(int state){
        if(state > 0){
            if(hasState(state)){
        		initialStates.insert(state);
            }
        }
		// std::cout << "Set initial state: " << state << "!!" <<std::endl;
	}


	// Complexity: O(log n)
	bool fa::Automaton::isStateInitial(int state) const{
        if(state < 0){
            return false;
        }
		std::set<int>::iterator iter;
		iter=initialStates.find(state);
		return iter!=initialStates.end();
	}


	// Complexity: O(log n)
	void fa::Automaton::setStateFinal(int state){
        if(state > 0){
            if(hasState(state)){
        		finalStates.insert(state);
            }
        }
		// std::cout << "Set final state: " << state << "!!" <<std::endl;

	}

	// Complexity: O(log n)
	bool fa::Automaton::isStateFinal(int state) const{
        if(state < 0){
            return false;
        }
		std::set<int>::iterator iter;
		iter=finalStates.find(state);
		return iter!=finalStates.end();
	}



    bool fa::trans::operator<(const trans& other) const {
        return std::tie(from, to, alpha) < std::tie(other.from, other.to, other.alpha);
    }


    // Complexity: O
	void fa::Automaton::addTransition(int from, char alpha, int to){
        if(hasState(from) && hasState(to)){
      		alphabets.insert(alpha);
      		if(!hasTransition(from, alpha, to)){
          	struct trans new_transition;
          	new_transition.from = from;
          	new_transition.alpha = alpha;
          	new_transition.to = to;
          	transitions.insert(new_transition);
      		}
        }
	}


	// Complexity:
	void fa::Automaton::removeTransition(int from, char alpha, int to){
        trans trans_to_delete;
        trans_to_delete.from = from;
        trans_to_delete.to = to;
        trans_to_delete.alpha = alpha;
 		transitions.erase(trans_to_delete);
	}



	bool fa::Automaton::hasTransition(int from, char alpha, int to) const{
        if(!hasState(from) || !hasState(to)){
          return false;
        }
        trans trans_to_search;
        trans_to_search.from = from;
        trans_to_search.to = to;
        trans_to_search.alpha = alpha;
        return transitions.find(trans_to_search) != transitions.end() ;
	}


	std::size_t fa::Automaton::countTransitions() const{
		return transitions.size();
	}





	std::size_t fa::Automaton::getAlphabetSize() const{
		return alphabets.size();
	}



	void fa::Automaton::prettyPrint(std::ostream& os) const{
		os << "Initial states: " << std::endl;
		std::set<int>::iterator iter_init_state;
		iter_init_state=initialStates.begin();
		while(iter_init_state != initialStates.end()){
			os << " " << *iter_init_state << " ";
			iter_init_state++;
		}
		os << std::endl;

		os << "Final states: " << std::endl;
		std::set<int>::iterator iter_final_state;
		iter_final_state=finalStates.begin();
		while(iter_final_state != finalStates.end()){
			os << " " << *iter_final_state << " ";
			iter_final_state++;
		}
		os << std::endl;

		os << "Transitions: " << std::endl;
		std::set<int>::iterator iter_all_state;
		iter_all_state=states.begin();
		while(iter_all_state != states.end()){
			os << "	For state " << *iter_all_state << ":" <<std::endl;
			std::set<char>::iterator iter_alpha=alphabets.begin();
			while(iter_alpha != alphabets.end()){
				os << "		For letter  " << *iter_alpha << " : ";
				std::set<struct trans>::iterator iter_trans;
				iter_trans = transitions.begin();
				while(iter_trans != transitions.end()){
					if(((*iter_trans).from==*iter_all_state) && ((*iter_trans).alpha==*iter_alpha)){
						os<< (*iter_trans).to <<" ";
					}
					iter_trans++;
				}
				os<< std::endl;
				iter_alpha++;
			}
			iter_all_state++;
		}
	}




//  Commande:            dot diagramme.dot -T png -o diagramme.png
	void fa::Automaton::dotPrint(std::ostream& os) const{
		os << "digraph automaton {" << std::endl ;
		os << "size = \"8.5, 11\";" << std::endl ;
		os << "fontsize = 10;" << std::endl ;

		std::set<int>::iterator iter_init_state;
		iter_init_state=initialStates.begin();
		while(iter_init_state != initialStates.end()){
			os << *iter_init_state << "[ style = filled, color=lightgrey ];" << std::endl;
			iter_init_state++;
		}


		std::set<int>::iterator iter_final_state;
		iter_final_state=finalStates.begin();
		while(iter_final_state != finalStates.end()){
			os <<  *iter_final_state << "[ shape = doublecircle ];" << std::endl;
			iter_final_state++;
		}

		std::set<int>::iterator iter_all_state;
		iter_all_state=states.begin();
		while(iter_all_state != states.end()){
			std::set<char>::iterator iter_alpha=alphabets.begin();
			while(iter_alpha != alphabets.end()){
				std::set<struct trans>::iterator iter_trans;
				iter_trans = transitions.begin();
				while(iter_trans != transitions.end()){
					if(((*iter_trans).from==*iter_all_state) && ((*iter_trans).alpha==*iter_alpha)){
						os<< (*iter_trans).from << "->" <<  (*iter_trans).to << " [ label = \"" << (*iter_trans).alpha << "\" ]; " <<std::endl;
					}
					iter_trans++;
				}
				os<< std::endl;
				iter_alpha++;
			}
			iter_all_state++;
		}
		os << "}" << std::endl ;

	}


      bool fa::Automaton::haveAndOnlyHaveOneStateInitial() const{
        int nbStateInitial = 0;
        std::set<int>::iterator initStates_it = initialStates.begin();
        while(initStates_it != initialStates.end()){
          if(isStateInitial(*initStates_it)){
            nbStateInitial++;
          }
          initStates_it++;
        }
        return nbStateInitial == 1;
    }


	bool fa::Automaton::isDeterministic() const{
        if(countStates()<1 || !haveAndOnlyHaveOneStateInitial()){
          return false;
        }
		std::set<int>::iterator iter_all_state;
		iter_all_state=states.begin();
		int count_to=0;
		while(iter_all_state != states.end()){
			if(!isStateFinal(*iter_all_state)){
				std::set<char>::iterator iter_alpha=alphabets.begin();
				while(iter_alpha != alphabets.end()){
					std::set<struct trans>::iterator iter_trans;
					iter_trans = transitions.begin();
					while(iter_trans != transitions.end()){
						if(((*iter_trans).from==*iter_all_state) && ((*iter_trans).alpha==*iter_alpha)){
							count_to++;
						}
						iter_trans++;
					}
					if(count_to > 1){
						return false;
					}
					iter_alpha++;
					count_to=0;
				}
			}
            iter_all_state++;
	  }
		return true;
	}

	bool fa::Automaton::isComplete() const{
		std::set<int>::iterator iter_all_state;
		iter_all_state=states.begin();
		int count_to=0;
		while(iter_all_state != states.end()){
			std::set<char>::iterator iter_alpha=alphabets.begin();
			while(iter_alpha != alphabets.end()){
				std::set<struct trans>::iterator iter_trans;
				iter_trans = transitions.begin();
				while(iter_trans != transitions.end()){
					if(((*iter_trans).from==*iter_all_state) && ((*iter_trans).alpha==*iter_alpha)){
						count_to++;
					}
					iter_trans++;
				}
				if(count_to == 0 ){
					return false;
				}
				iter_alpha++;
				count_to=0;
			}
			iter_all_state++;
		}
		return true;
	}



	void fa::Automaton::makeComplete(){
		int garbage_state=-1;
		while(garbage_state==-1){
			int temp=getTheBiggestState()+1;
			if(!hasState(temp)){
				garbage_state=temp;
			}
		}

		std::set<int>::iterator iter_all_state;
		iter_all_state=states.begin();
		int count_to=0;
		while(iter_all_state != states.end()){
			std::set<char>::iterator iter_alpha=alphabets.begin();
			while(iter_alpha != alphabets.end()){
				std::set<struct trans>::iterator iter_trans;
				iter_trans = transitions.begin();
				while(iter_trans != transitions.end()){
					if(((*iter_trans).from==*iter_all_state) && ((*iter_trans).alpha==*iter_alpha)){
						count_to++;
					}
					iter_trans++;
				}
				if(count_to ==0){
          addState(garbage_state);
					addTransition(*iter_all_state, *iter_alpha, garbage_state);
				}
				iter_alpha++;
				count_to=0;
			}
			iter_all_state++;
		}


	}


	// Complexity:
	void fa::Automaton::makeComplement(){
    if(!isComplete()){
      makeComplete();
    }
    // if(!Deterministic()){
    //   this=createDeterministic(this);
    // }
		std::set<int>::iterator iter=states.begin();
		while(iter != states.end()){
			if(isStateFinal(*iter)){
				finalStates.erase(*iter);
			}
			else{
				finalStates.insert(*iter);
			}
			iter++ ;
		}
	}



//********************************************* TP4 ***************************************************
	Automaton fa::Automaton::createProduct(const Automaton& lhs, const Automaton& rhs){
		fa::Automaton new_automaton;
		std::set<int> lhs_init=lhs.getInitialStates();
		std::set<int> rhs_init=rhs.getInitialStates();
		std::set<int>::iterator left_initStates = lhs_init.begin();
		std::set<int>::iterator right_initStates = rhs_init.begin();



		std::size_t n2 = rhs.getTheBiggestState() + 1;


		//create init states
		while(left_initStates != lhs_init.end()){
			while(right_initStates != rhs_init.end()){
                new_automaton.addState((*left_initStates * n2) + (*right_initStates));
				new_automaton.setStateInitial((*left_initStates * n2) + (*right_initStates));
				right_initStates++;
			}
			left_initStates++;
		}

		//create les alphabets communes
		std::set<char> s3 ;
   		std::set<char>::iterator iter = s3.begin() ;
   		set_intersection(lhs.alphabets.begin(),lhs.alphabets.end(),rhs.alphabets.begin(),rhs.alphabets.end(),inserter(s3,iter));
   		new_automaton.alphabets=s3;
		// create transitions
		std::set<int>::iterator iter_new_States=new_automaton.states.begin();
		while(iter_new_States!= new_automaton.states.end()){
			std::set<char>::iterator iter_alpha=new_automaton.alphabets.begin();
			while(iter_alpha != new_automaton.alphabets.end()){
				int s1 = *iter_new_States/n2;
				int s2 = *iter_new_States%n2;
				int res_l = lhs.getToWithFromAndAlpha(s1,*iter_alpha);
				int res_r = rhs.getToWithFromAndAlpha(s2,*iter_alpha);

				if( res_l ==0 || res_r ==0){
					iter_alpha++;
				}
				else{
					int new_state = (res_l * n2) + res_r;
					if (!new_automaton.hasState(new_state)){
						new_automaton.addState(new_state);
						new_automaton.addTransition(*iter_new_States, *iter_alpha, new_state);

						if(lhs.isStateFinal(res_l) && rhs.isStateFinal(res_r)){
							new_automaton.setStateFinal(new_state);
						}
					}
					new_automaton.addTransition(*iter_new_States, *iter_alpha, new_state);
					iter_alpha++;
				}
			}
			iter_new_States++;
		}
		return new_automaton;
	}


    

	bool fa::Automaton::hasEmptyIntersectionWith(const Automaton& other) const{
		fa::Automaton new_automate = createProduct(*this, other);
        std::cout << "alphabet : " << new_automate.getAlphabetSize() << ", transitions : " << new_automate.countTransitions() << ", states : " << new_automate.countStates() << std::endl;
        new_automate.prettyPrint(std::cout);
        return new_automate.getAlphabetSize()==0 || new_automate.countTransitions() ==0 || new_automate.countStates() ==0 || new_automate.getInitialStates().empty() || new_automate.getFinalStates().empty();
	}




  //********************************************** fin de TP4 ***********************************




  //*************************************   tp6   ***********************************
  bool fa::Automaton::CompareMap(std::map<int,int> &mapSrc, std::map<int,int> &mapDst){
  	if ( mapSrc.size() != mapDst.size() ){
  		return false;
  	}

  	std::map<int,int>::iterator it = mapSrc.begin();
  	while( it != mapSrc.end()){
  		std::map<int,int>::iterator itDst = mapDst.find(it->first);
  		if (itDst != mapDst.end()){
  			if (itDst->second != it->second){
  				return false;
  			}
  		}
  		else{
  			return false;
  		}
  		it++;
  	}
  	return true;
  }


  Automaton fa::Automaton::createMinimalMoore(const Automaton& automaton){
    bool finish = false;
    fa::Automaton tmp_automate;
    tmp_automate = automaton;
    if(!tmp_automate.isComplete()){
      tmp_automate.makeComplete();
    }
    // if(!tmp_automate.isDeterministic()){
    //   tmp_automate.Deterministic();
    // }


    fa::Automaton new_automate;
    std::map<int,int> map0,map1;
    std::map<int,int> map2, map3;
    std::set<char> tmp_alphabets = tmp_automate.getAlphabets();
    std::set<struct trans> tmp_transitions = tmp_automate.getTransitions();
    std::set<struct trans>::iterator tmp_transtions_iter;
    std::set<int> tmp_states = tmp_automate.getStates();
    std::set<int>::iterator tmp_states_iter = tmp_states.begin();
    int nbState = tmp_automate.countStates() + 1;

    while(tmp_states_iter != tmp_states.end()){
      if(automaton.isStateFinal(*tmp_states_iter)){
        map0.insert(std::pair<int,int>(*tmp_states_iter,2));
        map1.insert(std::pair<int,int>(*tmp_states_iter,2));
      }
      else{
        map0.insert(std::pair<int,int>(*tmp_states_iter,1));
        map1.insert(std::pair<int,int>(*tmp_states_iter,1));
      }
      tmp_states_iter++;
    }



    while(!finish){
      tmp_transtions_iter = tmp_transitions.begin();
      while(tmp_transtions_iter != tmp_transitions.end()){
        //nb_0 est la position de alpha dans automate
        //nb est multiplier pour calculer et séparer dans map1
        int nb_0 = std::distance( tmp_alphabets.begin(), std::find( tmp_alphabets.begin(), tmp_alphabets.end(),tmp_transtions_iter->alpha)) + 2;
        int nb = pow(nbState, nb_0);
        map1[tmp_transtions_iter->from]=map1[tmp_transtions_iter->from]+map0[tmp_transtions_iter->to]*nb;
        // map1.insert(std::pair<int,int>(tmp_transtions_iter->from,map1[tmp_transtions_iter->from]+map0[tmp_transtions_iter->to]*nb));
        tmp_transtions_iter++;
      }


      std::map<int,int>::iterator it11 = map1.begin();
      while(it11!=map1.end()){
        it11++;
      }


      int current = 1;
      tmp_states_iter = tmp_states.begin();
      while(tmp_states_iter != tmp_states.end()){
        std::map<int,int>::iterator map3_it = map3.begin();
        std::map<int,int>::iterator map2_it = map2.begin();
        bool hasValue = false;
        while(map3_it != map3.end()){
          if(map3_it->second==map1[*tmp_states_iter]){
            hasValue=true;
            break;
          }
          map3_it++;
          map2_it++;
        }
        if(hasValue){
          map2.insert(std::pair<int,int>((*tmp_states_iter),map2_it->second));
        }
        else{
          map2.insert(std::pair<int,int>(*tmp_states_iter,current));
          map3.insert(std::pair<int,int>(*tmp_states_iter, map1[*tmp_states_iter]));
          current++;
        }
        tmp_states_iter++;
      }
      if(CompareMap(map0,map2)){
        finish = true;
        break;
      }
      else{
        map0 = map2;
        map1 = map2;
        map2.clear();
        map3.clear();
      }
    }

    std::map<int,int>::iterator map2_it = map2.begin();
    while(map2_it != map2.end()){
      new_automate.addState((*map2_it).second);
      if(tmp_automate.isStateFinal((*map2_it).first)){
        new_automate.setStateFinal((*map2_it).second);
      }
      if(tmp_automate.isStateInitial((*map2_it).first)){
        new_automate.setStateInitial((*map2_it).second);
      }
      map2_it++;
    }

    std::map<int,int>::iterator map1_it = map1.begin();
    while(map1_it != map1.end()){
      std::set<char>::iterator tmp_alphabets_iter = tmp_alphabets.begin();
      while(tmp_alphabets_iter != tmp_alphabets.end()){
        int nb_1 = std::distance( tmp_alphabets.begin(), tmp_alphabets_iter) + 2;
        int nb1 = pow(nbState, nb_1);
        int stat_to = (map1_it->second/nb1)%nbState;
        new_automate.addTransition(map1_it->first, *tmp_alphabets_iter, stat_to);
        tmp_alphabets_iter++;
      }
      map1_it++;
    }

    return new_automate;
  }


  std::set<struct trans> * fa::Automaton::getTransitionsPointer(){
    return &transitions;
  }



  Automaton fa::Automaton::createWithoutEpsilon(const Automaton& automaton){
    Automaton new_automaton = automaton;
    std::set<struct trans> *new_transitions = new_automaton.getTransitionsPointer();
    std::set<struct trans>::iterator new_transitions_it = new_transitions->begin();
    while(new_transitions_it != new_transitions->end()){
      // bool yes=false;
      if(new_transitions_it->alpha == '\0'){
        std::cout << "Etape1: " <<new_transitions_it->from <<new_transitions_it->alpha << new_transitions_it->to<< std::endl;
        std::set<struct trans>::iterator new_transitions_it2 = new_transitions->begin();
        while(new_transitions_it2 != new_transitions->end()){
          if(new_transitions_it2->from == new_transitions_it->to){
            if(automaton.isStateFinal(new_transitions_it2->to)){
              new_automaton.setStateFinal(new_transitions_it->from);
            }
            new_automaton.addTransition(new_transitions_it->from,new_transitions_it2->alpha,new_transitions_it2->to);
            std::cout << "Etape2: " << new_transitions_it->from << new_transitions_it2->alpha << new_transitions_it2->to << std::endl;
            // if(new_transitions_it2->alpha == '\0'){
            //   yes = true;
            // }
          }
          new_transitions_it2++;
        }
        std::cout << "Before: " << new_automaton.countTransitions() << std::endl;
        // new_transitions_it = new_transitions.erase(new_transitions_it);
        new_automaton.removeTransition(new_transitions_it->from,new_transitions_it->alpha,new_transitions_it->to);
        std::cout << "After: " << new_automaton.countTransitions() << std::endl;
        std::cout << "Etape3: " << new_transitions_it->from << new_transitions_it->alpha << new_transitions_it->to << std::endl;

        new_transitions = NULL;
        new_transitions = new_automaton.getTransitionsPointer();
        std::set<struct trans>::iterator new_transitions_it3 = new_transitions->begin();
        while(new_transitions_it3!=new_transitions->end()){
          std::cout << "Etape4: " << new_transitions_it3->from << new_transitions_it3->alpha << new_transitions_it3->to << std::endl;
          new_transitions_it3++;
        }
        // if(yes){
        //   new_transitions_it = new_transitions.begin();
        // }
      }
      // if(!yes){
        new_transitions_it++;
      // }
    }
    return new_automaton;
  }




  //----------------------------------------------fin de TP6--------------------------------------------


    std::set<int> fa::Automaton::getStates() const{
		return states;
	}

    std::set<int> fa::Automaton::getInitialStates() const{
    	return initialStates;
    }

    std::set<int> fa::Automaton::getFinalStates() const{
    	return finalStates;
    }

    std::set<struct trans> fa::Automaton::getTransitions() const{
    	return transitions;
    }

    std::set<char> fa::Automaton::getAlphabets() const{
    	return alphabets;
    }

    int fa::Automaton::getTheBiggestState() const{
    	std::set<int>::iterator first = states.begin();
    	std::size_t tmp=countStates();
    	for(size_t i=1; i<tmp; i++){
    		first++;
    	}
    	return *first;
    }

    int fa::Automaton::getToWithFromAndAlpha(int from, char alpha) const{
    	std::set<int>::iterator iter_to = states.begin();
    	while(iter_to != states.end()){
    		struct trans try_transition;
    		try_transition.from = from;
    		try_transition.alpha = alpha;
    		try_transition.to = *iter_to;
    		if(transitions.find(try_transition) != transitions.end()){
    			return *iter_to;
    		}
    		iter_to ++;
    	}
    	return 0;

    }

    std::set<int> fa::Automaton::getToSetWithFromAndAlpha(int from, char alpha) const {
        std::set<int> to;
        for (std::set<struct trans>::iterator trans_iter = transitions.begin(); trans_iter != transitions.end(); trans_iter++) {
            if ((*trans_iter).from == from && (*trans_iter).alpha == alpha) {
                to.insert((*trans_iter).to);
            }
            if ((*trans_iter).from > from) {
                break;
            }
        }
        return to;
    }

    std::set<int> fa::Automaton::from(int state) const {
        std::set<int> to_set;
        std::set<struct trans>::iterator trans_iter = transitions.begin();
        while(trans_iter != transitions.end()){
            struct trans transition = *trans_iter;
            if (transition.from == state) {
                to_set.insert(transition.to);
            }
            trans_iter++;
        }
        return to_set;
    }

    std::set<int> fa::Automaton::to(int state) {
        std::set<int> from_set;
        std::set<struct trans>::iterator trans_iter = transitions.begin();
        while(trans_iter != transitions.end()){
            struct trans transition = *trans_iter;
            if (transition.to == state) {
                from_set.insert(transition.from);
            }
            trans_iter++;
        }
        return from_set;
    }

    bool fa::Automaton::depthFirstSearch(std::set<int> *visited, int current) const {
        if ((*visited).find(current) != (*visited).end()) {
            return false;
        }
        std::set<int> destinations = from(current);
        (*visited).insert(current);
        bool path_found = false;
        if ( ! destinations.empty() ) {
            std::set<int>::iterator dest_iter = destinations.begin();
            while (dest_iter != destinations.end()) {
                path_found = depthFirstSearch(visited, *dest_iter) || path_found;
                dest_iter++;
            }
        }
        if (finalStates.find(current) != finalStates.end()) {
            return true;
        }
        return path_found;
    }

    bool fa::Automaton::depthFirstSearchReversed(std::set<int> *visited, int current) {
        if ((*visited).find(current) != (*visited).end()) {
            return false;
        }
        std::set<int> origins = to(current);
        (*visited).insert(current);
        bool path_found = false;
        if ( ! origins.empty() ) {
            std::set<int>::iterator or_iter = origins.begin();
            while (or_iter != origins.end()) {
                path_found = depthFirstSearchReversed(visited, *or_iter) || path_found;
                or_iter++;
            }
        }
        if (initialStates.find(current) != initialStates.end()) {
            return true;
        }
        return path_found;
    }

    bool fa::Automaton::isLanguageEmpty() const {   // ! const
        std::set<int> visited_states;
        bool path_found = false;
        std::set<int>::iterator init_iter = initialStates.begin();
        while (init_iter != initialStates.end() && !path_found) {
            path_found = depthFirstSearch(&visited_states, *init_iter);
            init_iter++;
        }
        return !path_found;
    }

    void fa::Automaton::removeNonAccessibleStates() {
        std::set<int> visited_states;
        std::set<int>::iterator init_iter = initialStates.begin();
        while (init_iter != initialStates.end()) {
            depthFirstSearch(&visited_states, *init_iter);
            init_iter++;
        }
        for (std::set<int>::iterator states_iter = states.begin(); states_iter != states.end(); states_iter++) {
            if (visited_states.find(*states_iter) == visited_states.end()) {
                removeState(*states_iter);
                states_iter--;   //Pour éviter le saut d'indice lorsqu'un élément du set est supprimé
            }
        }
    }

    void fa::Automaton::removeNonCoAccessibleStates() {
        std::set<int> visited_states;
        std::set<int>::iterator final_iter = finalStates.begin();
        while (final_iter != finalStates.end()) {
            depthFirstSearchReversed(&visited_states, *final_iter);
            final_iter++;
        }
        for (std::set<int>::iterator states_iter = states.begin(); states_iter != states.end(); states_iter++) {
            if (visited_states.find(*states_iter) == visited_states.end()) {
                removeState(*states_iter);
                states_iter--;   //Pour éviter le saut d'indice lorsqu'un élément du set est supprimé
            }
        }
    }

    void fa::Automaton::readStringPartial(const std::string& word, int current, std::set<int> path, std::set<int> *derivated_states) const {

        if (word.empty()) {
            //if (isStateFinal(current)) {
               // for (std::set<int>::iterator path_iter = path.begin(); path_iter != path.end(); path_iter++) {
                  //  (*derivated_states).insert(*path_iter);
               // }
           // }
            (*derivated_states).insert(current);    //l'état à la fin du mot est ajouté
            return;
        }

        char next = word.front();
        for (std::set<struct trans>::iterator trans_iter = transitions.begin(); trans_iter != transitions.end(); trans_iter++) {
            if ((*trans_iter).from == current && (*trans_iter).alpha == next) {
                std::set<int> updated_path = std::set<int>(path);
                updated_path.insert((*trans_iter).to);
                readStringPartial(word.substr(1, word.length()-1), (*trans_iter).to, updated_path, derivated_states);
            }
            if ((*trans_iter).from > current) {
                return;    //We leave once the area is behind
            }
        }
    }

    std::set<int> fa::Automaton::readString(const std::string& word) const {
        std::set<int> path;
        std::set<int> derivated_states;
        for (std::set<int>::iterator iter_init = initialStates.begin(); iter_init != initialStates.end(); iter_init++) {
            path.clear();
            path.insert(*iter_init);
            readStringPartial(word, *iter_init, path, &derivated_states);
        }
        return derivated_states;
    }

    bool fa::Automaton::match(const std::string& word) const {
        std::set<int> derivated = readString(word);
        for (std::set<int>::iterator der_iter = derivated.begin(); der_iter != derivated.end(); der_iter++) {
            if (isStateFinal(*der_iter)) {
                return true;
            }
        }
        return false;
    }

    void fa::Automaton::deterministicRecProcess(std::set<int> new_step, std::map<std::set<int>,std::map<char,std::set<int>>> *process_board) {
        if ((*process_board).find(new_step) != (*process_board).end()) {
            return;
        }
        std::map<char,std::set<int>> to_map;
        std::pair<std::map<std::set<int>,std::map<char,std::set<int>>>::iterator,bool> new_line = (*process_board).insert(std::pair<std::set<int>,std::map<char,std::set<int>>>(new_step, to_map));
        /*for (std::set<int>::iterator step_iter = new_step.begin(); step_iter != new_step.end(); step_iter++) {
            for (std::set<char>::iterator alpha_iter = alphabets.begin(); alpha_iter != alphabets.end(); alpha_iter++) {
                std::set<int> to_set = getToSetWithFromAndAlpha(*step_iter, *alpha_iter);
                ((*(new_line.first)).second).insert(std::pair<char,std::set<int>>(*alpha_iter, to_set));
                deterministicRecProcess(to_set, process_board);
            }
        }*/
        for (std::set<char>::iterator alpha_iter = alphabets.begin(); alpha_iter != alphabets.end(); alpha_iter++) {
            std::set<int> to_alpha_accumulated;
            for (std::set<int>::iterator step_iter = new_step.begin(); step_iter != new_step.end(); step_iter++) {
                std::set<int> to_alpha = getToSetWithFromAndAlpha(*step_iter, *alpha_iter);
                to_alpha_accumulated.insert(to_alpha.begin(), to_alpha.end());
            }
            ((*(new_line.first)).second).insert(std::pair<char,std::set<int>>(*alpha_iter, to_alpha_accumulated));
            deterministicRecProcess(to_alpha_accumulated, process_board);
        }
    }

    Automaton fa::Automaton::createDeterministic() {
        std::map<std::set<int>,std::map<char,std::set<int>>> process_board;
        deterministicRecProcess(getInitialStates(),&process_board);
        std::map<std::set<int>,int> new_nbs_map;
        int max_state_value = 0;
        Automaton determinist;
        for (std::map<std::set<int>,std::map<char,std::set<int>>>::iterator line_iter = process_board.begin(); line_iter != process_board.end(); line_iter++) {
            if (((*line_iter).first).empty())  {
                continue;
            }
            new_nbs_map.insert(std::pair<std::set<int>,int>((*line_iter).first, max_state_value));
            determinist.addState(max_state_value);
            bool is_init = true;
            for (std::set<int>::iterator it = ((*line_iter).first).begin(); it != ((*line_iter).first).end(); it++) {
                if (isStateFinal(*it)) {
                    determinist.setStateFinal(max_state_value);
                }
                if (!isStateInitial(*it)) {
                    is_init = false;
                }
            }
            if (is_init) {
                determinist.setStateInitial(max_state_value);
            }
            max_state_value++;
        }

        for (std::map<std::set<int>,int>::iterator iter = new_nbs_map.begin(); iter != new_nbs_map.end(); iter++) {
            std::cout << "[";
                for (std::set<int>::iterator set_iter = ((*iter).first).begin(); set_iter != ((*iter).first).end(); set_iter++) {
                    std::cout << " " << *set_iter;
                }
            std::cout << " ] -> " << (*iter).second << std::endl;
        }

        for (std::map<std::set<int>,std::map<char,std::set<int>>>::iterator line_iter = process_board.begin(); line_iter != process_board.end(); line_iter++) {
            for (std::map<char,std::set<int>>::iterator alpha_iter = ((*line_iter).second).begin(); alpha_iter != ((*line_iter).second).end(); alpha_iter++) {
                if (((*alpha_iter).second).empty()) {
                    continue;
                }
                int new_from = (*(new_nbs_map.find((*line_iter).first))).second;
                int new_to = (*(new_nbs_map.find((*alpha_iter).second))).second;
                char alpha = (*alpha_iter).first;
                determinist.addTransition(new_from, alpha, new_to);
            }
        }
        return determinist;
    }

        Automaton fa::Automaton::createDeterministic(const Automaton& automaton) {
            Automaton auto_cpy = automaton;
            return auto_cpy.createDeterministic();
        }

        bool fa::Automaton::isIncludedIn(const Automaton& other) const {
            Automaton other_cpy = other;
            other_cpy.makeComplement();
            return hasEmptyIntersectionWith(other_cpy);
        }
}
