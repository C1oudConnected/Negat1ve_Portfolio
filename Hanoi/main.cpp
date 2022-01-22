#include <iostream>
#include <vector>

const int MAX = 6;
std::vector<int> twrs[3]{};

void prnt(int i, int start = 0) {
	if (start >= twrs[i].size())
		std::cout << '_';
	else
		for (int j = start; j < twrs[i].size(); j++)
			std::cout << twrs[i][j] << ' ';
}

void prnt() {
	std::cout<<"==========================" << std::endl;
	for (int i = 0; i < 3; i++) {
		prnt(i);
		std::cout << std::endl;
	}
}

void hanoi(int from, int to, int start) {
	int sub_high = twrs[from].size() - start; // Hight of the subtower to move

	// Moving 1 disk;
	if(sub_high == 1) {
		twrs[to].push_back(twrs[from].back());
		twrs[from].pop_back();

		prnt();
		return;
	}


	// Moving a subtower
	int swp = 3 - (from + to); 		// Index of swap-tower
	int size_swp = twrs[swp].size();
	hanoi(from, swp, start + 1);		// Move everything but first disk to swap.
	hanoi(from, to, start);				// Move first disk to destination.
	hanoi(swp, to, size_swp);			// Move swap to reconstruct subtower in the dest.
}

int main(int argc, char** argv) {

	for (int i = MAX; i >= 1; i--)
		twrs[0].push_back(i);

	twrs[1].clear();
	twrs[2].clear();

	prnt();
	hanoi(0,2,0);
}
