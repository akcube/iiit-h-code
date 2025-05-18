#include<bits/stdc++.h>

int main(int argc, char *argv[]){
	std::string line;
	std::int32_t current_node = -1;
	std::vector<std::int32_t> adj;

	auto publish = [&](){
		std::cout << current_node << '\t';
		for(auto &v : adj) std::cout << v << ' ';
		std::cout << '\n';
	};

	while(std::getline(std::cin, line)){
		std::int32_t u, v;
		std::vector<std::int32_t> tmp;
		std::stringstream ss(line);
		ss >> u;
		while(ss >> v) tmp.emplace_back(v);
		if(current_node == u) {
			std::vector<std::int32_t> dst;
			std::merge(tmp.begin(), tmp.end(), adj.begin(), adj.end(), std::back_inserter(dst));
			std::swap(dst, adj);
		}
		else {
			if(current_node != -1) publish();
			current_node = u; adj = tmp;
		}
	}
	publish();
}

