#include<bits/stdc++.h>

int main(int argc, char *argv[]){
	std::string line;
	std::string current_key = "#";
	std::vector<std::int32_t> adj;

	auto publish = [&](){
		if(current_key == "#") return;
		std::replace(current_key.begin(), current_key.end(), '-', ' ');
		std::cout << current_key << '\t';
		std::sort(adj.begin(), adj.end());
		for(auto &v : adj) std::cout << v << ' ';
		std::cout << '\n';
	};

	while(std::getline(std::cin, line)){
		std::string key;
		std::int32_t v;
		std::vector<std::int32_t> tmp;
		std::stringstream ss(line);
		ss >> key;
		if(current_key == key) {
			while(ss >> v) adj.emplace_back(v);
		}
		else {
			publish();
			adj.clear();
			current_key = key;
			while(ss >> v) adj.emplace_back(v);
		}
	}
	publish();
}

