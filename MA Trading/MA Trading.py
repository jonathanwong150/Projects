#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import pandas as pd
import matplotlib.pyplot as plt

#read-in input files
stock = pd.DataFrame.from_csv('/data/microsoft.csv') #Change file to desired stock
print(stock.head())
print(stock.shape())

#Add moving average columns
fast_sig= input("Enter the length of desired short signal: ") #Typical lengths are 10, 20 ,50
slow_sig= input("Enter the length of desired fast signal: ") #Typical lengths are 100, 200, 250
stock['FastMA'] = stock['Close'].rolling(fast_sig).mean() 
stock['SlowMA'] = stock['Close'].rolling(slow_sig).mean()
stock = stock.dropna()

#1 to long hold a sock and -1 to short a stock
stock['Shares'] = [1 if stock.loc[i, 'FastMA']>stock.loc[i, 'SlowMA'] else -1 for i in stock.index]

#plot data
plt.figure(figsize=(10, 8))
stock['Close'].plot()
stock['FastMA'].plot()
stock['ShortMA'].plot()
plt.show()

#Should I currently be holding or shorting?
if stock.iloc[-1,7]==1:
    print("Hold the stock, fast signal is greater than short signal.")
else:
    print("Short the stock, fast signal is less than short signal.")

