import sqlite3 # import sqlite3

# class to query database
class SQLQueryObject:

	def __init__(self, dbname:str):
		self.db = sqlite3.connect(dbname)	
		self.cur = self.db.cursor()

	def query(self, q:str):
		res = self.cur.execute(q)
		return res

	def print(self, res, cols:list):
		for i in cols:
			print(", ".join([x[i] for x in res]), end='')
		print("")

	def getCount(self, res):
		return len(list(res))

db = SQLQueryObject("ipl.db") # Init class object

# Task 1.1
print("Umpire names: ", end='')
res = db.query("SELECT * FROM Umpire LIMIT 10")
db.print(res, [1])

# Task 1.2
print("The number of countries the umpires belong to are: ", end='')
res = db.query("SELECT DISTINCT Umpire_Country FROM Umpire")
print(db.getCount(res))

# Task 1.3
print("Venue names in alphabetical order: ", end='')
res = db.query("SELECT Venue_Name FROM Venue ORDER BY Venue_Name ASC")
db.print(res, [0])

# Task 1.4
print("Australian players: ", end='')
res = db.query("SELECT * FROM Player WHERE Country_Name = 5")
db.print(res, [1])

# Task 1.5
print("The number of matches CSK won more than RCB: ", end="")
res = db.query("SELECT * FROM Match WHERE Match_Winner = (SELECT Team_Id FROM Team WHERE Team_Name = 'Chennai Super Kings')")
cskW = db.getCount(res)
res2 = db.query("SELECT * FROM Match WHERE Match_Winner = (SELECT Team_Id FROM Team WHERE Team_Name = 'Royal Challengers Bangalore')")
rcbW = db.getCount(res)
print(cskW-rcbW)

