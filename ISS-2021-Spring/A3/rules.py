import json #import JSON library to parse json

#Class to read rules.json and setup a query interface
class JSONParser:
	
	def __init__(self, filename:str):
		'''Constructor function
		Reads json data from the given file and populates it's internal 
		dictionary for lookup requests
		'''
		self.LUT = {} # Initializes the dictionary
		self.headers = [] # Initializes the list

		# Handle exceptions if unable to open file
		try:
			# Open the file and parse the json data 
			with open(filename, 'r') as f:
				jsonData = json.load(f)

			# Populate the dictionary with results for all the given rules
			for rule in jsonData:
				self.LUT[tuple(rule["fields"].values())] = rule["results"]
				self.headers = list(rule["fields"].keys())

		except Exception as e: # Handle error gracefully
			print("Unable to open file. Check if file exists / insufficient permissions")
			print(e)

	def query(self, q:list):
		'''Return the result for queried spec (expected as list)'''
		return self.LUT[tuple(q)]

	def getHeaders(self):
		'''Return the required headers for successful query'''
		return self.headers;