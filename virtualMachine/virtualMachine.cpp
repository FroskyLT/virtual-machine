#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;

string read_bin_file(string name = "decryptor.bin");
void commands(string operation, string operand, unsigned char regs[], int i);
int get_Rx_or_Ry(string operand, bool Rx = true);
//void operand_to_dec();

int main()
{
	unsigned char regs[16];
	char prog_mem[256];
	int flag;

	string hex_string, item;
	vector <string> items;
	hex_string = read_bin_file();

	int i = 0;
	for (auto it : hex_string)
	{
		i++;
		item.push_back(it);
		if (i == 2) {
			items.push_back(item);
			item = "";
			i = 0;
		}
	}

	/*for (auto it : items) {
		cout << it << " ";
		i++;
		if (i == 8) { cout << endl; i = 0; }
	}*/
	//cout << items.size();

	for (int i = 0; i < items.size(); i+=2)
	{
		string operation, operand;
		operation = items[i];
		operand = items[i + 1];

		//commands(operation, operand, regs, i);

		cout<<get_Rx_or_Ry(operand, false)<<" ";

	}
}

string read_bin_file(string name) {

	ifstream::pos_type size;
	char* memblock;

	ifstream file(name, ios::in | ios::binary | ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();

		cout << "the complete file content is in memory" << endl;

		ostringstream ret;

		for (string::size_type i = 0; i < string(memblock, size).length(); ++i)
		{
			int z = string(memblock, size)[i] & 0xff;
			ret << hex << setfill('0') << setw(2) << (uppercase) << z;
		}

		return ret.str();
	}

}

void commands(string operation, string operand, unsigned char regs[], int i) {
	map<string, int> hex_dec;

	ifstream fd("commands.txt");
	string strtemp; int inttemp;

	while (fd >> strtemp >> inttemp)
		hex_dec[strtemp] = inttemp;
	fd.close();

	int choose = 1;

	cout << operation << " " << operand << endl;
	switch (choose)
	{
	case 1:

		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	case 16:
		break;
	default:
		break;
	}
}

int get_Rx_or_Ry(string operand, bool Rx) {
	int R = -1;

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