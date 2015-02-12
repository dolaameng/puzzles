from sklearn.feature_extraction import text
from sklearn.naive_bayes import MultinomialNB
from sklearn.grid_search import GridSearchCV
from sklearn.pipeline import Pipeline
import numpy as np
from sys import stdin 

train_file = "data/trainingdata.txt"
lines = open(train_file).readlines()[1:]
labels, texts = zip(*[line.split(None, 1) for line in lines])
labels = np.asarray(labels)
texts = np.asarray(texts)

tfidf = text.TfidfVectorizer(stop_words="english", ngram_range=(1, 1),  
                             min_df = 15, max_df = 0.3)
train_X = tfidf.fit_transform(texts)
nb_classifier = MultinomialNB(alpha=0.5)
nb_classifier.fit(train_X, labels)


T = int(stdin.readline())
test_texts = [stdin.readline() for _ in xrange(T)]
test_X = tfidf.transform(test_texts)
test_yhat = nb_classifier.predict(test_X)
print "\n".join(test_yhat)