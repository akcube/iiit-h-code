class RE:
	def check_site(site:str):
		if(len(site) != 6):
			return False
		if(site[1:5] == "AATT" and site[0] in ['A', 'G'] and site[5] in ['T', 'C']):
			return True
		return False