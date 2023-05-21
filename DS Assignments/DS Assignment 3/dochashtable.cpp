#include "dochashtable.h"

//*** General Functions ***//

string wordFilter(string w)
{
	// change the word into lower case
	for (int i = 0; i < w.length(); i++) {
        w[i] = tolower(w[i]);
    }

	// check if the last character is one of the punctuation marks
	while(w[w.length()-1] == '.' || w[w.length()-1] == ',' || w[w.length()-1] == '\\' || w[w.length()-1] == '!' || w[w.length()-1] == '?' || w[w.length()-1] == ';')
	{
		w.pop_back();
	}
	return w;
}

bool isPrime(int n)
{
    if (n <= 1)
        return false;
 
    // Check from 2 to n-1
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;
 
    return true;
}

int findNextPrime(int num)
{
	// If the given number is even, it increments it by 1 to start checking for primes
    if (num % 2 == 0)
        num++;

    // It then iterates by incrementing the number by 2 until a prime number is found.
    while (true) {
        if (isPrime(num))
            return num;

        num += 2;
    }
}

long hashFun1(string key)
{
	long hashVal = 0;
	for (int i = 0; i < key.length(); i++) {
		// compute a hash value for the given key by summing the ASCII values of each character multiplied by a power of 33 corresponding to its position in the key
        hashVal += key[i] * pow(33, key.length() - i - 1);
    }
    return hashVal;
}

long hashFun2(string key)
{
	long hashVal = 0;
	for (int i = 0; i < key.length(); i++) {
		// compute a hash value for the given key by performing bitwise operations on each character's ASCII value
		hashVal = ((hashVal << 5) | (hashVal >> 27));
		hashVal += (unsigned long)key[i];
    }
    return hashVal;
}

long hashFun3(string key)
{
	long hashVal = 0;
	for (int i = 0; i < key.length(); i++) {
		// compute a hash value for the given key by summing the ASCII values of each character
		hashVal += key[i];
    }
    return hashVal;
}

long hashFun4(string key)
{
	long hashVal = 0;
	for (int i = 1; i < key.length(); i++) {
		// compute a hash value for the given key by multiplying each character's ASCII value with the ASCII value of its previous character
		hashVal += key[i] * key[i-1];
    }
    return hashVal;
}

long hashFun5(string key)
{
	long hashVal = 0;
	for (int i = 0; i < key.length(); i++) {
		// compute a hash value for the given key by performing bitwise and shift operations on each character's ASCII value
		hashVal = key[i] + (hashVal << 6) + (hashVal << 16) - hashVal;
    }
    return hashVal;
}

long hashFun6(string key)
{
	long hashVal = 0;
	for (int i = 0; i < key.length(); i++) {
		// compute a hash value for the given key by raising each character's ASCII value to the power of 3 and summing them
		hashVal += pow(key[i], 3);
    }
    return hashVal;
}

//*** Hash Node Methods ***//

HashNode::HashNode(string k, int v = 1)
{
	// Initializes the key and value of the node
    key = k;
    value = v;
}

HashNode::HashNode(){
	key = "";
	value = 0;
}

// Compares two HashNode objects for equality based on their keys
bool HashNode::operator==(const HashNode& n) const{
    if (key == n.key){
        return true;
    }
    return false;
}

// Compares two HashNode objects based on their values
bool HashNode::operator<(const HashNode& n) const{
    if (value < n.value){
        return true;
    }
    return false;
}

// Compares two HashNode objects based on their values
bool HashNode::operator>(const HashNode& n) const{
    if (value > n.value){
        return true;
    }
    return false;
}

// Getter function for retrieving the key of the HashNode
string HashNode::getKey(){return key;}

// Getter function for retrieving the value of the HashNode
int HashNode::getVal(){return value;}

//*** Hash Table Methods ***//

DocHASHTABLE::DocHASHTABLE()
{
	size = 0;
	capacity = 1000001;
	buckets = new MyList<HashNode>[capacity];
}

DocHASHTABLE::~DocHASHTABLE()
{
	// remove all the nodes in the table and delete the buckets array
	clearTable();
	delete[] buckets;
}

int selectedHashFun = 5;

long DocHASHTABLE::hashCode(string key)
{
	long hashCode;

	// call the hash function based on the selected function
	switch(selectedHashFun)
	{
		case 1:
			hashCode = abs(hashFun1(key) % capacity);
		   	break;

		case 2:
			hashCode = abs(hashFun2(key) % capacity);
		    break;
    	case 3:
			hashCode = abs(hashFun3(key) % capacity);
		    break;
		case 4:
			hashCode = abs(hashFun4(key) % capacity);
		    break;
		case 5:
			hashCode = abs((hashFun5(key)*17+10) % capacity);
		    break;
		case 6:
			hashCode = abs(hashFun6(key) % capacity);
		    break;
	}

    return hashCode;
}

