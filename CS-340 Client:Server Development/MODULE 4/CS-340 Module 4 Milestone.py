# -------------------------------------------------------------------------
# Developer: Eric Wallace
# Platform : Python 3.11
# Course: CS-340  Client/Server Development
# Description: Creates new records and finds existing records in MongoDB
# Filename: Module 4 Milestone.py
# -------------------------------------------------------------------------
import pymongo
# Import the pymongo library


# Create a class to handle the database
class AnimalShelter:
    # Initialize the class
    def __init__(self, host, port, db_name, collection_name, username, password):
        self.result = None
        self.client = pymongo.MongoClient(host, port, username=username, password=password, authSource='admin')
        self.db = self.client[db_name]
        self.collection = self.db[collection_name]
        if self.collection is not None:
            print("Connection successful")
        else:
            print("Connection failed")

    """Insert a new animal into the collection"""
    def create(self, data):
        result = self.collection.insert_one(data)
        if result.acknowledged is True:
            return True # Return true if the insert was successful
        else:
            return False # Return false if the insert was unsuccessful

    """ Find an animal by data received"""
    def find(self, data):
        self.result = self.collection.find(data)
        if self.result is not None:
            return self.result # Return the result if the find was successful
        else:
            raise Exception("No records found, because data supplied did not match any records")