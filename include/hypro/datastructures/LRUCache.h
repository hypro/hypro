/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "util/adaptions_eigen/adaptions_eigen.h"
#include "util/statistics/statistics.h"

#include <list>

namespace std {
    template<typename first, typename second>
    struct hash<std::pair<first, second>> {
        std::size_t operator()(std::pair<first, second> const &keyPair) const {
            size_t seed = 0;
            carl::hash_add(seed, keyPair.first);
            carl::hash_add(seed, keyPair.second);
            return seed;
        }
    };
}  // namespace std

namespace hypro {

    template<typename Key, typename Value>
    class LRUCache {
    private:
        using EntryPair = std::pair<Key, Value>;
        using CacheList = std::list<EntryPair>;

        CacheList mCacheList;
        std::unordered_map<Key, typename CacheList::iterator, std::hash<Key>> mCacheMap;
        std::size_t mEntryCount = 0;
        std::size_t mMaxSize;

    public:
        LRUCache() = delete;

        LRUCache(const LRUCache &orig) = delete;

        LRUCache(LRUCache &&orig) = delete;

        explicit LRUCache(std::size_t size)
                : mMaxSize(size) {
            // TRACE("hypro.datastructures.cache","Created cache of size " << size << " (@" << this << ")" );
        }

        typename CacheList::iterator begin() { return mCacheList.begin(); }

        typename CacheList::iterator end() { return mCacheList.end(); }

        typename CacheList::const_iterator get(const Key &key) const {
            COUNT("Cache-Access");
            auto it = mCacheMap.find(key);
            if (it == mCacheMap.end()) {
                // COUNT("Cache-Miss");
                return mCacheList.end();
            }
            // COUNT("Cache-Find");
            return it->second;
        }

        bool has(const Key &key) const { return mCacheMap.find(key) != mCacheMap.end(); }

        typename CacheList::iterator insert(const Key &key, const Value &value) {
            // TRACE("hypro.datastructures.cache","Add element to cache. Current size: " << this->size() << " (@" << this << ")");
            assert(mEntryCount == mCacheList.size() && mEntryCount == mCacheMap.size());
            auto it = mCacheMap.find(key);
            if (it != mCacheMap.end()) {
                mCacheList.erase(it->second);
                (*it).second = mCacheList.insert(mCacheList.begin(), std::make_pair(key, value));
                return (*it).second;
            } else {
                if (mEntryCount == mMaxSize) {
                    // TRACE("hypro.datastructures.cache","Cache full, remove least used element." << " (@" << this << ")");
                    mCacheMap.erase(mCacheList.back().first);
                    mCacheList.pop_back();
                    --mEntryCount;
                }
                auto it = mCacheList.insert(mCacheList.begin(), std::make_pair(key, value));
                mCacheMap.emplace(key, it);
                ++mEntryCount;
                return it;
            }
        }

        std::size_t size() const {
            assert(mEntryCount == mCacheList.size() && mEntryCount == mCacheMap.size());
            return mEntryCount;
        }
    };

}  // namespace hypro
