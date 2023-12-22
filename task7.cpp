#include "task7.h"

ConsoleFor7::ConsoleFor7()
{
}

ConsoleFor7::~ConsoleFor7()
{
}

int ConsoleFor7::run()
{
	cout << "Выберите номер задания из работы 7:\n";
	cout << "1. Сжать фразу из консоли методом Шеннона-Фано\n";
	cout << "2. Сжать текстовый файл методом Шеннона-Фано\n";
	cout << "3. Сжать двоичный код методом LZ\n";
	cout << "4. Сжать фразу методом LZ78\n";
	cout << "5. Сжать фразу из консоли методом Хаффмана\n";
	cout << "6. Сжать текстовый файл методом Хаффмана (без записи таблицы декодирования)\n";
	cout << "7. Сжать текстовый файл методом Хаффмана (вместе с таблицей декодирования)\n";
	cout << "0. Перейти к выбору работы\n";
	string key;
	int num;
	while (1)
	{
		getline(cin, key);
		if (!numcheck(key, 0, 7))
		{
			cout << "Некорректный ввод! Попробуйте ещё раз: ";
			continue;
		}
		num = stoi(key);
		if (num == 1)
		{
			cout << "Введите фразу:" << endl;
			string toCompress;
			getManyLines(cin, toCompress);
			pair<map<char, vector<bool>>, map<vector<bool>, char>> tables = shannonFano(toCompress);
			cout << "Таблица кодировки:" << endl;
			for (auto kv : tables.first)
			{
				cout << "'" << kv.first << "' = ";
				for (bool b : kv.second)
					cout << b;
				cout << endl;
			}
			vector<bool> compressed = codeSF(toCompress, tables.first);
			cout << "Сжатая фраза: ";
			for (bool b : compressed)
				cout << b;
			cout << endl << "Декодированная фраза: " << decodeSF(compressed, tables.second);
			cout << endl << "Коэффициент сжатия равен " << (double)toCompress.length() * sizeof(char) * 8 / compressed.size() << endl;
		}
		if (num == 2)
		{
			ifstream txtin = ifstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7test.txt", ios::in);
			pair<map<char, vector<bool>>, map<vector<bool>, char>> tables = shannonFano(txtin);
			txtin.close();
			/*cout << "Таблица кодировки:" << endl;
			for (auto kv : tables.first)
			{
				cout << "'" << kv.first << "' = ";
				for (bool b : kv.second)
					cout << b;
				cout << endl;
			}*/
			txtin.open("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7test.txt", ios::in);
			ofstream binout = ofstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testbin.bin", ios::out | ios::binary);
			codeSF(txtin, binout, tables.first);
			txtin.close();
			binout.close();
			ifstream binin = ifstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testbin.bin", ios::in | ios::binary);
			ofstream txtout = ofstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testDec.txt", ios::out);
			decodeSF(binin, txtout, tables.second);
			binin.close();
			binout.close();
			cout << "Файл закодирован!" << endl;
			cout << "Коэффициент сжатия равен " << (double)filesystem::file_size("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7test.txt") / filesystem::file_size("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testbin.bin") << endl;
		}
		if (num == 3)
		{
			cout << "Введите двоичный код:" << endl;
			string toCompress;
			while (1)
			{
				getline(cin, toCompress);
				for (char c : toCompress)
					if (c != '0' && c != '1')
					{
						cout << "Введённая фраза не является двоичным кодом! Попробуйте ещё раз: " << endl;
						continue;
					}
				break;
			}
			vector<bool> toCode = strToVec(toCompress);
			pair<vector<bool>, map<vector<bool>, vector<bool>>> inf = codeLZ(toCode);
			cout << "Таблица кодировки:" << endl;
			for (auto kv : inf.second)
				cout << vecToStr(kv.first) << " -> " << vecToStr(kv.second) << endl;
			string compressed = vecToStr(inf.first);
			cout << "Сжатая фраза: " << compressed << endl;
			cout << "Декодированная фраза: " << vecToStr(decodeLZ(inf.first).first);
			cout << endl << "Коэффициент сжатия равен " << (double)toCompress.length() / compressed.length() << endl;
		}
		if (num == 4)
		{
			cout << "Введите фразу:" << endl;
			string toCompress;
			getManyLines(cin, toCompress);
			vector<pair<unsigned char, char>> compressed = codeLZ78(toCompress);
			cout << "Сжатая фраза: " << endl;
			for (auto p : compressed)
				cout << "<" << (int)p.first << ", " << p.second << "> ";
			cout << endl << "Декодированная фраза: " << decodeLZ78(compressed);
			cout << endl << "Коэффициент сжатия равен " << (double)toCompress.length() * sizeof(char) / compressed.size() / (sizeof(char) + sizeof(unsigned char)) << endl;
		}
		if (num == 5)
		{
			cout << "Введите фразу:" << endl;
			string toCompress;
			getManyLines(cin, toCompress);
			pair<map<char, vector<bool>>, map<vector<bool>, char>> tables = haffman(toCompress);
			cout << "Таблица кодировки:" << endl;
			for (auto kv : tables.first)
			{
				cout << "'" << kv.first << "' = ";
				for (bool b : kv.second)
					cout << b;
				cout << endl;
			}
			vector<bool> compressed = codeSF(toCompress, tables.first);
			cout << "Сжатая фраза: ";
			for (bool b : compressed)
				cout << b;
			cout << endl << "Декодированная фраза: " << decodeSF(compressed, tables.second);
			cout << endl << "Коэффициент сжатия равен " << (double)toCompress.length() * sizeof(char) * 8 / compressed.size() << endl;
		}
		if (num == 6)
		{
			ifstream txtin = ifstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7test.txt", ios::in);
			pair<map<char, vector<bool>>, map<vector<bool>, char>> tables = haffman(txtin);
			txtin.close();
			/*cout << "Таблица кодировки:" << endl;
			for (auto kv : tables.first)
			{
				cout << "'" << kv.first << "' = ";
				for (bool b : kv.second)
					cout << b;
				cout << endl;
			}*/
			txtin.open("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7test.txt", ios::in);
			ofstream binout = ofstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testbin.bin", ios::out | ios::binary);
			codeHaffman(txtin, binout, tables.first);
			txtin.close();
			binout.close();
			ifstream binin = ifstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testbin.bin", ios::in | ios::binary);
			ofstream txtout = ofstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testDec.txt", ios::out);
			decodeHaffman(binin, txtout, tables.second);
			binin.close();
			binout.close();
			cout << "Файл закодирован!" << endl;
			cout << "Коэффициент сжатия равен " << (double)filesystem::file_size("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7test.txt") / filesystem::file_size("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testbin.bin") << endl;
		}
		if (num == 7)
		{
			ifstream txtin = ifstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7test.txt", ios::in);
			ofstream binout = ofstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testbin.bin", ios::out | ios::binary);
			codeHaffman(txtin, binout);
			txtin.close();
			binout.close();
			ifstream binin = ifstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testbin.bin", ios::in | ios::binary);
			ofstream txtout = ofstream("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testDec.txt", ios::out);
			decodeHaffman(binin, txtout);
			binin.close();
			txtout.close();
			cout << "Файл закодирован!" << endl;
			cout << "Коэффициент сжатия равен " << (double)filesystem::file_size("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7test.txt") / filesystem::file_size("C:\\Users\\ivanp\\source\\repos\\siaod1\\siaod1\\7testbin.bin") << endl;
		}
		else if (num == 0)
			break;
		cout << "Выберите номер из меню: ";
	}
	return 0;
}



