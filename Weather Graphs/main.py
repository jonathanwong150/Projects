# Name: Jonathan Wong
# Email: Jzwong@usc.edu
# Section: 31885
# Spring 2022
# Homework 13

import matplotlib.pyplot as plt
import pandas as pd

def main():
    # Read in the pandas file and drop null values
    df = pd.read_csv("chicago.csv")
    df = df.dropna()
    # Create figure with two subplots
    fig, ax = plt.subplots(2, figsize=(15,10))
    # List containing the years we have data for
    ten_years = [2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021, 2022]
    # Convert all strings to datetime objects to parse easily
    df["DATE"] = pd.to_datetime(df["DATE"])
    # Separate specific dates using strftime
    df["DAY"] = df["DATE"].dt.strftime("%m-%d")
    # Group the days and years
    years = df.groupby(df["DATE"].dt.year)
    days = df.groupby(df["DAY"])
    # Iterate through all the years we have data for
    for year in ten_years:
        # Retrieve all data for that year and plot
        group = years.get_group(year)
        group.plot('DAY', 'TMAX', xlabel='Month', label=year, ax=ax[0])
    # Iterate through each day and find the average temperature values
    TAVG_list = []
    for day in df["DAY"]:
        group = days.get_group(day)
        TAVG = group['TMAX'].mean()
        # Append to our temperatture list
        TAVG_list.append(TAVG)
    # In our second plot, plot the average temperature values for past years
    ax[1].bar(df["DAY"], TAVG_list, color='blue', alpha=0.6, label="historical average")
    # Group the 2021 data and plot
    group_2021 = years.get_group(ten_years[-2])
    ax[1].bar(group_2021['DAY'], group_2021['TMAX'], color='orange', label='2021', alpha=0.6)
    # Create a title for our figure
    fig.suptitle('Yearly climatological data for Chicago from 2012 to 2022')
    # Set the title and axes for both grapphs
    ax[0].set(title='Last 10 years', xlabel= "Months", ylabel='temp (ºF)')
    ax[1].set(title='Current year and historical averages', xlabel='Months', ylabel='temp (ºF)')
    months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November","December"]
    # Set the months as x-axis values
    ax[0].xaxis.set_major_locator(plt.MultipleLocator(35))
    ax[0].set_xticklabels(months)
    ax[1].xaxis.set_major_locator(plt.MultipleLocator(35))
    ax[1].set_xticklabels(months)
    # Display the legends
    ax[0].legend()
    ax[1].legend()
    fig.tight_layout()
    # Show plot
    plt.show()

if __name__ == "__main__":
    main()
