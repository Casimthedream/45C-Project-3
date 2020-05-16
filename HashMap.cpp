#include <iostream> 
#include "HashMap.hpp"  
#include <string>

namespace
{
    unsigned int defaultHash(const std::string& str)
    {
        unsigned int total = 0;
        for (int i = 0; i < str.length(); ++i)
        {
            total += int(str[i]);
        }
        return total; 
    } 

}

HashMap:: HashMap() 
    :hashFunction{defaultHash}, kv_pairs{0}, buckets{INITIAL_BUCKET_COUNT}
{
    set_table(); 
}

HashMap::HashMap(HashFunction hashFunction)
    :hashFunction{hashFunction}, kv_pairs{0}, buckets{INITIAL_BUCKET_COUNT}  
{
    set_table(); 
}

HashMap::HashMap(const HashMap& hm)
{   //Make copy of hm Hashmap 
    hashFunction = hm.hashFunction;
    kv_pairs = 0;
    buckets = hm.buckets; 
    set_table(); 
    for (int i = 0; i < hm.buckets; ++i)
    {
        Node *head = hm.hashTable[i]; 

        if (head == nullptr)
        {
            hashTable[i] = nullptr; 
        }
        else
        {
            while(head != nullptr)
            {
                add(head->key, head->value); 
                head = head->next; 
            }
        }
    }

}

HashMap::~HashMap() 
{
    for (int i = 0; i < buckets; ++i)
    {
       Node *node = hashTable[i];  
       if (node == nullptr)
        {
            continue;
        }
        Node *head = node; 
        Node *tail = head;         
        while(head != nullptr)
        {
            tail = head; 
            head = head->next; 
            delete tail; 
        }
    }
    delete[] hashTable; 
}


HashMap& HashMap::operator=(const HashMap& hm)  // WANT to give the left side the value of the 
                                                // of the right side 
{                                               // Dealocate the left side too 
    if (this != &hm)
    {   
        hashFunction = hm.hashFunction;
        kv_pairs = hm.kv_pairs;
        int ogsize = buckets;
        buckets = hm.buckets; 
        Node** oghashTable = hashTable; 
        set_table(); 

        for (int i = 0; i < hm.buckets; ++i)
        {
            Node *head = hm.hashTable[i]; 
            if(head == nullptr)
            {
                hashTable[i] = nullptr; 
            }
            else 
            {
                while(head != nullptr)
                { 
                    add(head->key,head->value);
                    head = head->next; 
                }
            }
        } 
        for (int i = 0; i < ogsize; ++i)
        {
            Node *node = oghashTable[i];
            if (node == nullptr) 
            {
                continue; 
            }
            else
            {
                Node *head = node; 
                Node *tail = head->next; 
                while(head != nullptr)
                {
                    tail = head; 
                    head = head->next; 
                    delete tail; 
                }
            }
        }

        delete[] oghashTable; 
        
    }
    return *this; 
}


unsigned int HashMap::size() const 
{
    return kv_pairs; 
} 

void HashMap::add(const std::string& key, const std::string& value) //NOT FINISHED 
{
    unsigned int hashKey = hashFunction(key); 
    hashKey %=  buckets; 
    Node *end = hashTable[hashKey]; 
	Node *second_to_last = end;

    Node *kvpair = new Node; 
	kvpair->key = key;
	kvpair->value = value;
	kvpair->next = nullptr;

	if(end == nullptr) 
	{
		hashTable[hashKey] = kvpair;
        kv_pairs++;
        return; 
	}
	while(end != nullptr)
	{
		if(end->key == key)
		{
			return;
		}
		else
		{
			second_to_last = end; 
			end = end->next;
		}
	}

	second_to_last->next = kvpair; 
	kv_pairs++;

    if(loadFactor() > .8)
    {
        newBuckets(); 
    }

    return;   
    
}

bool HashMap::contains(const std::string& key) const
{
    for(int i = 0; i < buckets; ++i)
    {
        Node *head = hashTable[i]; 

        if(head == nullptr)
        {
            continue; 
        }
        else 
        {
            while (head != nullptr)
                if (head->key == key)
                {
                    return true;
                }
                else
                {
                    head = head->next; 
                }
        }
    }
    return false; 
}
   
bool HashMap::remove(const std::string& key)
{
    for(int i = 0; i < buckets; ++i)
    {
        Node *node = hashTable[i]; 
        Node *head = node; 
        if(node == nullptr)
        {
            continue; 
        }
        else 
        {
            
            while (node != nullptr)

                if (node->key == key)           //If key contains node
                {
                    if(node->key == head->key)  //If its first 
                    {
                        if (node->next == nullptr)  //If its the only node 
                        {
                            hashTable[i] = nullptr;
                            delete node;
                            kv_pairs -= 1;
                            return true; 
                        }
                        else
                        {
                            hashTable[i] = head->next; 
                            delete node;
                            kv_pairs -= 1;
                            return true;  
                        }
                    }
                    else
                    {
                        head->next = node->next; 
                        delete node; 
                        kv_pairs -= 1; 
                        return true;
                    }
                    
                }
                else
                {
                    head = node; 
                    node = node->next; 
                }
        }
    }
    return false; 
}

std::string HashMap::value(const std::string& key) const
{
    for(int i = 0; i < buckets; ++i)
    {
        Node *node = hashTable[i]; 
        
        if(node == nullptr)
        {
            continue; 
        }
        else
        {
            while(node != nullptr)
            {
                if (node->key == key)
                {
                    return node->value; 
                } 
                else
                {
                    node = node->next;
                }
                
            }
        }
    }
    return ""; 
}

double HashMap::loadFactor() const 
{
    double a = kv_pairs;
    double b = buckets;
    return a/b; 
}

unsigned int HashMap::maxBucketSize() const
{
    unsigned int size = 0;
    for(int i = 0; i < buckets; ++i)
    {
        unsigned int temp = 0;
        Node *node = hashTable[i]; 
         
        if(node == nullptr)
        {
            continue; 
        }
        else 
        {
            
            while (node != nullptr)    
            {
                temp += 1;
                node = node->next; 
            }
        }
        if(temp>size)
        {
            size = temp;
        }
    }
    
    return size;  
}

unsigned int HashMap::bucketCount() const
{
    return buckets; 
}

void HashMap::set_table()
{
    hashTable = new Node*[buckets];
    for (int i = 0; i < buckets; ++i)
    {
        hashTable[i] = nullptr; 
    }
}

void HashMap::newBuckets()
{
    kv_pairs = 0;
    int old_count = buckets;
    buckets = (2 * buckets) + 1; 
    Node** oldhashTable = hashTable;   
    set_table();
    for(int i = 0; i < old_count; ++i)
    {
        Node *kvpair = oldhashTable[i]; 
        Node *prev = kvpair; 

        if(kvpair == nullptr)
        {
            continue; 
        }
        while(kvpair != nullptr)
        {
            add(kvpair->key,kvpair->value);
            prev = kvpair; 
            kvpair =kvpair->next; 
            delete prev; 
            
        }
    }
    delete[] oldhashTable; 
}
