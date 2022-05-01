class utils:
	def get_complement(DNA:str):
		retval = ""
		pairs = {
	    	"a": "t",
	    	"c": "g",
	    	"g": "c",
	    	"t": "a"
		}
		for c in DNA:
			retval += pairs[c]
		return retval