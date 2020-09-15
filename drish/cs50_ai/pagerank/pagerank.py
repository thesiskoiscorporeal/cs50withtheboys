import os
import random
import re
import sys
import numpy as np

DAMPING = 0.85
SAMPLES = 10000


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python pagerank.py corpus")
    corpus = crawl(sys.argv[1])
    
    ranks = sample_pagerank(corpus, DAMPING, SAMPLES)
    print(f"PageRank Results from Sampling (n = {SAMPLES})")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")
      
    ranks = iterate_pagerank(corpus, DAMPING)
    print(f"PageRank Results from Iteration")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")


def crawl(directory):
    """
    Parse a directory of HTML pages and check for links to other pages.
    Return a dictionary where each key is a page, and values are
    a list of all other pages in the corpus that are linked to by the page.
    """
    pages = dict()

    # Extract all links from HTML files
    for filename in os.listdir(directory):
        if not filename.endswith(".html"):
            continue
        with open(os.path.join(directory, filename)) as f:
            contents = f.read()
            links = re.findall(r"<a\s+(?:[^>]*?)href=\"([^\"]*)\"", contents)
            pages[filename] = set(links) - {filename}

    # Only include links to other pages in the corpus
    for filename in pages:
        pages[filename] = set(
            link for link in pages[filename]
            if link in pages
        )

    return pages


def transition_model(corpus, page, damping_factor):
    """
    Return a probability distribution over which page to visit next,
    given a current page.

    With probability `damping_factor`, choose a link at random
    linked to by `page`. With probability `1 - damping_factor`, choose
    a link at random chosen from all pages in the corpus.
    """

    # initialise model to 1 - d (random jump)term
    model = {x: (1 - damping_factor)/len(corpus) for x in corpus.keys()}

    # random click term
    if len(corpus[page]) > 0:
        prob_click = (1 / len(corpus[page]))*damping_factor
        for outlink in corpus[page]:
            model[outlink] = float(model[outlink]) + prob_click
    else: # if there are no links out of a page (other than itself)
        model[page] += damping_factor # surfer will stay there in absence of random jump 
                                       

    return model


def sample_pagerank(corpus, damping_factor, n):
    """
    Return PageRank values for each page by sampling `n` pages
    according to transition model, starting with a page at randommodelfor x in model

    Return a dictionary where modelpagerank[x] = model are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """

    # initialise time series with one randomly selected page
    time_series = [np.random.choice([x for x in corpus.keys()])]

    # iteratively add remaining n-1 pages to time series
    for iteration in range(n-1):
        probs = [*transition_model(corpus, time_series[-1], damping_factor).values()]
        time_series.append(np.random.choice(
            [*corpus.keys()], p=probs))  # TODO

    # create pagerank dict
    pagerank = {x: time_series.count(x) / len(time_series)
                for x in corpus.keys()}

    # normalise values of pagerank for good measure
    probs = np.array([*pagerank.values()])
    probs /= probs.sum()
    pagerank = {[*pagerank.keys()][x] : probs[x] for x in range(len(pagerank))}

    return pagerank


def iterate_pagerank(corpus, damping_factor):
    """
    Return PageRank values for each page by iteratively updating
    PageRank values until convergence.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    
    N = len(corpus)
    
    # initialise values to 1/N
    pagerank = {x: 1 / N
                for x in corpus.keys()}
    
    # explicitly copy dictionary
    new_pagerank = pagerank.copy()
    iterations = 0
    while True:
        # iterate over keys, values in new_pagerank  
        for (page, rank) in new_pagerank.items():
            # initialise rank to static term
            new_pagerank[page] = (1 - damping_factor)/N
            for (key, value) in corpus.items():
                if page in value:
                    new_pagerank[page] += damping_factor * new_pagerank[key] / len(value)    

        # np arrays for old and new PR scores
        old_scores = np.array([*pagerank.values()])
        new_scores = np.array([*new_pagerank.values()])
        
        # array of absolute differerences
        diff = np.abs(old_scores - new_scores)             
        # convert to boolean array, gives TRUE if > 0.001
        diff = diff > 0.001
        
        # if NONE of the elements are TRUE, break (all less than 0.001 diff)
        if not np.any(diff):
            break
        else:
            #explicitly copy dictionary
            pagerank = new_pagerank.copy()
            iterations += 1            
        
            
    
        
    # normalise values of pagerank for good measure
    probs = np.array([*new_pagerank.values()])
    probs /= probs.sum()
    new_pagerank = {[*new_pagerank.keys()][x] : probs[x] for x in range(len(new_pagerank))}
    return new_pagerank


if __name__ == "__main__":
    main()
