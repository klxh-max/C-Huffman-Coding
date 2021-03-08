#include<bits/stdc++.h>
#include "HfmTree.h"
using namespace std;

// 定义全局哈弗曼树向量
vector<HfmTree>hfmTreeArr;
string textfile = "";

// 哈弗曼树的构建
/**
* @param {int} n 表示输入了多少个字符
*/
void createHfmTree(int n) {
	for (int i = n;i < 2 * n - 1;i++) {
		HfmTree temp;
		hfmTreeArr.push_back(temp);
	}
	/*cout << hfmTreeArr.size();*/
	int i = 0;

	// 循环n-1 次，每一次找到两个最小的值，添加进向量中
	while (i < n - 1)
	{
		// 每次循环的两个最小值（字符的权重）
		int minData1 = 99999, minData2 = 99999;
		// 每次循环两个最小权重字符的 索引值（下标）
		int leftIndex = -1, rightIndex = -1;

		for (int j = 0; j < n + i;j++) {
			if (hfmTreeArr[j].getWeight() < minData1 && hfmTreeArr[j].getTag() == 0) {
				minData2 = minData1;
				rightIndex = leftIndex;
				minData1 = hfmTreeArr[j].getWeight();
				leftIndex = j;
			}
			else if (hfmTreeArr[j].getWeight() < minData2 && hfmTreeArr[j].getTag() == 0) {
				minData2 = hfmTreeArr[j].getWeight();
				rightIndex = j;
			}
		}

		int sum = minData1 + minData2;

		HfmTree temp = HfmTree("", sum, leftIndex, rightIndex, -1);
		hfmTreeArr[n + i] = temp;
		hfmTreeArr[leftIndex].setParent(n + i);
		hfmTreeArr[leftIndex].setTag(1);

		hfmTreeArr[rightIndex].setParent(n + i);
		hfmTreeArr[rightIndex].setTag(1);

		i++;
	}
}

// 哈夫曼编码
/**
* @parma {HfmTree*} node  表示节点
* @parma {string} data 表示需要转换的字符（单个）
* @parma {string} charcode 表示这个节点的哈夫曼编码
*/



void hfmCode(int a, string data,string charcode) {
	//cout << charcode << " " << hfmTreeArr[a].getData() << endl;
	if (hfmTreeArr[a].getLeft() == -1 && hfmTreeArr[a].getRight() == -1) {
		if (hfmTreeArr[a].getData() == data) {
			hfmTreeArr[a].setCharCode(charcode);
		}
	}
	if (hfmTreeArr[a].getLeft() != -1) {
		hfmCode(hfmTreeArr[a].getLeft(), data,charcode + "0");
	}
	if (hfmTreeArr[a].getRight() != -1) {
		hfmCode(hfmTreeArr[a].getRight(), data, charcode + "1");
	}
}//编码

void hfmDecode(string a) {
	int t = 0;
	textfile = "";
	while (1) {
		int k = hfmTreeArr.size()-1,i=0;
		for ( i = t;i < a.length();i++) {
			if (hfmTreeArr[k].getLeft() != -1 && hfmTreeArr[k].getRight() != -1) {
				if (a[i] == '1')
					k = hfmTreeArr[k].getRight();
				else if (a[i] == '0')
					k = hfmTreeArr[k].getLeft();
			}
			else {
				textfile+=hfmTreeArr[k].getData();
				t = i;
				break;
			}
		}
		if (i == a.length()) {
			textfile += hfmTreeArr[k].getData();
			break;
		}
	}
}//译码

fstream File;

