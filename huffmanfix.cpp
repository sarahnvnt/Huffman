#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

// Simpul tree
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

// Fungsi untuk mengalokasikan simpul tree baru
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// Objek perbandingan yang digunakan untuk menyusun tumpukan
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// Item prioritas tertinggi memiliki frekuensi terendah
		return l->freq > r->freq;
	}
};

// Melintasi huffman tree dan menyimpan kode huffman di map
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	// Menemukan simpul leaf pada huffman tree
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// Melintasi huffman tree dan men-decode string yang telah di-enconde
void decode(Node* root, int &index, string str)
{
	if (root == nullptr) {
		return;
	}

	// Menemukan simpul leaf pada huffman tree
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

// Membuat prosedur huffman tree dan men-decode string yang diberikan
void buildHuffmanTree(string text)
{
	cout << "\nString awal  :\n" << text << '\n';
	
	// Hitung frekuensi kemunculan setiap karakter dan simpan di map
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	// Membuat prioritas queue untuk menyimpan simpul dari huffman tree
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Buat simpul leaf untuk setiap karakter dan tambahkan ke prioritas queue
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// Melooping sampai ada lebih dari satu simpul dalam queue
	while (pq.size() != 1)
	{
		// Menghapus dua simpul dengan prioritas tertinggi (frekuensi terendah) dari queue
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// Membuat simpul internal baru dengan dua node ini sebagai children dan dengan frekuensi yang sama dengan jumlah dari frekuensi dua simpul 
		// Tambahkan simpul baru ke prioritas queue
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// Root menyimpan pointer ke root dari huffman Tree
	Node* root = pq.top();

	// Melintasi huffman tree, menyimpan kode huffman di map, dan mencetaknya
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "\nHuffman Codes-nya sebagai berikut :\n";
	for (auto pair: huffmanCode) {
		cout << pair.first << " " << pair.second << "\n";
	}

	// Mencetak string yang di-encode
	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	cout << "\nString yang telah di-encode:\n" << str << "\n";

	// Melintasi huffman tree lagi, perbedaannya kali ini men-decode string yang telah di-encode
	int index = -1;
	cout << "\nString yang telah di-decode : \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}

// Main program untuk memanggil prosedur buildHuffmanTree 
int main()
{
	string text;
	
	cout << "\t\t\tProgram Huffman Codes\n";
	cout << "\t\t\t=====================\n";

	cout << "Silahkan Masukan String :\n"; 
	getline(cin, text);

	buildHuffmanTree(text);

	cout << "\n";

	return 0;
}
