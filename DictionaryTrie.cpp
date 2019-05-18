#include "util.h"
#include "DictionaryTrie.h"
TstNode::TstNode(){};
TstNode::TstNode(char a)
{ 
  this-> val = a;
  this->end = false;
  this->left = NULL;
  this->mid = NULL;
  this->right = NULL;
  this->fn = INT_MIN;
  this->ans= "";
}
/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){ 
  root = 0;
}
/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  if(word.size()==0)
  	return false;
  TstNode* pt;
  if(!root){//the tree is empty
  	//set root as the new first letter which will traverse down only 
    root = new TstNode(word[0]); 
    pt = root;
    if(word.size()==1){
     	pt->end = true; 
      	pt->fn = freq;
		pt->ans = word;
		return true;
    }//ended early, but it is also an extra step
    for(unsigned int i = 1; i<word.size(); i++){
      pt->mid = new TstNode(word[i]);
      pt = pt->mid;
    }
    pt->end = true;
	pt->fn = freq;
	pt->ans = word;
	return true;
  }//end not root
  else{ //the tree is not originally empty
    pt = root;
    while(true){//traverse to the first node before looping to the later ones
    	if(pt->val > word[0]){
			if(pt->left!=NULL)
	  			pt = pt->left;
			else{
	  			pt->left = new TstNode(word[0]);
	 			pt = pt->left;
	  			break;
			}//else
      	}//if
    	else if( pt->val <word[0]){
			if(pt->right!=NULL)
	  			pt = pt->right;
			else{
	  			pt->right = new TstNode(word[0]);
	  			pt = pt->right;
	  			break;
			}
    	}
    	else{
			break;
    	} 
    } //while  
    for(unsigned int i = 1; i<word.length(); i++){
		if(!pt->mid){
			pt->mid = new TstNode(word[i]);
			pt = pt->mid;
      	}
      	else if (pt->mid->val == word[i]){
			pt = pt->mid;
      	}
      	else{
			pt = pt->mid;
			while(true){
				if(pt->val >word[i]){
					if(pt->left!=NULL)
						pt = pt->left;
					else{
						pt->left = new TstNode(word[i]);
						pt = pt->left;
					}
				}//if
				else if(pt->val < word[i]){
					if(pt->right!=NULL)
						pt = pt->right;
					else{
						pt->right = new TstNode(word[i]);
						pt = pt->right;
					}
				}//elif
				else{
					break;
				}     

			}//while
		}//else
    }   // for loop for str[1:] 
    if(pt->end)//if it is an end word 
      return false; 
    pt->end = true;
    pt->fn = freq;
	pt->ans = word;
  } // root not null
  return pt->end;
}
/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
	if(word.size()==0)//empty string
    	return false;
	if(!root)//root is null
		return false;
	TstNode *pt = root;
	for(unsigned int i = 0; i<word.length(); i++){
		while(true){
			if(pt->val >word[i]){
				if(pt->left!=NULL){
					pt=pt->left;
				}
				else{	
					return pt->end;
				}
			}
			else if(pt->val <word[i]){
				if(pt->right!=NULL){
					pt= pt->right;
				}
				else{
					return pt->end;
				}
			}
			else{
				if(pt->mid == NULL||i+1==word.length()){
					return pt->end;	
				}								
				else{
					break;
				}
			}//else					
		}//while
	}//for
	return pt->end;
}
/*
It is a helper method for predictComplection that traverse through all nonempty nodes
@param current: TstNode for current spot
@param a: set passed by reference for storing all the possible words
*/
void DictionaryTrie::traversalHelp(TstNode* current,std::set< std::pair<unsigned int, std::string> > & a){
	if(current->end){
		std::pair<unsigned int,std::string> p(current->fn,current->ans);
		a.insert(p);//insert into the set called by reference 
	}
	if(current->left!=NULL)//if left child node is not null
		traversalHelp(current->left, a);
	if(current->right!=NULL)
		traversalHelp(current->right,a);
 	if(current->mid!=NULL)
		traversalHelp(current->mid,a);
} 
/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  std::set<std::pair<unsigned int, std::string> > all; //store all if true the word, recursively traverse all the node, pass by reference.
	unsigned int count = 0;
	for(unsigned int i = 0; i<prefix.length(); i++){
		if(!std::islower(prefix[i])){
			std::cerr<<"Invalid Input. Please retry with correct input"<<std::endl;
			return words;
		}
	}
  	bool checkPre = false;
	if(!root){
		return words;
	}
	if(num_completions <=0 || prefix.length()<=0){
		return words;
	}
	TstNode*pt = root;	
	for(unsigned int i = 0; i<prefix.length();i++){			
		while(true){
			if(pt->val >prefix[i]){
				if(pt->left!=NULL){
					pt=pt->left;
				}
				else{
					return words;	
				}
			}
			else if(pt->val < prefix[i]){
				if(pt->right!=NULL){
					pt= pt->right;
				}
				else{
					return words;
				}
			}
			else{

				if(pt->mid == NULL ){
					return words;
				}
              	else if(pt->end && i == prefix.length()-1){
                  checkPre = true;
                  break;
                }
				else{
                  	pt=pt->mid;
                  	break;
				}
			}					
		}//while
	}//for
  	if(checkPre){
		std::pair<unsigned int,std::string> p(pt->fn,pt->ans);
		all.insert(p);
        traversalHelp(pt->mid,all);
    }
	else traversalHelp(pt->mid,all);
  	std::set< std::pair<unsigned int, std::string> >::reverse_iterator rit;
	for(rit = all.rbegin(); rit!=all.rend();++rit){
		words.push_back((*rit).second);
		count++;
		if(count==num_completions)
			break;
	}
	return words;
}
/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(this->root);

}
/* helper for destructor to efficiently perfore deallocation*/
void DictionaryTrie::deleteAll(TstNode* current){
	if(current == NULL)
		return;
	if(current->left!=NULL)
		deleteAll(current->left);
	if(current->right!=NULL)
		deleteAll(current->right);
	if(current->mid!=NULL)
		deleteAll(current->mid);
	delete current;
}