double totalProb(vector<Symbol>::iterator from, vector<Symbol>::iterator to)
{
	double total = 0;
	while (from != to)
	{
		total += from->prob;
		from++;
	}
	return total;
}

void leftPart(vector<Symbol>& v, vector<Symbol>::iterator from, vector<Symbol>::iterator to)
{
	for (vector<Symbol>::iterator it = from; it != to; it++)
		it->code.push_back(0);
	if (to - from < 2)
		return;

	double leftTotal = 0;
	vector<Symbol>::iterator it = from;
	while (leftTotal < totalProb(from, to) / 2)
	{
		leftTotal += it->prob;
		it++;
	}

	leftPart(v, from, it);
	rightPart(v, it, to);
}

void rightPart(vector<Symbol>& v, vector<Symbol>::iterator from, vector<Symbol>::iterator to)
{
	for (vector<Symbol>::iterator it = from; it != to; it++)
		it->code.push_back(1);
	if (to - from < 2)
		return;

	double leftTotal = 0;
	vector<Symbol>::iterator it = from;
	while (leftTotal < totalProb(from, to) / 2)
	{
		leftTotal += it->prob;
		it++;
	}

	leftPart(v, from, it);
	rightPart(v, it, to);
}

void partition(vector<Symbol>& v, vector<Symbol>::iterator from, vector<Symbol>::iterator to)
{
	if (to - from < 2)
		return;

	double leftTotal = 0;
	vector<Symbol>::iterator it = from;
	double half = totalProb(from, to) / 2;
	while (leftTotal < half)
	{
		leftTotal += it->prob;
		it++;
	}
	if (abs(half - leftTotal) > abs(half - leftTotal + (it - 1)->prob))
		it--;

	leftPart(v, from, it);
	rightPart(v, it, to);
}

