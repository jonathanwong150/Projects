# Jonathan Wong, jzwong@usc.edu
# ITP 115, Fall 2021
# Section: 31856
# Final Project
# main_wong_jonathan.py
# Description: Main file that will use functions from other files

import tasks
import interface

def main():
    print("National parks")
    print("")
    # Generates a list of all parks
    parkList=tasks.createListOfParks("national_parks.csv")
    # Keep running loop until Q or q is inputted
    while True:
        # User the interface functions to diplay menu and get input
        interface.displayMenu(interface.getMenuDict())
        choice=interface.getUserInput(interface.getMenuDict())
        print("")
        # Call appropriate function using branching
        if choice=="A":
            interface.printAllParks(parkList)
        elif choice=="B":
            interface.printParksInState(parkList)
        elif choice=="C":
            interface.printLargestPark(parkList)
        elif choice=="D":
            interface.printParksForSearch(parkList)
        elif choice=="E":
            interface.printOldestPark(parkList)
        elif choice=="F":
            interface.printMostParkState(parkList)
        elif choice=="Q":
            # If user inputs a Q, quit program
            return
        print("")

main()