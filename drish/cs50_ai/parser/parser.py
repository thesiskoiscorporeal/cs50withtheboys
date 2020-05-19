import nltk
import sys
import re

TERMINALS = """
Adj -> "country" | "dreadful" | "enigmatical" | "little" | "moist" | "red"
Adv -> "down" | "here" | "never"
Conj -> "and"
Det -> "a" | "an" | "his" | "my" | "the"
N -> "armchair" | "companion" | "day" | "door" | "hand" | "he" | "himself"
N -> "holmes" | "home" | "i" | "mess" | "paint" | "palm" | "pipe" | "she"
N -> "smile" | "thursday" | "walk" | "we" | "word"
P -> "at" | "before" | "in" | "of" | "on" | "to" | "until"
V -> "arrived" | "came" | "chuckled" | "had" | "lit" | "said" | "sat"
V -> "smiled" | "tell" | "were"
"""

NONTERMINALS = """
S -> NP VP | NP VP Conj NP VP | NP VP PP NP VP | NP VP Conj VP 
NP -> N | Det N | AdjP N | NP PP | AdjP AdjP NP | AdjP AdjP AdjP N
VP -> V | AdvP VP | VP AdvP | VP PP NP | VP NP 
AdvP -> Adv | Det NP PP NP
AdjP -> Adj | Det Adj
PP -> P | P Det N P
"""

grammar = nltk.CFG.fromstring(NONTERMINALS + TERMINALS)
parser = nltk.ChartParser(grammar)


def main():

    # If filename specified, read sentence from file
    if len(sys.argv) == 2:
        with open(sys.argv[1]) as f:
            s = f.read()

    # Otherwise, get sentence as input
    else:
        s = input("Sentence: ")

    # Convert input into list of words
    s = preprocess(s)

    # Attempt to parse sentence
    try:
        trees = list(parser.parse(s))
    except ValueError as e:
        print(e)
        return
    if not trees:
        print("Could not parse sentence.")
        return

    # Print each tree with noun phrase chunks
    for tree in trees:
        tree.pretty_print()

        print("Noun Phrase Chunks")
        for np in np_chunk(tree):
            print(" ".join(np.flatten()))


def preprocess(sentence):
    """
    Convert `sentence` to a list of its words.
    Pre-process sentence by converting all characters to lowercase
    and removing any word that does not contain at least one alphabetic
    character.
    """
    
    # remove punctuation from sentence, lowercase, and convert to list
    sentence = sentence.lower()
    result = nltk.tokenize.word_tokenize(sentence)
       
    # remove non alphabetic words from result list
    for word in result:
        if not re.search('[a-zA-Z]', word): 
            result.remove(word)
            
    return result

def np_chunk(tree):
    """
    Return a list of all noun phrase chunks in the sentence tree.
    A noun phrase chunk is defined as any subtree of the sentence
    whose label is "NP" that does not itself contain any other
    noun phrases as subtrees.
    """
    result = []
    
    # iterate through subtrees with label 'NP', print subtree if does not contain subtrees containing NP
    for s in tree.subtrees(lambda t: t.label() == "NP"):
        subsub_labels = [subsub.label() for subsub in s.subtrees()] #create list of subsubtree labels
        if subsub_labels.count("NP") > 1: # if any of the subsubtree NON-ROOT labels are NP (NP count > 1), skip
            continue
        else:
            result.append(s) # else, append the subtree s to result list
                           
    return result


if __name__ == "__main__":
    main()
