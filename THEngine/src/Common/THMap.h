#ifndef THHASHMAP_H
#define THHASHMAP_H

#include "THObject.h"
#include <map>

namespace THEngine
{
	template<class KeyType, class ValueType>
	class Map
	{
	private:
		std::map<KeyType, ValueType> map;

	public:
		void Put(const KeyType& key, const ValueType& value)
		{
			typename std::map<KeyType, ValueType>::iterator iter;
			iter = map.find(key);
			if (iter != map.end())
			{
				iter->second = value;
			}
			else
			{
				std::pair<std::map<KeyType, ValueType>::iterator, bool> insert_pair;
				map.insert(std::pair<KeyType, ValueType>(key, value));
			}
		}

		ValueType Get(const KeyType& key)
		{
			typename std::map<KeyType, ValueType>::iterator iter;
			iter = map.find(key);
			if (iter != map.end())
			{
				return iter->second;
			}
			throw std::runtime_error("requested key does not exist in map.");
		}

		bool HasKey(const KeyType& key)
		{
			typename std::map<KeyType, ValueType>::iterator iter;
			iter = map.find(key);
			return iter != map.end();
		}

		bool Remove(const KeyType& key)
		{
			typename std::map<KeyType, ValueType>::iterator iter;
			iter = map.find(key);
			if (iter != map.end())
			{
				iter->erase();
				return true;
			}
			return false;
		}

		void Clear()
		{
			map.clear();
		}
	};

	class MapIterator
	{
	};
}

#endif