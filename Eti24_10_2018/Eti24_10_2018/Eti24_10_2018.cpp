#include <iostream>
#include <utility>

using namespace std;

pair<bool, bool> properties(bool* necklace, int n) {
	bool isZero = false, isOne = false;
	for (int i = 0; i < n; i++) {
		if (necklace[i] == true) isOne = true;
		else isZero = true;
	}
	pair<bool, bool> resoultZeroOne;
	resoultZeroOne.first = isZero;
	resoultZeroOne.second = isOne;
	return resoultZeroOne;
}

bool isEven(bool* necklace, int n, int beginning, int length) {
	bool evenResoult;
	if (necklace[beginning]) evenResoult = false;
	else evenResoult = true;
	for (int i = beginning+1; i < beginning + length; i++) {
		if (necklace[i]) {
			if (evenResoult) evenResoult = false;
			else evenResoult = true;
		}
	}
	return evenResoult;
}

int main() {

	// zamiana 
	int q;
	cin >> q;
	for (int ask = 0; ask < q; ask++) {
		int n, m;
		cin >> n >> m;
		bool* necklace1 = new bool[n];
		bool* necklace2 = new bool[m];
		int stone;
		for (int i = 0; i < n; i++) {
			cin >> stone;
			necklace1[i] = stone % 2;
		}
		for (int i = 0; i < m; i++) {
			cin >> stone;
			necklace2[i] = stone % 2;
		}

		// sytuacja n i m =1
		if (m == 1 && n == 1) {
			if (necklace1[0] != necklace2[0]) {
				cout << 0 << endl;
				continue;
			}
			else {
				cout << 1 << endl;
				continue;
			}
		}

		pair<bool, bool> zeroOne1, zeroOne2;
		zeroOne1 = properties(necklace1, n);
		zeroOne2 = properties(necklace2, m);

		bool nSmaller;

		if (n < m)nSmaller = true;
		else nSmaller = false;

		if ((zeroOne1.first == false && zeroOne2.first == false && n%2==m%2)
			|| (zeroOne1.second == false && zeroOne2.second == false)) {
			if (nSmaller) {
				cout << n << endl;
				continue;
			}
			else {
				cout << m << endl;
				continue;
			}
		}
		//sprawdzenie czy w wiekszym jest taki sam jak mniejszy
		bool smallEven, found = false, bigEven;
		bool *biggerNec, *smallerNec;
		int bigger, smaller;
		if (nSmaller) {
			bigger = m;
//			smallEven = isEven(necklace1, n, 0, n);
			smaller = n;
			biggerNec = necklace2;
			smallerNec = necklace1;
		}
		else {
			bigger = n;
			//smallEven = isEven(necklace2, m, 0, m);
			smaller = m;
			biggerNec = necklace1;
			smallerNec = necklace2;
		}

		for (int i = smaller; i > 0; i--) {
			for (int j = 0; j <= smaller - i; j++) {
				smallEven = isEven(smallerNec, smaller, j, i);
				for (int k = 0; k <= bigger - i; k++) {
					bigEven = isEven(biggerNec, bigger, k, i);
					if (smallEven == bigEven) {
						found = true;
						break;
					}
				}
				if (found) break;
			}
			if (found) {
				cout << i << endl;
				break;
			}
		}
		if (!found) cout << 0 << endl;


		//for (int i = 0; i < bigger; i++) {
		//	if (smallEven == isEven(biggerNec, bigger, i, smaller)) {
		//		found = true;
		//	}
		//}
		//if (found) cout << smaller << endl;
		//else cout << smaller - 1 << endl;
		
		delete[] necklace1;
		delete[] necklace2;
		biggerNec = NULL;
		smallerNec = NULL;
	}
	return 0;
}