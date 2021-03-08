#include "HfmTree.h"

HfmTree::HfmTree() {
	
}

HfmTree::HfmTree(string d, int w, int l, int r,int p) {
	data = d;
	weight = w;
	left = l;
	right = r;
	parent = p;
	tag = 0;
}

string HfmTree::getData() {
	return this->data;
}

int HfmTree::getWeight() {
	return this->weight;
}

int HfmTree::getTag() {
	return this->tag;
}

int HfmTree::getLeft() {
	return this->left;
}

int HfmTree::getRight() {
	return this->right;
}

int HfmTree::getParent() {
	return this->parent;
}

string HfmTree::getCharCode() {
	return this->charCode;
}

void HfmTree::setLeft(int left) {
	this->left = left;
}

void HfmTree::setRight(int right) {
	this->right = right;
}

void HfmTree::setParent(int parent) {
	this->parent = parent;
}

void HfmTree::setTag(int tag) {
	this->tag = tag;
}

void HfmTree::setCharCode(string charCode) {
	this->charCode = charCode;
}