pair<map<char, vector<bool>>, map<vector<bool>, char>> shannonFano(string s)
{
	vector<Symbol> symbols = { Symbol(s[0], 1, 0) };
	for (int i = 1; i < s.length(); i++)
	{
		vector<Symbol>::iterator it = symbols.begin();
		while (it != symbols.end())
		{
			if (it->name == s[i])
			{
				it->count += 1;
				break;
			}
			it++;
		}
		if (it == symbols.end())
			symbols.push_back(Symbol(s[i], 1, 0));
	}
	for (Symbol& sym : symbols)
		sym.prob = (double)sym.count / s.length();
	/*for (Symbol s : symbols)
		cout << "'" << s.name << "' " << s.count << " " << s.prob << endl;*/
	sort(symbols.rbegin(), symbols.rend());
	/*for (Symbol s : symbols)
		cout << "'" << s.name << "' " << s.count << " " << s.prob << endl;*/
	partition(symbols, symbols.begin(), symbols.end());

	map<char, vector<bool>> codeTable;
	map<vector<bool>, char> decodeTable;
	for (Symbol s : symbols)
	{
		codeTable.insert(make_pair(s.name, s.code));
		decodeTable.insert(make_pair(s.code, s.name));
	}

	return make_pair(codeTable, decodeTable);
}

pair<map<char, vector<bool>>, map<vector<bool>, char>> shannonFano(ifstream& in)
{
	string content = "";
	char buff;
	while (in)
	{
		in.get(buff);
		content += buff;
	}
	content.erase(content.end()-1);
	pair<map<char, vector<bool>>, map<vector<bool>, char>> tables = shannonFano(content);
	return tables;
}




vector<bool> codeSF(string text, map<char, vector<bool>> codeTable) 
{
	vector<bool> ans;
	for (char c : text)
		ans.insert(ans.end(), codeTable[c].begin(), codeTable[c].end());
	return ans;
};

void codeSF(ifstream& in, ofstream& out, map<char, vector<bool>> codeTable)
{
	char buff;
	vector<bool> toWrite = {};
	while (in.get(buff))
	{
		for (bool b : codeTable[buff])
			toWrite.push_back(b);
	}
	//toWrite.erase(toWrite.end() - codeTable[buff].size(), toWrite.end());
	char trash = (8 - toWrite.size() % 8) % 8;
	//cout << "Trash " << (int)trash << endl;
	out.write((char*)&trash, sizeof(char));
	for (int i = trash; i > 0; i--)
		toWrite.push_back(0);
	//for (bool b : toWrite)
		//cout << (int)b;
	//cout << endl;
	reverse(toWrite.begin(), toWrite.end());
	//for (bool b : toWrite)
		//cout << (int)b;
	//cout << endl;
	while (!toWrite.empty())
	{
		unsigned char byte = 0;
		bitset<8> bs = { byte };

		for (int i = 0; i < 8; i++)
		{
			//cout << toWrite[toWrite.size() - 1] << ": ";
			byte = byte << 1;
			if (toWrite[toWrite.size() - 1])
				byte++;
			toWrite.pop_back();
			bs = { byte };
			//cout << bs << " ";
		}

		//cout << endl;
		//cout << "WRITING " << (int)byte << endl;
		//cout << sizeof((char*)&byte) << endl;
		out.put(byte);
	}
	//cout << endl;
}




