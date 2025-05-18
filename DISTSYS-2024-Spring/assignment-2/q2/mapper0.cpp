#include<bits/stdc++.h>

int main(int argc, char *argv[]){
	std::string line;
	std::vector<std::pair<std::int32_t, std::int32_t>> tmp;
	while(std::getline(std::cin, line)){
		std::int32_t u, v;
		std::stringstream ss(line);
		ss >> u >> v;
		std::cout << u << '\t' << v << '\n';
		std::cout << v << '\t' << u << '\n';
	}
}

