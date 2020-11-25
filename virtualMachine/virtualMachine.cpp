#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	unsigned char regs[16] = {};
	char prog_mem[256];
	bool flag = false;

	ifstream fd;
	ofstream fr;

	fd.open("q2_decryptor.bin", ios::binary);
	fd.read(prog_mem, 256);
	fd.close();

	int length = strlen(prog_mem);

	//for (int i = 0; i <= length - 1; i+=2)
		//cout << i << ".  " << (int)prog_mem[i] << " " << (int)prog_mem[i + 1] << endl;


	fd.open("to_be_decrypted.txt");
	fr.open("output.txt");

	bool run = true; 
	int i = 0;
	while (run)
	{
		char operation, operand;
		int Rx, Ry, constant;

		operation = prog_mem[i];
		operand = prog_mem[i + 1];
		Rx = operand & 0x0F;
		Ry = (operand & 0xF0) >> 4;
		constant = (int)operand;

		//cout << "i= " << i << "       " << (int)operation << " " << (int)operand << " " << Ry << " " << Rx << " " << constant << endl << endl;

		bool next = true;

		switch (operation)
		{
		case 1:
			regs[Rx] = regs[Rx] + 1;					break;

		case 2:
			regs[Rx] = regs[Rx] - 1;					break;

		case 3:
			regs[Rx] = regs[Ry];						break;

		case 4:
			regs[0] = (unsigned char)operand;			break;

		case 5:
			regs[Rx] = (regs[Rx] << 1);					break;

		case 6:
			regs[Rx] = (regs[Rx] >> 1);					break;

		case 7:
			i += constant; next = false;				break;

		case 8://
			if (!flag) { i += constant; next = false; } break;

		case 9://
			if (flag) { i += constant; next = false; }	break;

		case 10:
			if (flag) {	i += constant; next = false; }	break;

		case 11:
			cout << "\nSuccessfully ended\n";
			run = false;								break;

		case 12:
			regs[Rx] = regs[Rx] + regs[Ry];				break;

		case 13:
			regs[Rx] = regs[Rx] - regs[Ry];				break;

		case 14:
			regs[Rx] = (regs[Rx] | regs[Ry]) & (~(regs[Rx] & regs[Ry]));
														break;

		case 15:
			regs[Rx] = (regs[Rx] | regs[Ry]);			break;

		case 16:
			char byte;
			if (fd.get(byte)) {
				flag = false;
				regs[Rx] = (unsigned char)byte;
			}
			else if (fd.eof()) flag = true;				break;

		case 17:
			cout << regs[Rx];
			fr << regs[Rx];								break;

		default:
														break;
		}

		if (next)
			i += 2;
		if (i >= length && run == true) {
			run = false;
			cout << "\nOut of range\n";
		}

	}
	fd.close();
	fr.close();

	return 0;
}