string decodeSF(vector<bool> coded, map<vector<bool>, char> decodeTable)
{
	string ans = "";
	reverse(coded.begin(), coded.end());
	vector<bool> curr = {};
	while (!coded.empty())
	{
		while (!decodeTable.contains(curr))
		{
			curr.push_back(coded[coded.size() - 1]);
			coded.pop_back();
		}
		ans += decodeTable[curr];
		curr.clear();
	}
	return ans;
}

void decodeSF(ifstream& in, ofstream& out, map<vector<bool>, char> decodeTable)
{
	vector<bool> toDecode = {};
	char byte;
	in.get(byte);
	int trash = byte;
	while (in.get(byte))
	{
		//cout << (unsigned int)byte << " ";
		for (int i = 7; i >= 0; i--)
			toDecode.push_back(byte >> i & 1);
	}
	//cout << trash;
	for (int i = 0; i < trash; i++)
		toDecode.pop_back();
	//for (bool b : toDecode)
		//cout << b;
	//cout << endl;
	reverse(toDecode.begin(), toDecode.end());
	vector<bool> buff;
	while (!toDecode.empty())
	{
		while (!decodeTable.contains(buff))
		{
			buff.push_back(toDecode[toDecode.size() - 1]);
			toDecode.pop_back();
		}
		out << decodeTable[buff];
		buff.clear();
	}
}

vector<bool> strToVec(string s)
{
	vector<bool> ans = {};
	for (char c : s)
		if (c == '1')
			ans.push_back(1);
		else
			ans.push_back(0);
	return ans;
}

string vecToStr(vector<bool> v)
{
	string ans = "";
	for (bool b : v)
		if (b)
			ans += "1";
		else
			ans += "0";
	return ans;
}

vector<bool> parseInt(int n)
{
	vector<bool> ans = {};
	while (n != 0)
	{
		ans.push_back(n % 2);
		n /= 2;
	}
	reverse(ans.begin(), ans.end());

	return ans;
}

