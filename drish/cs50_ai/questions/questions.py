import nltk
import sys
import os
import string
import numpy as np

FILE_MATCHES = 1
SENTENCE_MATCHES = 1


def main():

    # Check command-line arguments
    if len(sys.argv) != 2:
        sys.exit("Usage: python questions.py corpus")

    # Calculate IDF values across files
    files = load_files(sys.argv[1])
    file_words = {
        filename: tokenize(files[filename])
        for filename in files
    }
    file_idfs = compute_idfs(file_words)

    # Prompt user for query
    query = set(tokenize(input("Query: ")))

    # Determine top file matches according to TF-IDF
    filenames = top_files(query, file_words, file_idfs, n=FILE_MATCHES)

    # Extract sentences from top files
    sentences = dict()
    for filename in filenames:
        for passage in files[filename].split("\n"):
            for sentence in nltk.sent_tokenize(passage):
                tokens = tokenize(sentence)
                if tokens:
                    sentences[sentence] = tokens

    # Compute IDF values across sentences
    idfs = compute_idfs(sentences)

    # Determine top sentence matches
    matches = top_sentences(query, sentences, idfs, n=SENTENCE_MATCHES)
    for match in matches:
        print(match + "\n")


def load_files(directory):
    """
    Given a directory name, return a dictionary mapping the filename of each
    `.txt` file inside that directory to the file's contents as a string.
    """
    results = {}
    
    for filename in os.listdir(directory): # iterate through filenames in directory
        f = open(os.path.join(directory, filename), "r", encoding="utf8") # open file
        results[filename] = f.read() # read contents and save to dict under key filename
        
    return results


def tokenize(document):
    """
    Given a document (represented as a string), return a list of all of the
    words in that document, in order.

    Process document by coverting all words to lowercase, and removing any
    punctuation or English stopwords.
    """
    
    result = nltk.tokenize.word_tokenize(document)
    result = [x.lower() for x in result]
    for item in result.copy(): # iterate through a copy of result so that you don't skip items as you remove items and the indices get messed up
        if item in nltk.corpus.stopwords.words("english") or item in string.punctuation:
            while item in result: result.remove(item)

    return result


def compute_idfs(documents):
    """
    Given a dictionary of `documents` that maps names of documents to a list
    of words, return a dictionary that maps words to their IDF values.

    Any word that appears in at least one of the documents should be in the
    resulting dictionary.
    """
    result = {}
    num_docs = len(documents)
    for key,item in documents.items(): # iterate through documents dict
        for word in item: # iterate through words in document
            if word in result.keys(): # skip if word idf already calculated
                continue
            else:
                num_appeared = 0 # number of docs in which word appears
                for x,y in documents.items(): # iterate through documents dict 
                    if word in y:
                        num_appeared += 1 # increment num_appeared if word in current document
                
                result[word] = np.log(num_docs/num_appeared)
                
    return result


def top_files(query, files, idfs, n):
    """
    Given a `query` (a set of words), `files` (a dictionary mapping names of
    files to a list of their words), and `idfs` (a dictionary mapping words
    to their IDF values), return a list of the filenames of the the `n` top
    files that match the query, ranked according to tf-idf.
    """
    file_values = {x: 0 for x in files.keys()} # dict containing filenames as keys and sum of query tf-idfs as values, initialise values to 0
    
    for word in query: # iterate over words in query
        for file,contents in files.items(): # iterate over files and their contents in dict
            if word in contents:
                tf_idf = contents.count(word) * idfs[word] # calculate tf-idf of word in contents of file
                file_values[file] += tf_idf # add calculated tf-idf for current word to value in file_values dict
    
    result = sorted(file_values, key=file_values.get, reverse=True)[:n] # returns list of n dict keys with highest values, descending order
      
    return result


def top_sentences(query, sentences, idfs, n):
    """
    Given a `query` (a set of words), `sentences` (a dictionary mapping
    sentences to a list of their words), and `idfs` (a dictionary mapping words
    to their IDF values), return a list of the `n` top sentences that match
    the query, ranked according to idf. If there are ties, preference should
    be given to sentences that have a higher query term density.
    """
    
    sentence_idfs = {x: 0 for x in sentences.keys()} # dict containing sentences as keys and sum of query idfs as values, initialise values to 0
    sentence_densities = {x: 0 for x in sentences.keys()} # dict containing query term densities 
    
    for word in query: # iterate over words in query
        for sentence,contents in sentences.items(): # iterate over sentences and their list of words
            if word in contents:
                sentence_idfs[sentence] += idfs[word] # add idf of word in query to value of sentence in sentence_idfs dict
    
    for key in sentences.keys(): # iterate over keys with max idf values
        sentence_length = len(sentences[key])
        words_in_query = 0 # number of words in sentence that are also in querty
        for word in sentences[key]: # iterate over contents of item (list)
            if word in query:
                words_in_query += 1
        sentence_densities[key] = words_in_query/sentence_length # update value of sentence key in dict to its query term density            
    
    result = [*sentences.keys()]
    result = sorted(result, key=lambda e: (sentence_idfs[e], sentence_densities[e]), reverse=True) # sort keys first by idf then by keyword term densities
    
    ''' #metrics
    counter = 1                                                                                               # reverse=True for descending order    
    for thing in result[:n]:
        print("Item " + str(counter))
        print("IDF: " + str(sentence_idfs[thing]))
        print("density: " + str(sentence_densities[thing]))
        print("Composite: " + str(sentence_idfs[thing] * sentence_densities[thing]) + "\n")
        counter += 1
    '''
        
    return result[:n]


if __name__ == "__main__":
    main()
