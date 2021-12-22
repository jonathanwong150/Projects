# Jonathan Wong, jzwong@usc.edu
# ITP 115, Fall 2021
# Section: 31856
# Final Project
# tasks.py
# Description: Define functions and sets up interface used in other files

import tasks

# Function Name: getMenuDict
# Input: None
# Return: A dictionary where the keys are letter inputs and values are menu options
# Side Effect: None
# Description: Creates a menu for user input
def getMenuDict():
    # Hard code a dictionary with choices and return
    dict={"A": "All National Parks","B": "Parks in a particular state", "C": "The largest park",
          "D": "Search for a park","E": "The oldest park","F": "State with most parks","Q": "Quit"}
    return dict

# Function Name: displayMenu
# Input: menuDict is a dictionary for the menu
# Return: None
# Side Effect: Prints menu to the screen
# Description: Displays a dictionary menu
def displayMenu(menuDict):
    # Iterate through the dictionary and print each key and value
    for key in menuDict:
        print(key,"->",menuDict[key])

# Function Name: getUserInput
# Input: menuDict is a dictionary for the menu
# Return: a string that is a valid choice entered by the user
# Side Effect: Prints to screen asking for a user input
# Description: Gets a valid user input for the menu
def getUserInput(menuDict):
    choice="z"
    while choice!="A" and choice!="B" and choice!="C" and choice!="D" and choice!="E" and choice!="F" and choice!="Q":
        choice=input("Choice: ").upper()
    return choice

# Function Name: printAllParks
# Input: parksList is a list of the parks where each park is a dictionary
# Return: None
# Side Effect: Prints park information
# Description: Loops through the park list and prints some information for each park
def printAllParks(parksList):
    for park in parksList:
        # Print basic information using dictionary keys
        print(park["Name"],"(" + park["Code"] + ")")
        print("\tLocation:",park["State"])
        print("\tArea:",park["Acres"],"acres")
        # Use tasks.getDate() function to get correct format
        print("\tDate Established:",tasks.getDate(park["Date"]))
        print("")

# Function Name: getState
# Input: None
# Return: a string with a two-letter abbreviation of a state
# Side Effect: Prints to screen asking for a user input
# Description: Keeps asking user to input a state abbreviation until valid
def getState():
    # Junk value to initiate while loop
    state="abc"
    # Keep running loop until we get a string of valid size
    while len(state)!=2:
        #Ask for state
        state=input("Enter a state: ").upper()
        if len(state)!=2:
            print("Need a two letter abbreviation")
    return state

# Function Name: printParksInState
# Input: parksList is a list containing parks represented by dictionaries
# Return: None
# Side Effect: Calls getState() and prints to screen
# Description: Finds all the parks in a given state and prints their information
def printParksInState(parksList):
    # Ask the user for a state
    state=getState()
    # Count how many parks are in that statet
    count=0
    # Loop through parksList and if we get a state match
    for park in parksList:
        # Print basic information
        if state in park["State"]:
            print(park["Name"], "(" + park["Code"] + ")")
            print("\tLocation:", park["State"])
            print("\tArea:", park["Acres"], "acres")
            # Use tasks.getDate() function to get correct format
            print("\tDate Established:", tasks.getDate(park["Date"]))
            print("")
            # Increment count
            count+=1
    # If there are no parks in that state, print different message
    if count==0:
        print("There are no national parks in",state,"or it is not a valid state.")

# Function Name: printLargestPark
# Input: parksList is a list containing parks represented by dictionaries
# Return: None
# Side Effect: Calls getLargestPark() and prints that parks information
# Description: Prints the information for the largest park in the list
def printLargestPark(parksList):
    # Call function to find the code of largest park
    code=tasks.getLargestPark(parksList)
    # Loop through the list to find largest park
    for park in parksList:
        if park["Code"]==code:
            # Print all of its information
            print(park["Name"], "(" + park["Code"] + ")")
            print("\tLocation:", park["State"])
            print("\tArea:", park["Acres"], "acres")
            # Use tasks.getDate() function to get correct format
            print("\tDate Established:", tasks.getDate(park["Date"]))
            print("\tDescription:", park["Description"])