int DocHASHTABLE::import(string path)
{
	fakeImport(path); // fake import function to get the number of unique words to make the right capacity size
    ifstream myfile(path);

    if (size > 0){ // check if table is not empty
    	int tempCapacity = findNextPrime(count_unique_words() * 1.25);
    	clearTable();
    	capacity = tempCapacity;
    }

    string word;
    while(myfile >> word)
    {
    	//filter the word from punctuation marks and ignoring the case
    	string filteredWord = wordFilter(word);
        // create hash code for the word
        long hashIndex = hashCode(filteredWord);
        HashNode newNode = HashNode(filteredWord);

        if (buckets[hashIndex].empty()) // check if the list is empty
        {
            // add the hashnode to the list and to the heap
            buckets[hashIndex].addFront(newNode);
            MyHeap.insert(newNode);        
        }
        else
        {
            HashNode* nodePtr = buckets[hashIndex].getSimilar(newNode);

            // if the word was already in the table, increase its node value which is the word frequency
            if(buckets[hashIndex].countElem(newNode) >= 1) 
            {
                nodePtr->value++;
                HashNode tempNode(filteredWord, nodePtr->value);
                if(MyHeap.getMax().value < nodePtr->value)
                {
                	MyHeap.removeMax();
                }
                MyHeap.insert(tempNode);
            }
            // if not, add the hashnode to the list and to the heap
            else
            {
                buckets[hashIndex].addFront(newNode);
                MyHeap.insert(newNode);
            }
        }

        size++;
    }
    return 0;
}

void DocHASHTABLE::select_hashFun(int hashFunID)
{
	// change the selectedHashFun to the value passed by the user
	selectedHashFun = hashFunID;
	cout << "Hash function " << hashFunID << " has been chosen succcesfully!\n\n";
}

int DocHASHTABLE::count_words()
{
	cout << "The total number of words is: " << size << endl;
	return size;
}

int DocHASHTABLE::count_collisions()
{
	int coll = 0;
	
	// loop through the table
	// if the list has nodes, sum its size-1 to the number of collisions
	for (int i = 0; i < capacity; i++)
	{
		if (!buckets[i].empty()){
			coll += buckets[i].getSize()-1;
		}
	}

	cout << "The number of collisions is: " << coll << endl;
	return coll;
}

int DocHASHTABLE::count_unique_words()
{
	int unique = 0;
	
	// loop through the table
	// if the list has nodes, sum its size to the number of collisions
	for (int i = 0; i < capacity; i++)
	{
		if (!buckets[i].empty()){
			unique += buckets[i].getSize();
		}
	}
	return unique;
}

int DocHASHTABLE::find_freq(string word)
{
	// calculates the hash code of the word to find the corresponding bucket in the hashtable
	long hashIndex = hashCode(word);
	// check if the bucket is empty
	if (buckets[hashIndex].empty())
    {
        return 0;
    }
    else
    {
        HashNode newNode(word);
        // if the word exists more than one time in the bucket, returns its frequency
        if(buckets[hashIndex].countElem(newNode) >= 1)
        {
            return buckets[hashIndex].getSimilar(newNode)->getVal();
        }
        return buckets[hashIndex].countElem(newNode);
    }
}

string DocHASHTABLE::find_max()
{
	// return the root of the heap
	return MyHeap.getMax().getKey();
}

void DocHASHTABLE::clearTable()
{
	for (int i = 0; i < capacity; i++)
	{
		while (!buckets[i].empty())
		{
			buckets[i].removeFront();
		}
	}
	int n = MyHeap.getSize()-1;
	while(n--){
		MyHeap.removeMax();
	}
	size = 0;
}

void DocHASHTABLE::fakeImport(string path)
{
    ifstream myfile(path);

    if (size > 0){
    	clearTable();
    }

    string word;
    while(myfile >> word)
    {
    	//filter the word from punctuation marks and ignoring the case
    	string filteredWord = wordFilter(word);
        // create hash code for the word
        long hashIndex = hashCode(filteredWord);
        HashNode newNode(filteredWord);

        if (buckets[hashIndex].empty())
        {
            // add the hashnode to the list
            buckets[hashIndex].addFront(newNode);
        }
        else
        {
            HashNode* nodePtr = buckets[hashIndex].getSimilar(newNode);

            if(buckets[hashIndex].countElem(newNode) >= 1)
            {
                nodePtr->value++;
            }
            else
            {
                buckets[hashIndex].addFront(newNode);
            }
        }

        size++;
    }
}