pair<vector<bool>, map<vector<bool>, vector<bool>>> codeLZ(vector<bool> v)
{
	vector<bool> ans = {};
	map<vector<bool>, vector<bool>> dict = { make_pair(vector<bool>{0}, vector<bool>{0}), make_pair(vector<bool>{1}, vector<bool>{1}) };
	int index = 0;
	ans.push_back(v[index]);
	index++;
	int digits;
	int step = 1;

	while (index < v.size())
	{
		bool last = false;
		step++;
		digits = ceil(log2(step)) + 1;
		vector<bool> buff = { v[index] };
		while (dict.contains(buff))
		{
			index++;
			if (index == v.size())
			{
				last = true;
				break;
			}
			buff.push_back(v[index]);
		}
		if (last)
		{
			for (int i = dict[buff].size(); i < digits; i++)
				ans.push_back(0);
			for (bool b : dict[buff])
				ans.push_back(b);
		}
		else
		{
			index++;
			dict.insert(make_pair(buff, parseInt(dict.size())));
			//cout << vecToStr(buff) << " " << vecToStr(dict[buff]) << endl;
			bool newb = buff[buff.size() - 1];
			buff.pop_back();
			vector<bool> lz = {};
			for (bool b : dict[buff])
				lz.push_back(b);
			lz.push_back(newb);
			while (lz.size() < digits)
				lz.insert(lz.begin(), 0);
			for (bool b : lz)
				ans.push_back(b);
		}
	}
	return make_pair(ans, dict);
}
pair<vector<bool>, map<vector<bool>, vector<bool>>> decodeLZ(vector<bool> v)
{
	vector<bool> ans = {};
	map<vector<bool>, vector<bool>> dict = { make_pair(vector<bool>{0}, vector<bool>{0}), make_pair(vector<bool>{1}, vector<bool>{1}) };
	int index = 0;
	ans.push_back(v[index]);
	index++;
	int digits;
	int step = 1;

	while (index < v.size())
	{
		step++;
		digits = ceil(log2(step));
		vector<bool> buff = {};
		for (int i = 0; i <= digits; i++)
		{
			buff.push_back(v[index]);
			index++;
		}
		if (index == v.size())
		{
			while (!dict.contains(buff))
				buff.erase(buff.begin());
			for (bool b : dict[buff])
				ans.push_back(b);
		}
		else 
		{
			vector<bool> lz = { buff[buff.size() - 1] };
			buff.pop_back();
			while (!dict.contains(buff))
				buff.erase(buff.begin());
			for (bool b : dict[buff])
				lz.insert(lz.end() - 1, b);
			dict.insert(make_pair(parseInt(dict.size()), lz));
			//cout << vecToStr(parseInt(dict.size() - 1)) << " " << vecToStr(dict[parseInt(dict.size() - 1)]) << endl;
			for (bool b : lz)
				ans.push_back(b);
		}
	}
	return make_pair(ans, dict);
}

vector<pair<unsigned char, char>> codeLZ78(string s)
{
	vector<pair<unsigned char, char>> ans = {};
	map<string, int> dict = {};
	int index = 0;
	while (index < s.length())
	{
		bool last = false;
		string buff(1, s[index]);
		while (dict.contains(buff))
		{
			index++;
			if (index == s.length())
			{
				last = true;
				break;
			}
			buff += s[index];
		}
		index++;
		if (last)
			ans.push_back(make_pair(dict[buff], '\0'));
		else
		{
			dict.insert(make_pair(buff, dict.size() + 1));
			if (buff.length() == 1)
				ans.push_back(make_pair(0, buff[0]));
			else
				ans.push_back(make_pair(dict[buff.substr(0, buff.length() - 1)], buff[buff.length() - 1]));
		}
	}
	
	for (auto kv : dict) cout << kv.first << " -> " << kv.second << endl;
	return ans;
}

string decodeLZ78(vector<pair<unsigned char, char>> v)
{
	string ans(1, v[0].second);
	map<int, string> dict = { make_pair(1, string(1, v[0].second)) };
	
	for (int i = 1; i < v.size(); i++)
	{
		if ((int)v[i].first != 0)
			ans += dict[v[i].first];
		ans += v[i].second;
		dict.insert(make_pair(dict.size(), string(1, v[i].second)));
	}

	return ans;
};


pair <map<char, vector<bool>>, map<vector<bool>, char>> haffman(string s)
{
	vector<HaffLeaf> leaves = {};
	
	for (char c : s)
	{
		auto newLeaf = find(leaves.begin(), leaves.end(), HaffLeaf(c, 0));
		if (newLeaf == leaves.end())
			leaves.push_back(HaffLeaf(c, 1));
		else
			newLeaf->weight++;
	}
	sort(leaves.begin(), leaves.end());

	//for (HaffLeaf l : leaves) cout << l.chars[0].first << " " << l.weight << endl;

	while (leaves.size() != 1)
	{
		for (pair<char, vector<bool>>& p : leaves[0].chars)
			p.second.insert(p.second.begin(), 0);
		for (pair<char, vector<bool>>& p : leaves[1].chars)
		{
			p.second.insert(p.second.begin(), 1);
			leaves[0].chars.push_back(p);
		}
		leaves[0].weight += leaves[1].weight;
		leaves.erase(leaves.begin() + 1);
		sort(leaves.begin(), leaves.end());
	}

	map<char, vector<bool>> coding = {};
	map<vector<bool>, char> decoding = {};
	for (pair<char, vector<bool>> p : leaves[0].chars)
	{
		coding.insert(p);
		decoding.insert(make_pair(p.second, p.first));
	}
	return make_pair(coding, decoding);
}
vector<bool> codeHaffman(string text, map<char, vector<bool>> codeTable)
{
	vector<bool> ans = {};
	for (char c : text)
		ans.insert(ans.begin(), codeTable[c].begin(), codeTable[c].end());
	return ans;
}
string decodeHaffman(vector<bool> coded, map<vector<bool>, char> decodeTable)
{
	string ans = "";
	reverse(coded.begin(), coded.end());
	vector<bool> curr = {};
	while (!coded.empty())
	{
		while (!decodeTable.contains(curr))
		{
			curr.push_back(coded[coded.size() - 1]);
			coded.pop_back();
		}
		ans += decodeTable[curr];
		curr.clear();
	}
	return ans;
}

