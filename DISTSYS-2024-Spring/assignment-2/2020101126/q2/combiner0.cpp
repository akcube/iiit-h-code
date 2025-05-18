#include<bits/stdc++.h>

int main(int argc, char *argv[]){
	std::string line;
	std::int32_t current_node = -1;
	std::vector<std::int32_t> adj;

	auto publish = [&](){
		std::cout << current_node << '\t';
		std::sort(adj.begin(), adj.end());
		for(auto &v : adj) std::cout << v << ' ';
		std::cout << '\n';
	};

	while(std::getline(std::cin, line)){
		std::int32_t u, v;
		std::stringstream ss(line);
		ss >> u >> v;
		if(current_node == u) adj.emplace_back(v);
		else {
			if(current_node != -1) publish();
			current_node = u; adj = {v};
		}
	}
	publish();
}

