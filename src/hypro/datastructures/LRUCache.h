#pragma once

#include "util/adaptions_eigen/adaptions_eigen.h"
#include "util/statistics/statistics.h"
#include <list>
#include <boost/unordered_map.hpp>


namespace std {
	template<typename first, typename second>
	struct hash<std::pair<first,second>> {
	    std::size_t operator()(std::pair<first,second> const& keyPair) const
	    {
	    	size_t seed = 0;
			carl::hash_add(seed, keyPair.first);
			carl::hash_add(seed, keyPair.second);
			return seed;
	    }
	};
} // namespace std



namespace hypro {

	template<typename Key, typename Value>
	class LRUCache {

	private:
		using EntryPair = std::pair<Key,Value>;
		using CacheList = std::list<EntryPair>;

		CacheList mCacheList;
		boost::unordered_map<Key, typename CacheList::iterator, std::hash<Key>> mCacheMap;
		std::size_t mEntryCount = 0;
		std::size_t mMaxSize;

	public:
		LRUCache() = delete;
		LRUCache(std::size_t size) : mMaxSize(size) {
			TRACE("hypro.datastructures.cache","Created cache of size " << size << " (@" << this << ")" );
		}

		typename CacheList::iterator begin() { return mCacheList.begin(); }
		typename CacheList::iterator end() { return mCacheList.end(); }

		inline typename CacheList::iterator get(const Key& key) {
			COUNT("Cache-Access");
			auto it = mCacheMap.find(key);
			if(it == mCacheMap.end()) {
				COUNT("Cache-Miss");
				return mCacheList.end();
			}
			COUNT("Cache-Find");
			return it->second;
		}

		inline bool has(const Key& key) const { return mCacheMap.find(key) != mCacheMap.end(); }

		inline typename CacheList::iterator insert(const Key& key, const Value& value) {
			TRACE("hypro.datastructures.cache","Add element to cache. Current size: " << this->size() << " (@" << this << ")");
			assert(mEntryCount == mCacheList.size() && mEntryCount == mCacheMap.size());
			auto it = mCacheMap.find(key);
			if(it != mCacheMap.end()) {
				mCacheList.erase(it->second);
				mCacheMap[key] = mCacheList.insert(mCacheList.begin(), std::make_pair(key,value));
				return mCacheList.begin();
			} else {
				if(mEntryCount == mMaxSize){
					TRACE("hypro.datastructures.cache","Cache full, remove least used element." << " (@" << this << ")");
					mCacheMap.erase(mCacheList.back().first);
					mCacheList.erase(--mCacheList.end());
					--mEntryCount;
				}
				mCacheMap[key] = mCacheList.insert(mCacheList.begin(), std::make_pair(key,value));
				++mEntryCount;
				return mCacheList.begin();
			}
		}

		std::size_t size() const {
			assert(mEntryCount == mCacheList.size() && mEntryCount == mCacheMap.size());
			return mEntryCount;
		}
	};

} // namespace
