setwd("D:/GitHub/projects/analytics/AL_opd4/AL_opd4")

library(tm)
library(SnowballC)

library(caret)
library(e1071)

#read data from csv file
twts = read.csv("twts.csv", stringsAsFactors = FALSE)
#extract only the needed data
twts = subset(
  twts,
  select = c(Sentiment, Tweet)
)

#add new factor Negative (TRUE or FALSE)
twts$Negative = as.factor(twts$Sentiment < 2)

#-------------------------------------------------------------------------------
#Pre-processing

#load tweets into the Corpus format (collection of documents)
# making it easy to apply modifications to the provided text
corpus = Corpus(VectorSource(twts$Tweet))
#set all characters to lower
corpus = tm_map(corpus, tolower)
#remove all punctuation
corpus = tm_map(corpus, removePunctuation)
#remove all stop-words, these are not needed in our model
corpus = tm_map(corpus, removeWords, c(stopwords("english")))

#stem all words
corpus = tm_map(corpus, stemDocument)

#-------------------------------------------------------------------------------
#Bag of words

#get frequencies of all the words in our corpus
frequencies = DocumentTermMatrix(corpus)

#remove rare words
sparse = removeSparseTerms(frequencies, 0.995)

#make sparse into a data frame
tweetSparse = as.data.frame(as.matrix(sparse))
#correcting names , words that start with numbers will be changed
colnames(tweetSparse) = make.names(colnames(tweetSparse))

#add independent variable
tweetSparse$Negative = twts$Negative


#-------------------------------------------------------------------------------
#Splitting data

library(caTools)
#seed for pseudo random generator
set.seed(123)
#splitting the data
split = sample.split(tweetSparse$Negative, SplitRatio = 0.7)
#training set
trainsparse = subset(tweetSparse, split == TRUE)
#testing set
testsparse = subset(tweetSparse, split == FALSE)
#-------------------------------------------------------------------------------
#CART-Tree

library(rpart)
library(rpart.plot)

#create CART-Tree
tweetCART = rpart(Negative ~ ., data = trainsparse, method ="class")  
#plot Cart-Tree
prp(tweetCART)
#prediction from our model applied to our test-set
predictCart = predict(tweetCART, newdata = testsparse, type="class")

#Confusion Matrix
print(confusionMatrix(testsparse$Negative, predictCart))

#-------------------------------------------------------------------------------
#ROC-Curve

library(ROCR)
#create ROC predict
predictTreeROC = predict(tweetCART,newdata = testsparse)

ROCRpred = prediction(predictTreeROC[,2],testsparse$Negative)
perf = performance(ROCRpred, "tpr", "fpr")
#Plot the ROC_Curve
plot(perf,
     colorize = TRUE,
     print.cutoffs.at = seq(0, 1, 0.1))
#Addition of linear line
abline(0, 1)
#Calculate Area under the Curve
AUC = as.numeric(performance(ROCRpred, "auc")@y.values)
print(AUC)