pair<map<char, vector<bool>>, map<vector<bool>, char>> haffman(ifstream& in)
{
	string content = "";
	char buff;
	while (in)
	{
		in.get(buff);
		content += buff;
	}
	content.erase(content.end() - 1);
	pair<map<char, vector<bool>>, map<vector<bool>, char>> tables = haffman(content);
	return tables;
}

void codeHaffman(ifstream& in, ofstream& out, map<char, vector<bool>> codeTable)
{
	char buff;
	vector<bool> toWrite = {};
	while (in.get(buff))
	{
		for (bool b : codeTable[buff])
			toWrite.push_back(b);
	}
	char trash = (8 - toWrite.size() % 8) % 8;
	out.write((char*)&trash, sizeof(char));
	for (int i = trash; i > 0; i--)
		toWrite.push_back(0);
	reverse(toWrite.begin(), toWrite.end());
	while (!toWrite.empty())
	{
		unsigned char byte = 0;
		bitset<8> bs = { byte };

		for (int i = 0; i < 8; i++)
		{
			byte = byte << 1;
			if (toWrite[toWrite.size() - 1])
				byte++;
			toWrite.pop_back();
			bs = { byte };
		}
		out.put(byte);
	}
}
void decodeHaffman(ifstream& in, ofstream& out, map<vector<bool>, char> decodeTable)
{
	vector<bool> toDecode = {};
	char byte;
	in.get(byte);
	int trash = byte;
	while (in.get(byte))
	{
		for (int i = 7; i >= 0; i--)
			toDecode.push_back(byte >> i & 1);
	}
	for (int i = 0; i < trash; i++)
		toDecode.pop_back();
	reverse(toDecode.begin(), toDecode.end());
	vector<bool> buff;
	while (!toDecode.empty())
	{
		while (!decodeTable.contains(buff))
		{
			buff.push_back(toDecode[toDecode.size() - 1]);
			toDecode.pop_back();
		}
		out << decodeTable[buff];
		buff.clear();
	}
}