int main() {
	int n;
	cout << "请输入需要的字符集长度：\n";
	cin >> n;
	cout << "请输入字符 和 权值（中间用空格隔开）\n";
	getchar(); 
	for (int i = 0;i < n;i++) {
		string data1;
		getline(cin, data1);
		string data2(1, data1[0]);
		int weight=0;
		string p = "";
		for (int j = 2;j < data1.length();j++)
			p += data1[j];
		weight = atoi(p.c_str());
		HfmTree temp = HfmTree(data2, weight, -1, -1, -1);
		hfmTreeArr.push_back(temp);
	}
	createHfmTree(n);

	File.open("D:\\Project\\C++Project\\数据结构课设\\hfm Tree.txt", ios::out);
	File << setw(8) << setiosflags(ios::left) << "权重" << setw(8) << "父母" << setw(8) << "左孩子" << setw(8) << "右孩子" << endl;
	for (int i = 0;i < hfmTreeArr.size()-1;i++) {
		if (hfmTreeArr[i].getLeft() != -1 && hfmTreeArr[i].getRight() != -1)
			File << setw(10) << setiosflags(ios::left) << hfmTreeArr[i].getWeight() << setw(10) << hfmTreeArr[hfmTreeArr[i].getParent()].getWeight() << setw(10) << hfmTreeArr[hfmTreeArr[i].getLeft()].getWeight() << setw(10) << hfmTreeArr[hfmTreeArr[i].getRight()].getWeight() << endl;
		else
			File << setw(10) << setiosflags(ios::left) << hfmTreeArr[i].getWeight() << setw(10) << hfmTreeArr[hfmTreeArr[i].getParent()].getWeight() << setw(10) << "无" << setw(10) << "无" << endl;
	}
	File << setw(10) << setiosflags(ios::left) << hfmTreeArr[hfmTreeArr.size() - 1].getWeight() << setw(10) << "无" << setw(10) << hfmTreeArr[hfmTreeArr[hfmTreeArr.size() - 1].getLeft()].getWeight() << setw(10) << hfmTreeArr[hfmTreeArr[hfmTreeArr.size() - 1].getRight()].getWeight() << endl;
	File.close();
	for (int i = 0; i < hfmTreeArr.size();i++) 
		hfmCode(hfmTreeArr.size() - 1, hfmTreeArr[i].getData(), "");

	cout << endl;

	cout << setw(8) << setiosflags(ios::left) << "权重" << setw(8) << "父母" << setw(8) << "左孩子" << setw(8) << "右孩子" << endl;
	for (int i = 0;i < hfmTreeArr.size() - 1;i++) {
		if (hfmTreeArr[i].getLeft() != -1 && hfmTreeArr[i].getRight() != -1)
			cout << setw(10) << setiosflags(ios::left) << hfmTreeArr[i].getWeight() << setw(10) << hfmTreeArr[hfmTreeArr[i].getParent()].getWeight() << setw(10) << hfmTreeArr[hfmTreeArr[i].getLeft()].getWeight() << setw(10) << hfmTreeArr[hfmTreeArr[i].getRight()].getWeight() << endl;
		else
			cout << setw(10) << setiosflags(ios::left) << hfmTreeArr[i].getWeight() << setw(10) << hfmTreeArr[hfmTreeArr[i].getParent()].getWeight() << setw(10) << "无" << setw(10) << "无" << endl;
	}
	cout << setw(10) << setiosflags(ios::left) << hfmTreeArr[hfmTreeArr.size() - 1].getWeight() << setw(10) << "无" << setw(10) << hfmTreeArr[hfmTreeArr[hfmTreeArr.size() - 1].getLeft()].getWeight() << setw(10) << hfmTreeArr[hfmTreeArr[hfmTreeArr.size() - 1].getRight()].getWeight() << endl;
	
	for (int i = 0; i < hfmTreeArr.size();i++)
		hfmCode(hfmTreeArr.size() - 1, hfmTreeArr[i].getData(), "");
	cout << "请输入你想进行编码的内容\n";
	string tobetran , codefile = "";
	cin >> tobetran;
	File.open("D:\\Project\\C++Project\\数据结构课设\\ToBeTran.txt", ios::out);
	File << tobetran;
	File.close();

	File.open("D:\\Project\\C++Project\\数据结构课设\\CodeFile.txt", ios::out);
	for (int j = 0;j < tobetran.length();j++) {
		for (int q = 0;q < hfmTreeArr.size();q++) {
			string x(1, tobetran[j]);
			if (x == hfmTreeArr[q].getData())
				File << hfmTreeArr[q].getCharCode();
		}
	}
	File.close();

	File.open("D:\\Project\\C++Project\\数据结构课设\\CodeFile.txt", ios::in);
	string in2;
	while (getline(File, in2)) {
		codefile += in2;
	}
	File.close();

	hfmDecode(codefile);
	File.open("D:\\Project\\C++Project\\数据结构课设\\Textfile.txt", ios::out);
	File << textfile;
	File.close();

	cout << "编码紧凑结果如下\n";

	File.open("D:\\Project\\C++Project\\数据结构课设\\CodePrin.txt", ios::out);
	int o = 0;
	for (int j = 0;j < codefile.length();j++) {
			cout << codefile[j];
			File<< codefile[j];
			o++;
			if(o==50){
				cout << endl;
				File << endl;
				o = 0;
		}
	}
	File.close();

	return 0;
}


