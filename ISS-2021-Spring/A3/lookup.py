import csv # import csv library to r/w to csv files
from rules import JSONParser # import our JSON parser to query results

# Handle exceptions if unable to open file(s)
try:
	# Initialize the JSON parser object with the file that contains our rules
	Results = JSONParser("rules.json")

	# Open the csv files to read / write to
	with open("data.csv", "r") as infile, open ("results.csv", "w") as outfile:
		csv_reader = csv.DictReader(infile) # Use dict reader for easier header r/w
		csv_writer = csv.writer(outfile, lineterminator='\n') # Get csv writer object

		# Read and write headers to results.csv
		headers = csv_reader.fieldnames 
		csv_writer.writerow(headers + ["results"])

		# Get required headers for making a query
		requiredHeaders = Results.getHeaders()

		# For every entry in data.csv fetch result and populate results.csv
		for entry in csv_reader:
			values = list(entry.values()) # Get entries in list form
			q = [entry[x] for x in requiredHeaders] # Form query
			result = Results.query(q) # Query result
			csv_writer.writerow(values + [result]) # Write back entry with appended result

except Exception as e: # Handle errors gracefully
	print("Error: ")
	print(e)