void codeHaffman(ifstream& in, ofstream& out)
{
	vector<HaffLeaf> leaves = {};
	char buff;
	string text = "";
	while (in.get(buff))
		text += buff;
	for (char c : text)
	{
		auto newLeaf = find(leaves.begin(), leaves.end(), HaffLeaf(c, 0));
		if (newLeaf == leaves.end())
			leaves.push_back(HaffLeaf(c, 1));
		else
			newLeaf->weight++;
	}
	sort(leaves.begin(), leaves.end());
	
	// for (HaffLeaf l : leaves) cout << l.chars[0].first << " " << l.weight << endl;

	while (leaves.size() != 1)
	{
		for (pair<char, vector<bool>>& p : leaves[0].chars)
			p.second.insert(p.second.begin(), 0);
		for (pair<char, vector<bool>>& p : leaves[1].chars)
		{
			p.second.insert(p.second.begin(), 1);
			leaves[0].chars.push_back(p);
		}
		leaves[0].weight += leaves[1].weight;
		leaves.erase(leaves.begin() + 1);
		sort(leaves.begin(), leaves.end());
	}

	map<char, vector<bool>> coding = {};
	for (pair<char, vector<bool>> p : leaves[0].chars)
		coding.insert(p);

	unsigned char numOfChar = coding.size();
	out.write((char*)&numOfChar, sizeof(char));
	for (pair<char, vector<bool>> p : coding)
	{
		char c = p.first;
		unsigned char len = p.second.size();
		out.write(&c, sizeof(char));
		out.write((char*)&len, sizeof(char));
	}
	vector<bool> keys = {};
	for (pair<char, vector<bool>> p : coding)
		keys.insert(keys.end(), p.second.begin(), p.second.end());
	// for (auto p : coding) { cout << p.first << " = "; for (bool b : p.second) cout << b; cout << endl; }
	char keysTrash = (8 - keys.size() % 8) % 8;
	out.write((char*)&keysTrash, sizeof(char));
	for (int i = keysTrash; i > 0; i--)
		keys.push_back(0);
	int numOfCode = keys.size() / 8;
	out.write((char*)&numOfCode, sizeof(int));
	reverse(keys.begin(), keys.end());
	while (!keys.empty())
	{
		unsigned char byte = 0;
		bitset<8> bs = { byte };

		for (int i = 0; i < 8; i++)
		{
			byte = byte << 1;
			if (keys[keys.size() - 1])
				byte++;
			keys.pop_back();
			bs = { byte };
		}
		out.put(byte);
	}
	vector<bool> toWrite = {};
	for (char c : text)
	{
		for (bool b : coding[c])
			toWrite.push_back(b);
	}
	char trash = (8 - toWrite.size() % 8) % 8;
	out.write((char*)&trash, sizeof(char));
	for (int i = trash; i > 0; i--)
		toWrite.push_back(0);
	reverse(toWrite.begin(), toWrite.end());
	while (!toWrite.empty())
	{
		unsigned char byte = 0;
		bitset<8> bs = { byte };

		for (int i = 0; i < 8; i++)
		{
			byte = byte << 1;
			if (toWrite[toWrite.size() - 1])
				byte++;
			toWrite.pop_back();
			bs = { byte };
		}
		out.put(byte);
	}
}

void decodeHaffman(ifstream& in, ofstream& out)
{
	char byte;
	in.get(byte);
	unsigned char numOfChars = byte;
	vector<char> chars(numOfChars);
	vector<unsigned char> lens(numOfChars);
	for (int i = 0; i < numOfChars; i++)
	{
		in.get(byte);
		chars[i] = byte;
		in.get(byte);
		lens[i] = byte;
	}
	in.get(byte);
	char keysTrash = byte;
	int numOfCode;
	in.read((char*)&numOfCode, sizeof(int));
	vector<bool> keys = {};
	for (int i = 0; i < numOfCode; i++)
	{
		in.get(byte);
		for (int j = 7; j >= 0; j--)
			keys.push_back(byte >> j & 1);
	}
	for (int i = 0; i < keysTrash; i++)
		keys.pop_back();
	reverse(keys.begin(), keys.end());
	vector<bool> buff;
	map<vector<bool>, char> decode = {};
	for (int i = 0; i < numOfChars; i++)
	{
		for (int j = 0; j < lens[i]; j++)
		{
			buff.push_back(keys[keys.size() - 1]);
			keys.pop_back();
		}
		decode.insert(make_pair(buff, chars[i]));
		buff.clear();
	}
	//for (auto p : decode){ for (bool b : p.first) cout << b; cout << " = " << p.second << endl;}
	vector<bool> toDecode = {};
	in.get(byte);
	unsigned char trash = byte;
	while (in.get(byte))
	{
		for (int i = 7; i >= 0; i--)
			toDecode.push_back(byte >> i & 1);
	}
	for (int i = 0; i < trash; i++)
		toDecode.pop_back();
	reverse(toDecode.begin(), toDecode.end());
	while (!toDecode.empty())
	{
		while (!decode.contains(buff))
		{
			buff.push_back(toDecode[toDecode.size() - 1]);
			toDecode.pop_back();
		}
		out << decode[buff];
		buff.clear();
	}
}