from itertools import product
import re
import string
import os.path
from os import path

# Description: 
#   To call this function, pass the function name into the CallProcedure function
# Example:
#   callProcedure("PurchasedItems");
# Output:
#   Outputs a list of items including the number of times they were purchased
# Return:
#   None

def PurchasedItems():
    # Open file containing products purchased
    products = open("purchased_items.txt", "r")

    # Create a empty dictionary to store purchased items
    productList = dict()

    # Iterate over each line in products, trim whitespace
    # and convert all entries to lowercase for better comparison
    for line in products:
        # Trim whitespace to provide more consistent data
        line = line.strip()

        # Convert entries to lowercase making all entries uniform
        # and easier to compare
        product = line.lower()

        # Compare entry to list for a match, if entry exists increment
        # the word counter.
        if product in productList:
            productList[product] += 1
        else:
            productList[product] = 1

    # Display all items from list with number of purchases
    for key in list(productList.keys()):
        print("\t", key, ":", productList[key]);

    # Close file
    products.close()

# Description: 
#   To call this function, pass the function name into
#   CallIntFunc including the item to count the number of purchases
# Example:
#   callIntFunc("CountPurchasedItems", searchItem);
# Output:
#   Outputs the number of purchases a particular item had on a given day
# Return:
#   int numOfPurchases
def CountPurchasedItems(searchItem):
    # Open file containing products purchased
    products = open("purchased_items.txt", "r")

    # Create variable to store the number of times 
    # the searchItem is found
    numOfPurchases = 0

    # Convert searchItem to lowercase, making it easier to find 
    # the item being search
    searchItem = searchItem.lower()

    # Iterate over the products file line by line, trim whitespace
    # convert to lowercase for more consistent searching
    for product in products:
        
        # Trim whitespace to make entries more consistent
        product = product.strip()

        # Convert product to lower making it easier to find match
        item = product.lower()

        # Compare current entry to searchItem, if match is found
        # increment the counter by one
        if item == searchItem:
            numOfPurchases += 1

        # Return the number of purchases indicating the number of
        # occurrences of the searchItem
    return numOfPurchases

    # Close file
    products.close()


# Description: 
#   To call this function, pass the function name into
#   CallProcedure function
# Example:
#   callProcedure("CalcFrequency");
# Output:
#   Outputs to a document (frequency.dat) with 
# Return:
#   int numOfPurchases
def OutputPurchasedList():
    # Open file containing products purchased
    purchases = open("purchased_items.txt", "r")

    # Create/Open frequency.dat file
    frequency = open("frequency.dat", "w")
    
    # Create an empty dictionary to store the frequency
    # of purchased items
    productList = dict()

    # Iterate over each line in products, trim whitespace
    # and convert all entries to lowercase for better comparison
    for line in purchases:
        # Trim whitespace to provide more consistent data
        line = line.strip()

        # Convert entries to lowercase making all entries uniform
        # and easier to compare
        product = line.lower()

        # Compare entry to list for a match, if entry exists increment
        # the word counter.
        if product in productList:
            productList[product] += 1
        else:
            productList[product] = 1

    # Write each entry to frequency.dat
    for key in list(productList.keys()):
        # Convert the key-value pair to a string and then a new line
        frequency.write(str(key.lower()) + " " + str(productList[key]) + "\n")

    # Close files
    purchases.close()
    frequency.close()


    
