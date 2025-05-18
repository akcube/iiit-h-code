#include<bits/stdc++.h>

int main(int argc, char *argv[]){
	std::string line;
	std::string current_key = "#";
	std::vector<std::int32_t> adj;

	auto publish = [&](){
		if(current_key == "#") return;
		std::cout << current_key << '\t';
		for(auto &v : adj) std::cout << v << ' ';
		std::cout << '\n';
	};

	while(std::getline(std::cin, line)){
		std::string key;
		std::int32_t v;
		std::stringstream ss(line);
		ss >> key >> v;
		if(current_key == key) adj.emplace_back(v);
		else {
			publish();
			current_key = key; adj = {v};
		}
	}
	publish();
}

