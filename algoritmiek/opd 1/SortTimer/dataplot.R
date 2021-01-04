library(readr)
data = read_csv("test.csv")

logn = log10(data$size)
mlogn = lm(data$duration ~ logn)
summary(mlogn)

plot(logn,data$duration)
abline(mlogn)


nsq = data$size^2
mnsq = lm(data$duration ~ nsq)
summary(mnsq)

plot(nsq, data$duration)
abline(mnsq)

nlogn = data$size * log10(data$size)
mnlogn = lm(data$duration ~ nlogn)
summary(mnlogn)

plot(nlogn,data$duration)
abline(mnlogn)