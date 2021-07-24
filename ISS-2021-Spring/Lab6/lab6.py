import json;
import matplotlib.pyplot as plt;
from wordcloud import WordCloud, STOPWORDS

class RestaurantReviews:

	def __init__(self, file):
		f = open(file, "r");
		self.jsonData = json.load(f);
		f.close();
		print("JSON has been loaded");

	def __getRestaurant(self, res_name):
		restaurant = None;
		for name in self.jsonData:
			if(name['name']==res_name):
				restaurant=name;
		return restaurant;

	def avg_rating(self, name):
		restaurant = self.__getRestaurant(name);

		if(restaurant==None):
			return None;

		total_rating = 0.0;
		num_ratings = 0;
		
		for review in restaurant['reviews']:
			total_rating += float(review['rating']);
			num_ratings+=1;

		if(num_ratings==0):
			return 0;
		return total_rating/num_ratings;

	def reviews_to_file(self):
		f = open("all_reviews.txt", "w");
		for name in self.jsonData:
			for review in name['reviews']:
				f.write(review["text"]+"\n")

		print("All reviews have been stored.");
		f.close();

	def plot_bargraph(self, name):
		restaurant = self.__getRestaurant(name);

		if(restaurant==None):
			print("Restaurant not found.");
			return;

		rating_arr = [];

		for review in restaurant['reviews']:
			rating_arr.append(int(review['rating']));

		freq = [];
		for x in range(6):
			freq.append(rating_arr.count(x));

		f1 = plt.figure(1);
		plt.tight_layout()
		plt.xlabel('Ratings');
		plt.ylabel('Frequency');
		plt.bar(x=range(6), height=freq);
		f1.savefig("plot.png");
		f1.clf();

		print("Bar plot has been generated.");

	def create_wordcloud(self):

		bigsentence = '';
		for name in self.jsonData:
			for review in name['reviews']:
				bigsentence += review['text'] + ' ';

		stopwords = set(STOPWORDS);
		wordcloud = WordCloud(width = 800, height = 800, background_color ='white', stopwords = stopwords, min_font_size = 10).generate(bigsentence);

		f2 = plt.figure(2, figsize = (8, 8), facecolor = None);	
		plt.imshow(wordcloud);
		plt.axis("off");
		plt.tight_layout(pad = 0);
		f2.savefig("cloud.png");
		f2.clf();

		print("Word cloud has been generated.");



Restaurants = RestaurantReviews("hyderabad_restaurant_reviews.json");

key = None;

while(key!=5):
	inp = input();
	key = int(inp.split(' ', 1)[0]);
	if(key==1):
		resname = inp.split(' ', 1)[1];
		rating = Restaurants.avg_rating(resname);

		if(rating==None):
			print("Restaurant not found");
		else:
			print("Rating: "+str(rating));

	elif(key==2):
		Restaurants.reviews_to_file();

	elif(key==3):
		resname = resname = inp.split(' ', 1)[1];
		Restaurants.plot_bargraph(resname);

	elif(key==4):
		Restaurants.create_wordcloud();

	elif(key!=5):
		print("Invalid key, please try again");