# Function Name: printParksForSearch
# Input: parksList is a list containing parks represented by dictionaries
# Return: None
# Side Effect: Prints information to output
# Description: Asks user for a search term and prints information for all parks with the search term
def printParksForSearch(parksList):
    # Ask user for a search term and changes the case
    search=input("Enter text for searching: ").lower()
    # Keep track of a count
    count=0
    # Iterate through park list and search for term in name, code, or description
    for park in parksList:
        if search in park["Code"].lower() or search in park["Name"].lower() or search in park["Description"].lower():
            # Print all of its information
            print(park["Name"], "(" + park["Code"] + ")")
            print("\tLocation:", park["State"])
            print("\tArea:", park["Acres"], "acres")
            # Use tasks.getDate() function to get correct format
            print("\tDate Established:", tasks.getDate(park["Date"]))
            print("\tDescription:", park["Description"])
            count+=1
    # If no park matches the search criteria, print alternate message
    if count==0:
        print("There are no national parks for the search text of '" + search + "'.")

# EXTRA CREDIT

# Function Name: printOldestPark
# Input: parksList is a list containing parks represented by dictionaries
# Return: None
# Side Effect: Prints information to output
# Description: Prints information for the oldest park in dictionary
def printOldestPark(parksList):
    # Set baseline values for oldest date and code
    # Use first entry as base
    oldestDate=parksList[0]["Date"]
    # Split so the date for easy comparison
    oldestDate=oldestDate.split("-")
    code=parksList[0]["Code"]
    # Iterate through the park list
    for park in parksList:
        # For every park, create a list using split() on the date
        date=park["Date"].split("-")
        # If the year is less than current lowest year, we have a new oldest park
        if date[0]<oldestDate[0]:
            oldestDate=date
            code=park["Code"]
        # If the years are equal
        elif date[0]==oldestDate[0]:
            # Check if the month is earlier than the current lowest month
            if date[1]<oldestDate[1]:
                oldestDate = date
                code = park["Code"]
            # If year and month are both equal
            elif date[1]==oldestDate[1]:
                # Check if the date is earlier than the current earliest month
                if date[2]<oldestDate[2]:
                    oldestDate = date
                    code = park["Code"]
    # Look for the park code in our park list and print out all of its information
    for park in parksList:
        if code==park["Code"]:
            # Print all of its information
            print(park["Name"], "(" + park["Code"] + ")")
            print("\tLocation:", park["State"])
            print("\tArea:", park["Acres"], "acres")
            # Use tasks.getDate() function to get correct format
            print("\tDate Established:", tasks.getDate(park["Date"]))
            print("\tDescription:", park["Description"])

# Function Name: printMostParkState
# Input: parksList is a list containing parks represented by dictionaries
# Return: None
# Side Effect: Prints information to output
# Description: Finds the state with the most parks and prints information on all parks in that state
def printMostParkState(parksList):
    # Create an empty dictionary
    states={}
    # Iterate through the entire parksList
    for park in parksList:
        # For parks in multiple states, separate them and check them individually
        if "&" in park["State"]:
            stateList=park["State"].split(" & ")
            # Loop through the separated state list and check if they exist in dictionary
            for state in stateList:
                # If state is not already in the dictionary, set the state with that value equal to 1
                if state not in states:
                    states[state] = 1
                # If it is already in the dictionary, increment the count
                else:
                    states[state] += 1
        # For parks in a single state
        else:
            # Check if state is already in dictionary
            if park["State"] not in states:
                states[park["State"]]=1
            # If not, increment
            else:
                states[park["State"]]+=1
    # Create a variable to hold the max parks in a state and the corresponding state
    max=-1
    state=""
    # Iterate through states dictionary
    for item in states:
        # If the number of states is greater than the current max
        if states[item]>max:
            # Set the new max and state values
            state=item
            max=states[item]
    # Print that state with the most parks
    print("The state with the most parks is",state)
    print("")
    # Find all parks in the state
    for park in parksList:
        # Print basic information
        if state in park["State"]:
            print(park["Name"], "(" + park["Code"] + ")")
            print("\tLocation:", park["State"])
            print("\tArea:", park["Acres"], "acres")
            # Use tasks.getDate() function to get correct format
            print("\tDate Established:", tasks.getDate(park["Date"]))
            print("")