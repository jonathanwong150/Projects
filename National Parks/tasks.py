# Jonathan Wong, jzwong@usc.edu
# ITP 115, Fall 2021
# Section: 31856
# Final Project
# tasks.py
# Description: Define functions that will be called from other functions in another Python file.

# Function Name: createListOfParks
# Input: name of input csv file
# Return: List of dictionary objects
# Side Effect: None
# Description: Creates a list with all parks in csv and their description and traits
def createListOfParks(fileName="national_parks.csv"):
    # Store result list and open the csv file
    result=[]
    fileIn=open(fileName,"r")
    # Store file header
    header=fileIn.readline().strip().split(",")
    # Track line number and iterate through csv
    for row in fileIn:
        # If the row is longer than the header, description has commas
        if len(row)>len(header):
            # Split that row into a list and join the last index
            row=row.split(",")
            row[len(header)-1]=",".join(row[len(header)-1::])
        # Create dictionary and initialize index
        dict={}
        index=0
        # For every column in the header
        for col in header:
            # Add a dict entry from col to row index
            dict[col]=row[index].strip().replace('"','')
            index+=1
        # Append to result list
        result.append(dict)
    return result

# Function Name: getDate
# Input: dataStr is a string containing the date (YYYY-MM-DD)
# Return: a string with the date in the following format: Month Day, Year
# Side Effect: None
# Description: Creates a string given a date
def getDate(dataStr):
    # Split param using hyphen
    date=dataStr.split("-")
    # Create a list of all the months
    monthList=["January","February","March","April","May","June","July","August","September","October",
               "November","December"]
    # Get variables that make up the date
    year=date[0]
    # Subtract by 1 because list index start at 0
    month=int(date[1])-1
    day=date[2]
    #Create result string and return
    result= monthList[month] + " " + day + ", " + year
    return result

# Function Name: getLargestPark
# Input: parksList is a list of the parks where each park is a dictionary
# Return: a string that is the park code of the park with the largest area
# Side Effect: None
# Description: Finds code of the largest park in a list
def getLargestPark(parksList):
    max=-1
    code=""
    for park in parksList:
        size=int(park["Acres"])
        if size>max:
            max=int(park["Acres"])
            code=park["Code"]
    return code