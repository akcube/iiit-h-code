dnatomrna = {
	'a' : 'u', 'c' : 'g', 't' : 'a', 'g' : 'c'
}

class utils:

	def DNAtomRNA(DNA:str):
		return DNA.replace("t", "u")
		# global dnatomrna
		# for c in DNA:
		# 	c = dnatomrna[c]
		# return DNA

class CodonTable:
	STOP = ["uaa", "uag", "uga"]
	START = ["aug"]
	mp = {
		"uuu": "Phe",
	    "uuc": "Phe",
	    "uua": "Leu",
	    "uug": "Leu",
	    "ucu": "Ser",
	    "ucc": "Ser",
	    "uca": "Ser",
	    "ucg": "Ser",
	    "uau": "Tyr",
	    "uac": "Tyr",
	    "uaa": "Stop",
	    "uag": "Stop",
	    "ugu": "Cys",
	    "ugc": "Cys",
	    "uga": "Stop",
	    "ugg": "Trp",
	    "cuu": "Leu",
	    "cuc": "Leu",
	    "cua": "Leu",
	    "cug": "Leu",
	    "ccu": "Pro",
	    "ccc": "Pro",
	    "cca": "Pro",
	    "ccg": "Pro",
	    "cau": "His",
	    "cac": "His",
	    "caa": "Gln",
	    "cag": "Gln",
	    "cgu": "Arg",
	    "cgc": "Arg",
	    "cga": "Arg",
	    "cgg": "Arg",
	    "auu": "Ile",
	    "auc": "Ile",
	    "aua": "Ile",
	    "aug": "Met",
	    "acu": "Thr",
	    "acc": "Thr",
	    "aca": "Thr",
	    "acg": "Thr",
	    "aau": "Asn",
	    "aac": "Asn",
	    "aaa": "Lys",
	    "aag": "Lys",
	    "agu": "Ser",
	    "agc": "Ser",
	    "aga": "Arg",
	    "agg": "Arg",
	    "guu": "Val",
	    "guc": "Val",
	    "gua": "Val",
	    "gug": "Val",
	    "gcu": "Ala",
	    "gcc": "Ala",
	    "gca": "Ala",
	    "gcg": "Ala",
	    "gau": "Asp",
	    "gac": "Asp",
	    "gaa": "Glu",
	    "gag": "Glu",
	    "ggu": "Gly",
	    "ggc": "Gly",
	    "gga": "Gly",
	    "ggg": "Gly"
	}