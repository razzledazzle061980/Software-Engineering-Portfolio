# -------------------------------------------------------------------------
# Developer: Eric Wallace
# Platform : Python 3.11
# Course: CS-340  Client/Server Development
# Description: Creates new records and finds existing records in MongoDB
# Filename: Module 4 Milestone.py
# -------------------------------------------------------------------------

# Import the pymongo library
from pymongo import MongoClient
from bson.json_util import dumps

"""Create a class to handle the database"""
class AnimalShelter:
    # Initialize the class
    def __init__(self, host, port, db_name, collection_name, username, password):
        self.result = None
        self.client = MongoClient(host, port, username=username, password=password, authSource='admin')
        self.db = self.client[db_name] # Connect to the database
        self.collection = self.db[collection_name] # Connect to the collection
        if self.collection is not None:
            print("Connection successful") # Return Connection successful if the connection was successful
        else:
            print("Connection failed") # Return Connection failed if the connection was unsuccessful

    """Insert a new animal into the collection"""
    def create(self, data):
        self.result = self.collection.insert(data)
        if self.result is not None:
            return True # Return true if the insert was successful
        else:
            return False # Return false if the insert was unsuccessful

    """ Find an animal by data received"""
    def read(self, data):
        self.result = self.collection.find(data)
        if self.result is not None:
            return self.result # Return the result if the find was successful
        else:
            raise Exception("No records found, because data supplied did not match any records") # Raise an exception if the find was unsuccessful

    """ Update an animal by data received"""
    def update(self, data, new_data):
        new_values = {"$set": new_data}
        self.result = self.collection.update(data, new_values)
        if self.result is not None:
            if self.result.modified_count >= 1:
                values = self.read(data) # Return the result if the update was successful by finding the record(s) that were updated
                return dumps(values, indent=2)
            elif self.result == 0:
                return "No records were updated, because data supplied did not match any records"
        else:
            raise Exception("Error updating record") # Raise an exception if the update was unsuccessful

    """ Delete an animal by data received"""
    def delete(self, data):
        self.result = self.collection.delete_many(data)
        if self.result is not None:
            return dumps(self.result.raw_result, indent=2) # Return the deleted data if the delete was successful
        else:
            raise Exception("Error deleting record") # Raise an exception if the delete was unsuccessful