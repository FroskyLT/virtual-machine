#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>

using namespace std;

string read_bin_file(string name = "decryptor.bin");
string read_data_file(string name = "q1_encr.txt");
int get_Rx_or_Ry(string operand, bool Rx = true);
int operand_to_dec(string operand);

int main() {
	unsigned char regs[16] = {};
	int flag = 1;

	string hex_string,
		   data_file,
		   byte;
	vector <string> commands;

	hex_string = read_bin_file();
	data_file = read_data_file();

	int i = 0;
	for (auto it : hex_string)
	{
		i++;
		byte.push_back(it);
		if (i == 2) {
			commands.push_back(byte);
			byte = "";
			i = 0;
		}
	}

	reverse(data_file.begin(), data_file.end());


	map<string, int> hex_dec;
	map<string, int>::iterator it;

	ifstream fd("commands.txt");
	string strtemp; int inttemp;

	while (fd >> strtemp >> inttemp)
		hex_dec[strtemp] = inttemp;
	fd.close();

	ofstream fr("output.txt");
	bool run = true, eof = false;
	string operation, operand;
	int choose = 1,
		size = commands.size();

	while (run)
	{
		operation = commands[i];
		operand = commands[i + 1];

		it = hex_dec.find(operation);
		if (it != hex_dec.end())
			choose = it->second;

		int Rx, Ry, constant;
		Rx = get_Rx_or_Ry(operand);
		Ry = get_Rx_or_Ry(operand, false);
		constant = operand_to_dec(operand);


		switch (choose)
		{
		case 1:
			regs[Rx] += 1;				break;

		case 2:
			regs[Rx] -= 1;				break;

		case 3:
			regs[Rx] = regs[Ry];		break;

		case 4:
			regs[0] = constant;			break;

		case 5:
			regs[Rx] *= 2;				break;

		case 6:
			regs[Rx] /= 2;				break;

		case 7:
			i += constant;				break;

		case 8:
			if (!flag) i += constant;	break;

		case 9:
			if (flag) i += constant;	break;

		case 10: //
			if (eof) i += constant;		break;

		case 11:
			run = false;				break;

		case 12:
			regs[Rx] = regs[Rx] + regs[Ry];		break;

		case 13:
			regs[Rx] = regs[Rx] - regs[Ry];		break;

		case 14:
			regs[Rx] = (regs[Rx] != regs[Ry]);	break;

		case 15:
			regs[Rx] = (regs[Rx] || regs[Ry]);	break;

		case 16: 
			regs[Rx] = data_file.back();
			//cout << regs[Rx];
			data_file.pop_back();
			if (data_file.size() == 0)
				eof = true;				break;

		case 17:
			//cout << regs[Rx];
			fr << regs[Rx];				break;

		default:						
										break;
		}

		for (int i = 0; i < 16; i++)
			cout << regs[i] << " ";
		cout << i << endl;

		if (i >= size - 2)
			run = false;
		i += 2;

	}

	fr.close();

	return 0;
}

string read_bin_file(string name) {

	ifstream::pos_type size;
	char* memory;

	ifstream fd(name, ios::in | ios::binary | ios::ate);
	if (fd.is_open())
	{
		size = fd.tellg();
		memory = new char[size];
		fd.seekg(0, ios::beg);
		fd.read(memory, size);
		fd.close();


		ostringstream ret;

		for (string::size_type i = 0; i < string(memory, size).length(); ++i)
		{
			int z = string(memory, size)[i] & 0xff;
			ret << hex << setfill('0') << setw(2) << (uppercase) << z;
		}

		return ret.str();
	}

}
string read_data_file(string name) {
	string data = "";
	char sym;
	ifstream fd(name);
	while (fd >> sym)
		data.push_back(sym);

	fd.close();

	return data;
}

int get_Rx_or_Ry(string operand, bool Rx) {
	int R = -1;

	//hex char to dec int
	if (Rx) {
		if (operand[1] >= '0' && operand[1] <= '9')
			R = operand[1] - '0';
		else if (operand[1] >= 'A' && operand[1] <= 'F')
			R = operand[1] - 'A' + 10;
	}
	else {
		if (operand[0] >= '0' && operand[0] <= '9')
			R = operand[0] - '0';
		else if (operand[0] >= 'A' && operand[0] <= 'F')
			R = operand[0] - 'A' + 10;
	}

	return R;
}
int operand_to_dec(string operand) {
	//hex string to signed int
	unsigned char chTest = std::stoi(operand, nullptr, 16);
	char chTest2 = *reinterpret_cast<char*>(&chTest);

	return static_cast<int>(chTest2);
}