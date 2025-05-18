#include<bits/stdc++.h>

int main(int argc, char *argv[]){
	std::string line;
	while(std::getline(std::cin, line)){
		std::int32_t v, tmp;
		std::vector<std::int32_t> adj;
		std::stringstream ss(line);
		ss >> v;
		while(ss >> tmp) adj.emplace_back(tmp);
		for(int i=0; i < adj.size(); i++)
			for(int j=i+1; j < adj.size(); j++)
				std::cout << adj[i] << '-' << adj[j] << '\t' << v << '\n';
	}
}

