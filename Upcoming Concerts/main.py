# Name: Jonathan Wong
# Email: Jzwong@usc.edu
# Section: 31885
# Spring 2022
# Homework 9

import ssl
from urllib.parse import urljoin
import urllib.request
import os
import math

from bs4 import BeautifulSoup as bs

# Description: Takes in a website URL and stores it
# Inputs: A string containing a website URL, ctx, and filename to store the website as
# Returns: None
# Side effects: Saves a new file with contents of URL
def retrieve_and_store_webpage(url, ctx, fn):
    page = urllib.request.urlopen(url, context=ctx)
    soup = bs(page.read().decode('utf-8'), 'html.parser')
    f = open(fn, 'w', encoding='utf-8')
    print(soup, file=f)
    f.close()

# Description: Takes in a website url and loads the webpage
# Inputs: String containing the url and ctx
# Returns: A soup object with read file
# Side effects: None
def load_webpage(url, ctx):
    page = urllib.request.urlopen(url, context=ctx)
    return bs(page.read(), 'html.parser')

# Description: Converts relative file path to a URL
# Inputs: Relative file path
# Returns: A file name
# Side effects: None
def relative_file_path_to_URL(relative_file_path):
    # expand relative to absolute
    absolute_file_path = os.path.abspath(relative_file_path)
    # prepend file:// on UNIX-style OSes like Mac and Linux and file:/// on Windows
    file_name_url = urljoin('file:', urllib.request.pathname2url(absolute_file_path))
    return file_name_url

def main():
    # Ignore certificate errors
    ctx = ssl.create_default_context()
    ctx.check_hostname = False
    ctx.verify_mode = ssl.CERT_NONE

    # URL for first website
    url = 'https://www.blackcatdc.com/schedule.html'

    # Store URL as html file
    # retrieve_and_store_webpage(url, ctx, 'sites/blackcat.html')

    # Creates a relative file path
    relative_file_path = 'sites/blackcat.html'
    file_name_url = relative_file_path_to_URL(relative_file_path)

    # Store blackcat headliners and dates performing
    soup = load_webpage(file_name_url, ctx)
    headline = soup.find_all('h1', class_='headline')
    dates = soup.find_all('h2', class_='date')

    # Output
    print("Concerts coming up at Black Cat:")
    for i in range(len(dates)):
        print('\t' + dates[i].text)
        print('\t\t' + headline[i].text)
    print()

    # Second URL
    url = 'https://www.residentdtla.com/events/'
    # Store URL as html file
    # retrieve_and_store_webpage(url, ctx, 'sites/resident.html')

    # Create relative file path
    relative_file_path = 'sites/resident.html'
    file_name_url = relative_file_path_to_URL(relative_file_path)

    # Store Resident headliners and performing dates
    soup = load_webpage(file_name_url, ctx)
    headline = soup.find_all('h2', class_='headliners summary')
    dates = soup.find_all('h2', class_='dates')
    # Output
    print("Concerts coming up at the Resident:")
    # Issue with overprinting, weird fix by dividing the range
    for i in range(math.floor(len(dates)/3)):
        print('\t' + dates[i].text.strip())
        print('\t\t' + headline[i].text.strip())

if __name__ == "__main__":
    main()
