#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#include <algorithm>
#include <forward_list>
#include <functional>
#include <list>
#include <stdexcept>
#include <vector>

template <typename KeyT>
class UnorderedSet {
 public:
  using BucketType = std::list<KeyT>;

  UnorderedSet() = default;

  explicit UnorderedSet(size_t bucket_count) : buckets_(bucket_count) {
  }

  template <typename ForwardIt>
  UnorderedSet(ForwardIt first, ForwardIt last) {
    size_t count = std::distance(first, last);
    buckets_.resize(count);
    for (auto it = first; it != last; ++it) {
      Insert(*it);
    }
  }

  UnorderedSet(const UnorderedSet& other) {
    buckets_.resize(other.buckets_.size());
    for (const auto& bucket : other.buckets_) {
      for (const auto& key : bucket) {
        Insert(key);
      }
    }
  }

  UnorderedSet(UnorderedSet&& other) noexcept {
    Swap(other);
  }

  UnorderedSet& operator=(const UnorderedSet& other) {
    if (this != &other) {
      UnorderedSet temp(other);
      Swap(temp);
    }
    return *this;
  }

  UnorderedSet& operator=(UnorderedSet&& other) noexcept {
    if (this != &other) {
      Clear();
      Swap(other);
    }
    return *this;
  }

  ~UnorderedSet() = default;

  size_t Size() const {
    return size_;
  }

  bool Empty() const {
    return size_ == 0;
  }

  void Clear() {
    buckets_.clear();
    size_ = 0;
  }

  bool Find(const KeyT& key) const {
    if (buckets_.empty()) {
      return false;
    }
    const auto& bucket = buckets_[BucketIndex(key)];
    return std::find(bucket.begin(), bucket.end(), key) != bucket.end();
  }

  void Insert(const KeyT& key) {
    if (Find(key)) {
      return;
    }
    MaybeRehash();
    buckets_[BucketIndex(key)].push_front(key);
    ++size_;
  }

  void Insert(KeyT&& key) {
    if (Find(key)) {
      return;
    }
    MaybeRehash();
    buckets_[BucketIndex(key)].push_front(std::move(key));
    ++size_;
  }

  void Erase(const KeyT& key) {
    if (buckets_.empty()) {
      return;
    }
    auto& bucket = buckets_[BucketIndex(key)];
    auto it = std::find(bucket.begin(), bucket.end(), key);
    if (it != bucket.end()) {
      bucket.erase(it);
      --size_;
    }
  }

  void Rehash(size_t new_bucket_count) {
    if (new_bucket_count < size_ || new_bucket_count == buckets_.size()) {
      return;
    }
    std::vector<BucketType> new_buckets(new_bucket_count);
    for (auto& bucket : buckets_) {
      for (auto& key : bucket) {
        size_t new_index = std::hash<KeyT>{}(key) % new_bucket_count;
        new_buckets[new_index].push_front(std::move(key));
      }
    }
    buckets_ = std::move(new_buckets);
  }

  void Reserve(size_t new_bucket_count) {
    if (new_bucket_count > buckets_.size()) {
      Rehash(new_bucket_count);
    }
  }

  size_t BucketCount() const {
    return buckets_.size();
  }

  size_t BucketSize(size_t id) const {
    if (id >= buckets_.size()) {
      return 0;
    }
    return buckets_[id].size();
  }

  size_t Bucket(const KeyT& key) const {
    if (buckets_.empty()) {
      return 0;
    }
    return BucketIndex(key);
  }

  float LoadFactor() const {
    return buckets_.empty() ? 0.0f : static_cast<float>(size_) / buckets_.size();
  }

  void Swap(UnorderedSet& other) noexcept {
    std::swap(buckets_, other.buckets_);
    std::swap(size_, other.size_);
  }

 private:
  std::vector<BucketType> buckets_;
  size_t size_ = 0;

  size_t BucketIndex(const KeyT& key) const {
    return std::hash<KeyT>{}(key) % buckets_.size();
  }

  void MaybeRehash() {
    if (buckets_.empty()) {
      buckets_.resize(1);
    } else if (size_ >= buckets_.size()) {
      Rehash(buckets_.size() * 2);
    }
  }
};

#endif